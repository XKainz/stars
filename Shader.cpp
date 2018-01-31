#include "Shader.h"

Shader::Shader()
{

}

Shader::Shader(const char* vsFile, const char* fsFile)
{
    Shader_init(vsFile,fsFile);
}

void Shader::Shader_init(const char* vsFile, const char* fsFile)
{
    shader_vp = glCreateShader(GL_VERTEX_SHADER);
    shader_fp = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vsTexts=Shader_textFileRead(vsFile);
    std::string fsTexts=Shader_textFileRead(fsFile);

    const char* vsText = vsTexts.c_str();
    const char* fsText = fsTexts.c_str();

    if(vsText==NULL||fsText==NULL){
        std::cout << "Importing Shaders did not work" << std::endl;
    }

    glShaderSource(shader_vp,1,&vsText,0);
    glShaderSource(shader_fp,1,&fsText,0);

    glCompileShader(shader_vp);
    char buffer[512];
    glGetShaderInfoLog(shader_vp, 512, NULL, buffer);
    std::cout << buffer << std::endl;
    glCompileShader(shader_fp);
    glGetShaderInfoLog(shader_fp, 512, NULL, buffer);
    std::cout << buffer << std::endl;

    shader_id = glCreateProgram();
    glAttachShader(shader_id,shader_fp);
    glAttachShader(shader_id,shader_vp);
    glBindFragDataLocation(shader_id, 0, "outColor");
    glLinkProgram(shader_id);


}

void Shader::Shader_bind()
{
    glUseProgram(shader_id);
}

void Shader::Shader_unbind()
{
    glUseProgram(0);
}

unsigned int Shader::Shader_id()
{
    return shader_id;
}

std::string Shader::Shader_textFileRead(const char* file){
    std::ifstream inputFile(file,std::ios::in);
    std::string fileContents;
    while (inputFile.good())
    {
        char x = inputFile.get();
        fileContents = fileContents + x;
    }
    inputFile.close();
    return fileContents;
}

Shader::~Shader()
{
    glDetachShader(shader_id,shader_vp);
    glDetachShader(shader_id,shader_fp);

    glDeleteShader(shader_vp);
    glDeleteShader(shader_fp);
    glDeleteProgram(shader_id);
}

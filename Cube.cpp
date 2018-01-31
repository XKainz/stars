#include "Cube.h"
static const GLfloat bufferData[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f


};

Cube::Cube(Camera* camera)
{
    shader.Shader_init("shaders/cube/cube.vs","shaders/cube/cube.fs");

    glCreateVertexArrays(1,&mVAO);
    glBindVertexArray(mVAO); //VAO Binded

        glGenBuffers(1,&mVBO);
        glBindBuffer(GL_ARRAY_BUFFER,mVBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(bufferData),bufferData,GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    int textWidth, textHeight;
    unsigned char* image = SOIL_load_image("container.jpg", &textWidth, &textHeight, 0, SOIL_LOAD_RGB);

    glGenTextures(1,&mTexture);
    glBindTexture(GL_TEXTURE_2D,mTexture);

        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,textWidth,textHeight,0,GL_RGB,GL_UNSIGNED_BYTE,image);
        glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,0);
    SOIL_free_image_data(image);

    mCamera = camera;

    mProjection = mCamera->Projection();

    mModelLoc = glGetUniformLocation(shader.Shader_id(), "model");
    mViewLoc = glGetUniformLocation(shader.Shader_id(), "view");
    mProjectionLoc = glGetUniformLocation(shader.Shader_id(), "projection");
}

Cube::~Cube()
{
    glDeleteBuffers(1,&mVBO);
    glDeleteTextures(1,&mTexture);
    glDeleteVertexArrays(1,&mVAO);
}

void Cube::Draw(glm::mat4 &mModel){
    mView = mCamera->View();

    shader.Shader_bind();
    glUniformMatrix4fv(mViewLoc,1,GL_FALSE,glm::value_ptr(mView));
    glUniformMatrix4fv(mModelLoc,1,GL_FALSE,glm::value_ptr(mModel));
    glUniformMatrix4fv(mProjectionLoc,1,GL_FALSE,glm::value_ptr(mProjection));

    glBindTexture(GL_TEXTURE_2D,mTexture);
    glBindVertexArray(mVAO);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D,0);
    shader.Shader_unbind();
}

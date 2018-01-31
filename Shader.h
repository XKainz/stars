#ifndef SHADER_H
#define SHADER_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#define  GLEW_STATIC
#include <GL/glew.h>

class Shader {
    public:
        Shader();
        Shader( const char* vsFile, const char* fsFile);
        void Shader_init(const char* vsFile, const char* fsFile);
        void Shader_bind();
        void Shader_unbind();
        unsigned int Shader_id();
        ~Shader();

    private:
        unsigned int shader_id;
        unsigned int shader_vp;
        unsigned int shader_fp;
        std::string Shader_textFileRead(const char* file);
};

#endif // SHADER_H

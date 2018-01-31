#ifndef CUBE_H
#define CUBE_H

#include "Shader.h"
#include "Camera.h"
#include "SOIL/SOIL.h"
#include "Display.h"

class Cube
{
    public:
        Cube(Camera* camera);
        virtual ~Cube();
        void Draw(glm::mat4 &mModel);

    private:
        Camera* mCamera;
        GLuint mVBO;
        GLuint mVAO;
        GLuint mTexture;
        Shader shader;
        GLint mModelLoc;
        glm::mat4 mView;
        GLint mViewLoc;
        glm::mat4 mProjection;
        GLint mProjectionLoc;
};

#endif // CUBE_H

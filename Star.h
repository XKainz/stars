#ifndef STAR_H
#define STAR_H

#include "Camera.h"
#include "BinFiles.h"


class Star
{
    public:
        Star(Camera* camera,const char* fPoints,GLuint pointsShader ,const char* fLines,GLuint linesShader);
        virtual ~Star();
        void DrawPoints(int first,int count);
        void DrawPoints();
        void DrawLines();

    protected:

    private:
        Camera* mCamera;
        GLuint mPointsShader;
        GLuint mPointsAO;
        GLint mPointsModelLoc;
        GLint mPointsViewLoc;
        GLint mPointsProjectionLoc;
        GLuint mPointsSize;


        GLuint mLinesShader;
        GLuint mLinesAO;
        GLuint mEBO;
        GLint mLinesModelLoc;
        GLint mLinesViewLoc;
        GLint mLinesProjectionLoc;
        GLuint mLinesSize;

        GLuint mVBO;
        glm::mat4 mModel;
        glm::mat4 mView;
        glm::mat4 mProjection;
};

#endif // BILLBOARD_H

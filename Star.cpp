#include "Star.h"

Star::Star(Camera* camera, const char* fPoints, GLuint pointsShader, const char* fLines, GLuint linesShader){

    mPointsShader = pointsShader;
    mLinesShader = linesShader;
    mPointsSize = readSize(fPoints);
    mLinesSize = readSize(fLines);

    const float* points = readBinaryFileVBO(fPoints);
    const unsigned int* lines = readBinaryFileEBO(fLines);

    glCreateVertexArrays(1,&mPointsAO);
    glBindVertexArray(mPointsAO); //VAO Binded

        glGenBuffers(1,&mVBO);
        glBindBuffer(GL_ARRAY_BUFFER,mVBO);
        glBufferData(GL_ARRAY_BUFFER,mPointsSize,points,GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2*sizeof(GLfloat)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0 );
        glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glCreateVertexArrays(1,&mLinesAO);
    glBindVertexArray(mLinesAO);

        glBindBuffer(GL_ARRAY_BUFFER,mVBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2*sizeof(GLfloat)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0 );
        glEnableVertexAttribArray(1);

        glGenBuffers(1,&mEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,mLinesSize,lines,GL_STATIC_DRAW);

    glBindVertexArray(0);
    delete[] lines;
    lines = NULL;
    delete[] points;
    points = NULL;

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_LINE_SMOOTH);

    mCamera = camera;
    mProjection = mCamera->Projection();

    mPointsModelLoc = glGetUniformLocation(mPointsShader, "model");
    mPointsViewLoc = glGetUniformLocation(mPointsShader, "view");
    mPointsProjectionLoc = glGetUniformLocation(mPointsShader, "projection");
    //std::cout << mPointsModelLoc << " " << mPointsViewLoc << " " << mPointsProjectionLoc << std::endl;

    mLinesModelLoc = glGetUniformLocation(mLinesShader, "model");
    mLinesViewLoc = glGetUniformLocation(mLinesShader, "view");
    mLinesProjectionLoc = glGetUniformLocation(mLinesShader, "projection");
    //std::cout << mLinesModelLoc << " " << mLinesViewLoc << " " << mLinesProjectionLoc << std::endl;
}

Star::~Star()
{
    glDeleteBuffers(1,&mEBO);
    glDeleteVertexArrays(1,&mLinesAO);
    glDeleteBuffers(1,&mVBO);
    glDeleteVertexArrays(1,&mPointsAO);

    glDisable(GL_PROGRAM_POINT_SIZE);
    glDisable(GL_BLEND);
}

void Star::DrawPoints(int first, int count)
{
    mView = mCamera->View();

    glUseProgram(mPointsShader);

    glUniformMatrix4fv(mPointsViewLoc,1,GL_FALSE,glm::value_ptr(mView));
    glUniformMatrix4fv(mPointsModelLoc,1,GL_FALSE,glm::value_ptr(mModel));
    glUniformMatrix4fv(mPointsProjectionLoc,1,GL_FALSE,glm::value_ptr(mProjection));

    glBindVertexArray(mPointsAO);

    glDrawArrays(GL_POINTS,first,count);

    glBindVertexArray(0);
    glUseProgram(0);
}

void Star::DrawLines()
{
    mView = mCamera->View();
    mProjection = mCamera->Projection();

    glUseProgram(mLinesShader);

    glUniformMatrix4fv(mLinesViewLoc,1,GL_FALSE,glm::value_ptr(mView));
    glUniformMatrix4fv(mLinesModelLoc,1,GL_FALSE,glm::value_ptr(mModel));
    glUniformMatrix4fv(mLinesProjectionLoc,1,GL_FALSE,glm::value_ptr(mProjection));

    glBindVertexArray(mLinesAO);

    glDrawElements(GL_LINES,mLinesSize/sizeof(unsigned int),GL_UNSIGNED_INT,0);

    glBindVertexArray(0);
    glUseProgram(0);

}

void Star::DrawPoints()
{
    DrawPoints(0,mPointsSize/(5*sizeof(GLfloat)));
}

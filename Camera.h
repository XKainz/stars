#ifndef CAMERA_H
#define CAMERA_H

#include "Display.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"



class Camera
{
    public:
        Camera(Display* Display,float speed);
        glm::mat4 Update();
        glm::vec3 CameraFront();
        glm::vec3 CameraUp();
        glm::mat4 View();
        glm::mat4 Projection();
        virtual ~Camera();
    private:
        Display* mDisplay;
        glm::mat4 view;
        glm::mat4 projection;
        glm::vec3 mCameraPosition;
        glm::vec3 mCameraObject;
        glm::vec3 mCameraFront;
        glm::vec3 mCameraUp;
        GLfloat mSpeed;
        GLfloat mSensetivity;
        GLfloat mYaw;
        GLfloat mPitch;
};

#endif // CAMERA_H

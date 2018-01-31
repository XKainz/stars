#include "Camera.h"


Camera::Camera(Display* Display,float speed)
{
    mDisplay = Display;
    mSpeed = speed;
    mYaw = -90 ;
    mPitch = 0;
    mSensetivity = 0.1f;
    mCameraPosition   = glm::vec3(0.0f, 0.0f,  0.0f);
    mCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    mCameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    projection = glm::perspective(45.0f, mDisplay->Width / mDisplay->Height , 0.1f , 100.0f);
}

Camera::~Camera()
{
    //dtor
}

glm::mat4 Camera::Update()
{
    projection = glm::perspective(45.0f, mDisplay->Width / mDisplay->Height , 0.1f , 100.0f);
    mYaw = mSensetivity * mDisplay->RelMotionX() + mYaw;
    mPitch = mSensetivity * mDisplay->RelMotionY() + mPitch;
    if( mPitch < -89){
        mPitch = -89;
    }else if(mPitch > 89 ){
        mPitch = 89;
    }
    //*
    glm::vec3 front;
    front.x = cos(glm::radians(mPitch)) * cos(glm::radians(mYaw));
    front.y = sin(glm::radians(mPitch));
    front.z = cos(glm::radians(mPitch)) * sin(glm::radians(mYaw));
    mCameraFront = glm::normalize(front);
    //*/
    if(mDisplay->Right()){
        mCameraPosition += glm::normalize(glm::cross(mCameraFront,mCameraUp)) * mSpeed;
    }
    if(mDisplay->Left()){
        mCameraPosition -= glm::normalize(glm::cross(mCameraFront,mCameraUp)) * mSpeed;
    }
    if(mDisplay->Up()){
        mCameraPosition += mSpeed * mCameraUp;
    }
    if(mDisplay->Down()){
        mCameraPosition -= mSpeed * mCameraUp;
    }
    if(mDisplay->Forward()){
        mCameraPosition += mSpeed * mCameraFront;
    }
    if(mDisplay->Backward()){
        mCameraPosition -= mSpeed * mCameraFront;
    }
    view = glm::lookAt(mCameraPosition,mCameraFront+mCameraPosition,mCameraUp);
    return view;
}

glm::vec3 Camera::CameraFront()
{
    return mCameraFront;
}

glm::vec3 Camera::CameraUp()
{
    return mCameraUp;
}

glm::mat4 Camera::View()
{
    return view;
}

glm::mat4 Camera::Projection(){
    return projection;
}

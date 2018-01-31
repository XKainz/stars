#ifndef DISPLAY_H
#define DISPLAY_H


#include <iostream>
#include <cstdio>
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
class Display
{
    public:
        Display(int width, int height, const std::string& title);
        ~Display();
        void Update();
        bool IsClosed();
        bool Right();
        bool Left();
        bool Up();
        bool Down();
        bool Forward();
        bool Backward();
        int RelMotionX();
        int RelMotionY();
        GLfloat Width;
        GLfloat Height;

    protected:

    private:
        SDL_Window* window;
        SDL_GLContext context;
        void resizeWindow();
        bool isClosed;
        bool mRight;
        bool mLeft;
        bool mUp;
        bool mDown;
        bool mForward;
        bool mBackward;
        bool mEscape;
        int mMotionX;
        int mMotionY;

};

#endif // DISPLAY_H

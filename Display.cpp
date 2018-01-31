#include "Display.h"
Display::Display(int width, int height, const std::string& title)
{
    Width = width;
    Height = height;
    if (SDL_Init(SDL_INIT_EVERYTHING)<0){
        std::cout << "SDL_INIT went wrong" << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    isClosed = false;

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,Width,Height,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
    if (window == 0){
        printf( "Window  could not be created! SDL_Error: %s\n", SDL_GetError() );
    }
    context = SDL_GL_CreateContext(window);
    if (context== 0){
        printf( "Context could not be created! SDL_Error: %s\n", SDL_GetError() );
    }

    mMotionY = 0;
    mMotionX = 0;

    SDL_SetRelativeMouseMode(SDL_TRUE);


    glewExperimental = GL_TRUE;
    glewInit();
    glViewport(0,0,Width,Height);
    glEnable(GL_DEPTH_TEST);

    mRight = false;
    mLeft = false;
    mUp = false;
    mDown = false;
    mForward = false;
    mBackward = false;
    mEscape = false;
}

Display::~Display()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Display::IsClosed()
{
    return isClosed;
}

void Display::Update()
{

    SDL_GL_SwapWindow(window);
    SDL_Event windowEvent;
    mMotionX = 0;
    mMotionY = 0;
    while (SDL_PollEvent (&windowEvent)!= 0){
        if ( windowEvent.type == SDL_QUIT){
            isClosed = true;
        }
        if (windowEvent.type == SDL_WINDOWEVENT){
            switch(windowEvent.window.event){
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                resizeWindow();
                break;
            default:
                break;
            }
        }
        if (!mEscape){
            if (windowEvent.type == SDL_KEYDOWN) {
                switch (windowEvent.key.keysym.sym)
                {
                case SDLK_d:
                    mRight = true;
                    break;
                case SDLK_a:
                    mLeft = true;
                    break;
                case SDLK_w:
                    mForward = true;
                    break;
                case SDLK_s:
                    mBackward = true;
                    break;
                case SDLK_SPACE:
                    mUp = true;
                    break;
                case SDLK_LSHIFT:
                    mDown = true;
                    break;
                case SDLK_ESCAPE:
                    mEscape = true;
                    SDL_SetRelativeMouseMode(SDL_FALSE);
                    break;
                default:
                    break;
                }
            }
            if (windowEvent.type == SDL_KEYUP) {
                switch (windowEvent.key.keysym.sym)
                {
                case SDLK_d:
                    mRight = false;
                    break;
                case SDLK_a:
                    mLeft = false;
                    break;
                case SDLK_w:
                    mForward = false;
                    break;
                case SDLK_s:
                    mBackward = false;
                    break;
                case SDLK_SPACE:
                    mUp = false;
                    break;
                case SDLK_LSHIFT:
                    mDown = false;
                    break;
                default:
                    break;
                }
            }
            if (windowEvent.type == SDL_MOUSEMOTION){
                mMotionX = windowEvent.motion.xrel;
                mMotionY = windowEvent.motion.yrel;
                /*
                std::cout << mMotionX << " " << mMotionY << std::endl;
                //*/
            }
        }else{
            if(windowEvent.type == SDL_KEYDOWN){
                mEscape = false;
                SDL_SetRelativeMouseMode(SDL_TRUE);
            }
        }
    }
}
bool Display::Right(){
    return mRight;
}
bool Display::Left(){
    return mLeft;
}
bool Display::Up()
{
    return mUp;
}
bool Display::Down()
{
    return mDown;
}
bool Display::Forward()
{
    return mForward;
}
bool Display::Backward()
{
    return mBackward;
}
int Display::RelMotionX()
{
    return mMotionX;
}
int Display::RelMotionY()
{
    return mMotionY;
}
void Display::resizeWindow()
{
    int width = 0, height = 0;
    SDL_GetWindowSize(window,&width,&height);
    Width = width;
    Height = height;
    glViewport(0,0,Width,Height);
}


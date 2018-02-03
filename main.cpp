#include "Shader.h"
#include "Camera.h"
#include "Timer.h"
#include "Star.h"
#include "Cube.h"
#include "BinFiles.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

int main(int argc,char* agrs[])
{
    //*
    Display display(1500,800,"The star constellations of Ovid");

    Camera camera(&display,0.1f);

    Shader pointsShader;
    pointsShader.Shader_init("../shaders/star/star.vs","../shaders/star/star.fs");
    Shader linesShader;
    linesShader.Shader_init("../shaders/lines/lines.vs","../shaders/lines/lines.fs");

    Star stars(&camera,"../hygdata_v3/hygdata_v3magspecxyz.csv",pointsShader.Shader_id(),"../hygdata_v3ebo.bin",linesShader.Shader_id());
    Cube cube(&camera);

    LTimer timer;

    while ( !display.IsClosed() ){

            timer.start();

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            camera.Update();

            stars.DrawPoints();
            //stars.DrawLines();


            display.Update();

            int frameTicks = timer.getTicks();
            if( frameTicks < SCREEN_TICKS_PER_FRAME ) {
                    SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
            }
    }
    //*/
    /*/
    std::vector<float> stars = readCSVFileVBO("../hygdata_v3/hygdata_v3magspecxyz.csv",';');
    for(int i(0); i < stars.size(); i++){
        std::cout << stars[i] << std::endl;
    }
    //*/
    return 0;
}


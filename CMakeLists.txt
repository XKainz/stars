cmake_minimum_required(VERSION 3.8)
project(OpenGLPlayground)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Camera.cpp
        Camera.h
        Cube.cpp
        Cube.h
        Display.cpp
        Display.h
        Star.cpp
        Star.h
        BinFiles.cpp
        BinFiles.h
        main.cpp
        Shader.cpp
        Shader.h
        Timer.cpp
        Timer.h)

add_executable(OpenGLPlayground ${SOURCE_FILES})

find_package(GLEW)
find_package(SDL2)
find_package(OpenGL)

include_directories(/usr/include/SOIL)
link_directories(/usr/lib/SOIL)


include_directories(${SOIL_INCLUDE_DIR} $(GLEW_INCLUDE_DIR) $(OPENGL_INCLUDE_DIR) $(SDL2))

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} SOIL)
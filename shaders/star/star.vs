#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in float size;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec3 realposition = position.xyz * 10;
    gl_Position =  projection * view * model* vec4(realposition,1.0f);
    float absoluteSize = pow(10,(size/-5))*10;
    if(absoluteSize<2){
        gl_PointSize = 2;
    }else{
        gl_PointSize = absoluteSize;
    }
}

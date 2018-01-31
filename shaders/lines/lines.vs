#version 330

layout(location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec3 realposition = position.xyz* 10;
    gl_Position =  projection * view * model* vec4(realposition,1.0f);
}

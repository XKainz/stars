#version 330

out vec4 outColor;

void main()
{
    vec2 coord = gl_PointCoord - vec2(0.5);
    float length = dot(coord,coord);
    if(length > 0.25)
        discard;
    outColor = vec4(1.0,1.0,1.0,1.0);
}

#version 330

in  vec2 textureCoord;

out vec4 outColor;

uniform sampler2D ourTexture;
//uniform mat4 view;

void main()
{

    outColor = texture(ourTexture, textureCoord);

    //outColor = vec4(0.5,0.7,0.2,1.0);

}

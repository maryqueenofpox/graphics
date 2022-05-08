//Version number
#version 400
//Layout Qualifer
layout( location = 0 ) out vec4 fragcolor;

 
varying vec2 TexCoords;
uniform sampler2D swordTexture;


void main()
{
    //Setting each vector component to uniform varaible then setting final colour
    fragcolor = texture2D(swordTexture, TexCoords);
}
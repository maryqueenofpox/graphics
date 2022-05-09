#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 2) in vec3 vertexNormal;

attribute vec2 texCoord;

out vec3 normal;
out vec3 fragPosition;

uniform mat4 bananaModel;
uniform mat4 cameraProjection;
uniform mat4 cameraView;

varying vec2 texCoord0;

void main()
{
    normal = vertexNormal; //out vec3 normal for use in .frag script

    fragPosition = vec3(bananaModel * vec4(vertexPosition, 1.0)); //out vec3 fragPosition for use in .frag script

    gl_Position = cameraProjection * cameraView * bananaModel * vec4(vertexPosition, 1.0);

    texCoord0 = texCoord;
}


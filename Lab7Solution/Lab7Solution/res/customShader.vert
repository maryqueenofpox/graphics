#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 2) in vec3 vertexNormal;

attribute vec2 texCoord;

out vec3 fragmentPosition;
out vec3 Position;
out vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

varying vec2 texCoord0;

void main()
{
    normal = vertexNormal;
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
    fragmentPosition = vec3(model * vec4(vertexPosition, 1.0));
    Position = vec3(model * vec4(vertexPosition, 1.0));
    texCoord0 = texCoord;
}
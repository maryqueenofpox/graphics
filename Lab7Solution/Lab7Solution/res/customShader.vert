#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

out vec3 fragmentPosition;
out vec3 Position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
    fragmentPosition = vec3(model * vec4(vertexPosition, 1.0));
    Position = vec3(model * vec4(vertexPosition, 1.0));
}
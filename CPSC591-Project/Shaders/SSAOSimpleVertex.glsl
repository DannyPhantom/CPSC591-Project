#version 410 core

layout (location = 0) in vec3 position_attr;
layout (location = 1) in vec2 texcoords_attr;

out vec2 texCoords;

void main()
{
    gl_Position = vec4(position_attr, 1.0f);
    texCoords = texcoords_attr;
}
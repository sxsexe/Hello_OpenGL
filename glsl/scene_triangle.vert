#version 330 core

layout (location = 0) in vec4 aPosition;
layout (location = 1) in vec4 aColor;

uniform mat4 u_MVP;
out vec4 v_Color;

void main()
{
    gl_Position = aPosition;
    v_Color = aColor;
}
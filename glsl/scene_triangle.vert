#version 330 core

layout (location = 0) in vec4 aPosition;
layout (location = 1) in vec4 aColor;

uniform mat4 u_MVP;
uniform mat4 u_Transform;
out vec4 v_Color;

void main()
{
//    gl_Position = u_Transform * aPosition;
    gl_Position = u_MVP * aPosition;
    v_Color = aColor;
}
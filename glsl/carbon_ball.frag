#version 330 core

in vec4 v_Color;
out vec4 outColor;

uniform float windowWidth;
uniform float windowHeight;

void main()
{
   vec2 coord = gl_PointCoord - vec2(0.5);
   if(length(coord) > 0.5)
        discard;

   outColor = v_Color;
}

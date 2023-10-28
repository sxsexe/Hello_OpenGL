#version 330 core

in vec4 v_Color;
out vec4 outColor;

uniform float time;
uniform int usingTime;
uniform float windowWidth;
uniform float windowHeight;

void main()
{
    float r;
    if(usingTime == 1) {
        float r = gl_FragCoord.x / windowWidth * sin(time);
        float g = gl_FragCoord.x / windowWidth * cos(time);
        outColor.r = r;
        outColor.g = g;
        outColor.b = max((r + g) / 2, 0.3f);
        outColor.a = 1.0;
    } else {
        outColor = v_Color;
    }

}

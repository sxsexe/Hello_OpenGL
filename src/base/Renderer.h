//
// Created by xiaodong.lxd on 2023/10/25.
//

#ifndef OPENGLSTUDY_RENDERER_H
#define OPENGLSTUDY_RENDERER_H

#include "common.h"

class Renderer {

public:

    static void DrawTrianglesEBO(GLsizei count, GLenum type, void * indices);

    static void DrawPoints(GLsizei count, float pointSize);

    static void DrawLinesEBO();

};

void Renderer::DrawTrianglesEBO(GLsizei count, GLenum type, void *indices) {
    GLCall(glDrawElements(GL_TRIANGLES, count, type, indices));
}

void Renderer::DrawPoints(GLsizei count, float pointSize = 10.0f) {
    GLCall(glPointSize(pointSize))
    GLCall(glDrawArrays(GL_POINTS, 0, count));
}

void Renderer::DrawLinesEBO() {

}


#endif //OPENGLSTUDY_RENDERER_H

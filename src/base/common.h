//
// Created by xiaodong.lxd on 2023/10/24.
//

#ifndef OPENGLSTUDY_COMMON_H
#define OPENGLSTUDY_COMMON_H

#include "gui.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <cassert>


#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 1200

#define DELETE_PTR(x) if(x){delete x;x=nullptr;}
#define DELETE_ARRAY_PTR(x) if(x){delete[] x; x=nullptr;}

#define ASSERT(x) assert(x);

#define GLCall(x) glClearErrors(); \
    x;\
    ASSERT(glLogError(#x, __FILE__, __LINE__))

static void glClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

static bool glLogError(const char* function, const char* file, int line) {
    int errorNum = 0;
    while(GLenum error = glGetError()) {
        std::cout << "[OpenGl Error] (" << error << "), " << function << "   " << file << ":" << line << std::endl;
        ++errorNum;
    }

    return errorNum == 0;
}

struct VertexBufferElement {
    uint32_t Type;
    uint32_t Count;
    bool Normalized;

    static uint8_t getTypeSize(uint32_t type) {
        switch (type) {
            case GL_UNSIGNED_INT:
            case GL_FLOAT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
            default:
                return 0;
        }
    }
};

struct Vertex {
    glm::vec4 Pos;                          // 三角形顶点
    glm::vec4 Color;                        // 颜色
    glm::vec2 TexCord;                      // 纹理坐标
    glm::vec3 Normal = {0.0f, 0.0f, 0.0f};  // 法向量

    Vertex(glm::vec4 pos, glm::vec4 color) : Pos(pos), Color(color), TexCord(0.0, 0.0){ }

    static uint32_t getPosSize() {return sizeof(Pos) / sizeof(float); }
    static uint32_t getColorSize() {return sizeof(Color) / sizeof(float); }
    static uint32_t getTextCordSize() {return sizeof(TexCord) / sizeof(float); }
    static uint32_t getNormalSize() {return sizeof(Normal) / sizeof(float); }

};

enum MouseDragDirection {
    DIR_NONE, DIR_UP=1, DIR_DOWN, DIR_LEFT, DIR_RIGHT
};

#endif //OPENGLSTUDY_COMMON_H

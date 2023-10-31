//
// Created by xiaodong.lxd on 2023/10/24.
//

#ifndef OPENGLSTUDY_VERTEXBUFFER_H
#define OPENGLSTUDY_VERTEXBUFFER_H

#include "common.h"

class VertexBuffer {

public:
    VertexBuffer(const void *data, unsigned int size, bool dynamic = false) : mVBO(0) {
        GLCall(glGenBuffers(1, &mVBO));
        std::cout << "Create VertexBuffer mVBO = " << mVBO << std::endl;
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, mVBO));
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
    }
    VertexBuffer(const VertexBuffer& rhs) = delete;
    VertexBuffer& operator=(const VertexBuffer& rhs) = delete;

    ~VertexBuffer() {
        Unbind();
        GLCall(glDeleteBuffers(1, &mVBO));
        std::cout << "Delete VertexBuffer mVBO = " << mVBO << std::endl;
    }

    void Bind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, mVBO));
    }

    void Unbind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void UpdateSubData(const void* data, uint32_t size, uint32_t offset = 0) {
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
    }


private:

    uint32_t mVBO;

};


#endif //OPENGLSTUDY_VERTEXBUFFER_H

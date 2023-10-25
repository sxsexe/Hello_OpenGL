//
// Created by xiaodong.lxd on 2023/10/24.
//

#ifndef OPENGLSTUDY_VERTEXBUFFER_H
#define OPENGLSTUDY_VERTEXBUFFER_H

#include "common.h"

class VertexBuffer {

public:
    VertexBuffer(const void *data, unsigned int size, bool dynamic = false) : mBufferID(0) {
        GLCall(glGenBuffers(1, &mBufferID));
        std::cout << "Create VertexBuffer mBufferID = " << mBufferID << std::endl;
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, mBufferID));
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
    }
    VertexBuffer(const VertexBuffer& rhs) = delete;
    VertexBuffer& operator=(const VertexBuffer& rhs) = delete;

    ~VertexBuffer() {
        Unbind();
        GLCall(glDeleteBuffers(1, &mBufferID));
        std::cout << "Delete VertexBuffer mBufferID = " << mBufferID << std::endl;
    }

    void Bind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, mBufferID));
    }

    void Unbind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void UpdateSubData(const void* data, uint32_t size, uint32_t offset = 0) {
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
    }


private:

    uint32_t mBufferID;

};


#endif //OPENGLSTUDY_VERTEXBUFFER_H

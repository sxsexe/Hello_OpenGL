//
// Created by xiaodong.lxd on 2023/10/25.
//

#ifndef OPENGLSTUDY_INDEXBUFFER_H
#define OPENGLSTUDY_INDEXBUFFER_H

#include "common.h"


class IndexBuffer {

public:
    /**
     *
     * @param data
     * @param count index个数，不是bytes
     */
    IndexBuffer(const unsigned int *data, int count) {
        GLCall(glGenBuffers(1, &mIBO));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
        std::cout << "Create IndexBuffer mIBO = " << mIBO << std::endl;
    }
    IndexBuffer(const IndexBuffer& rhs) = delete;
    IndexBuffer& operator=(const IndexBuffer& rhs) = delete;

    ~IndexBuffer(){
        Unbind();
        GLCall(glDeleteBuffers(1, &mIBO));
        std::cout << "Delete IndexBuffer mIBO = " << mIBO << std::endl;
    }

    void Bind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO));
    }

    void Unbind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    inline int getIbo() const { return mIBO; }

private:
    unsigned int mIBO;

};

#endif //OPENGLSTUDY_INDEXBUFFER_H

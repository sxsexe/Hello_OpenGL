//
// Created by xiaodong.lxd on 2023/10/25.
//

#ifndef OPENGLSTUDY_ELEMENTARRAYBUFFER_H
#define OPENGLSTUDY_ELEMENTARRAYBUFFER_H

#include "common.h"


class ElementArrayBuffer {

public:
    /**
     *
     * @param data
     * @param count index个数，不是bytes
     */
    ElementArrayBuffer(const unsigned int *data, int count) {
        GLCall(glGenBuffers(1, &mEBO));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
        std::cout << "Create ElementArrayBuffer mEBO = " << mEBO << std::endl;
    }
    ElementArrayBuffer(const ElementArrayBuffer& rhs) = delete;
    ElementArrayBuffer& operator=(const ElementArrayBuffer& rhs) = delete;

    ~ElementArrayBuffer(){
        Unbind();
        GLCall(glDeleteBuffers(1, &mEBO));
        std::cout << "Delete ElementArrayBuffer mEBO = " << mEBO << std::endl;
    }

    void Bind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO));
    }

    void Unbind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    inline int getIbo() const { return mEBO; }

private:
    unsigned int mEBO;

};

#endif //OPENGLSTUDY_ELEMENTARRAYBUFFER_H

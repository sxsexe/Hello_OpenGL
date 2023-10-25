//
// Created by xiaodong.lxd on 2023/10/25.
//

#ifndef OPENGLSTUDY_VERTEXARRAY_H
#define OPENGLSTUDY_VERTEXARRAY_H


#include "common.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {

public:

    VertexArray(const VertexArray& rhs) = delete;
    VertexArray& operator=(const VertexArray& rhs) = delete;

    VertexArray() {
        GLCall(glGenVertexArrays(1, &mVAO));
        std::cout << "Create VertexArray mVAO = " << mVAO << std::endl;
    }

    ~VertexArray() {
        Unbind();
        GLCall(glDeleteVertexArrays(1, &mVAO));
        std::cout << "Delete VertexArray mVAO = " << mVAO << std::endl;
    }

    void Bind() {
        GLCall(glBindVertexArray(mVAO));
    }

    void Unbind() {
        GLCall(glBindVertexArray(0));
    }

    void AddVertexBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {

        this->Bind();
        vb.Bind();

        const auto &elements = layout.getElements();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); i++) {
            const auto& element = elements[i];

            GLCall(glEnableVertexAttribArray(i));
            GLCall(glVertexAttribPointer(i, element.Count, element.Type,
                                         element.Normalized ? GL_TRUE : GL_FALSE,
                                         layout.getStride(), (GLvoid *)offset));

            offset += element.Count * VertexBufferElement::getTypeSize(element.Type);
        }

    }

private:
    uint32_t mVAO;
};

#endif //OPENGLSTUDY_VERTEXARRAY_H

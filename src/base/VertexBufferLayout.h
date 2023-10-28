//
// Created by xiaodong.lxd on 2023/10/25.
//

#ifndef OPENGLSTUDY_VERTEXBUFFERLAYOUT_H
#define OPENGLSTUDY_VERTEXBUFFERLAYOUT_H

#include <vector>
#include "common.h"

class VertexBufferLayout {

public:
    VertexBufferLayout() : mStride(0) {};
    ~VertexBufferLayout(){}
    VertexBufferLayout (const VertexBufferLayout& rhs) = delete;
    VertexBufferLayout& operator=(const VertexBufferLayout& rhs) = delete;

    template<typename T>
    void push (uint32_t count) {}

    template<>
    void push<float> (uint32_t count) {
        mElements.push_back({GL_FLOAT, count, false});
        mStride += count * VertexBufferElement::getTypeSize(GL_FLOAT);
    }

    template<>
    void push<unsigned int> (uint32_t count) {
        mElements.push_back({GL_UNSIGNED_INT, count, false});
        mStride += count * VertexBufferElement::getTypeSize(GL_UNSIGNED_INT);
    }

    template<>
    void push<unsigned char> (uint32_t count) {
        mElements.push_back({GL_UNSIGNED_BYTE, count, false});
        mStride += count * VertexBufferElement::getTypeSize(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferElement> getElements() const { return mElements; }

    inline int getStride() const { return mStride; }

    static void makeDefaultLayout(VertexBufferLayout& layout){
        layout.push<float>(Vertex::getPosSize());
        layout.push<float>(Vertex::getColorSize());
        layout.push<float>(Vertex::getTextCordSize());
        layout.push<float>(Vertex::getNormalSize());
    }

private:
    int mStride;
    std::vector<VertexBufferElement> mElements;

};




#endif //OPENGLSTUDY_VERTEXBUFFERLAYOUT_H

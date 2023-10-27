//
// Created by xiaodong.lxd on 2023/10/26.
//

#ifndef OPENGLSTUDY_BASESHAPE_H
#define OPENGLSTUDY_BASESHAPE_H

#include <iostream>
#include <vector>
#include "common.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Color.h"

class BaseShape {

public:

    BaseShape(): mVA(nullptr), mVB(nullptr), mIB(nullptr), mVertexData(nullptr), mIndexData(nullptr), indexCount(0) {

    };
    virtual ~BaseShape() {
        DELETE_PTR(mIB);
        DELETE_PTR(mVA);
        DELETE_PTR(mVB);
        DELETE_ARRAY_PTR(mIndexData);
        DELETE_ARRAY_PTR(mVertexData);
    };

    virtual void Draw(double delta) = 0;

protected:

    std::vector<Vertex> mVertexVector;
    std::vector<GLuint> mIndexVector;
    float* mVertexData;
    GLuint* mIndexData;
    uint32_t indexCount = 0;

    VertexArray *mVA;
    VertexBuffer *mVB;
    IndexBuffer *mIB;

};


#endif //OPENGLSTUDY_BASESHAPE_H

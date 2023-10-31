//
// Created by xiaodong.lxd on 2023/10/26.
//

#ifndef OPENGLSTUDY_BASESHAPE_H
#define OPENGLSTUDY_BASESHAPE_H

#include <iostream>
#include <vector>
#include "common.h"
#include "ElementArrayBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Color.h"
#include "Renderer.h"
#include "ShaderProxy.h"

enum ShapeType {
    S_NONE = 0, S_Triangle = 1, S_Cylinder = 2, S_Torus = 3, S_CarbonBall = 4
};

class BaseShape {

public:

    BaseShape() : mVAO(nullptr), mVBO(nullptr), mEBO(nullptr), mVertexData(nullptr), mIndexData(nullptr), indexCount(0),
                  mType(S_NONE), mShaderProxy(nullptr) {
    };

    virtual ~BaseShape() {
        DELETE_PTR(mShaderProxy);
        DELETE_PTR(mEBO);
        DELETE_PTR(mVAO);
        DELETE_PTR(mVBO);
        DELETE_ARRAY_PTR(mIndexData);
        DELETE_ARRAY_PTR(mVertexData);
    };

    virtual void Draw(double delta) = 0;

    inline ShapeType getType() { return mType; }

    inline ShaderProxy* getShader() {
        return mShaderProxy;
    }

    virtual void SetupShader(glm::mat4 mvp) {}

protected:

    std::vector<Vertex> mVertexVector;
    std::vector<GLuint> mIndexVector;
    float *mVertexData;
    GLuint *mIndexData;
    uint32_t indexCount = 0;

    VertexArray *mVAO;
    VertexBuffer *mVBO;
    ElementArrayBuffer *mEBO;

    ShapeType mType;

    ShaderProxy *mShaderProxy;
};


#endif //OPENGLSTUDY_BASESHAPE_H

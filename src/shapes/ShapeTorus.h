//
// Created by xiaodong.lxd on 2023/10/28.
//

#ifndef OPENGLSTUDY_SHAPETORUS_H
#define OPENGLSTUDY_SHAPETORUS_H

#include "BaseShape.h"

class ShapeTorus : public BaseShape {

public:
    ShapeTorus() {
        std::cout << "Create ShapeTorus" << std::endl;
        mType = S_Torus;

        // P(x, y , z) =
        float A = 0.15f;
        float D = 1.0f;

        const int circleCount = 64;
        const int circlePointCount = 64;
        // 用于画小圆的角度
        float INNER_ANGLE = 360.0f / circlePointCount;
        float OUTER_ANGLE = 360.0f / circleCount;
        float a = 0;
        float u = 0;

        for (int k = 0; k < circleCount; k++) {
            float ru = glm::radians(u);

            for (int i = 0; i < circlePointCount; i++) {
                float ra = glm::radians(a);
                float x = (D + A * glm::sin(ra)) * glm::sin(ru);
                float y = A * glm::cos(ra);
                float z = (D + A * glm::sin(ra)) * glm::cos(ru);
                mVertexVector.push_back(Vertex({x, y, z}));
                a += INNER_ANGLE;
            }
            u += OUTER_ANGLE;
        }

        for (int i = 0; i < circleCount; i++) {

            int c = i * circlePointCount;
            int n = i == (circleCount - 1) ? 0 : (i + 1) * circlePointCount;

            for (int k = 0; k < circlePointCount; k++) {
                if (k != (circlePointCount -1)) {
                    mIndexVector.push_back(c + k);
                    mIndexVector.push_back(n + k);
                    mIndexVector.push_back(n + 1 + k);
                    mIndexVector.push_back(n + 1 + k);
                    mIndexVector.push_back(c + 1 + k);
                    mIndexVector.push_back(c + k);
                } else {
                    mIndexVector.push_back(c + k);
                    mIndexVector.push_back(n + k);
                    mIndexVector.push_back(n);
                    mIndexVector.push_back(n);
                    mIndexVector.push_back(c);
                    mIndexVector.push_back(c + k);
                }
            }
        }

        indexCount = mIndexVector.size();
        mIndexData = new GLuint[indexCount * sizeof(GLuint)];
        memcpy(mIndexData, &mIndexVector[0], indexCount * sizeof(GLuint));
        mEBO = new ElementArrayBuffer(mIndexData, indexCount);

        mVertexData = new float[mVertexVector.size() * sizeof(Vertex)];
        memcpy(mVertexData, &mVertexVector[0], mVertexVector.size() * sizeof(Vertex));
        // dynamic update data
        mVBO = new VertexBuffer(nullptr, mVertexVector.size() * sizeof(Vertex), true);

        mVAO = new VertexArray();
        mVAO->Bind();
        VertexBufferLayout layout;
        VertexBufferLayout::makeDefaultLayout(layout);
        mVAO->AddVertexBuffer(*mVBO, layout);
    }

    ~ShapeTorus() override {
        std::cout << "Delete ShapeTorus" << std::endl;
    }


    void Draw(double delta) override {
        mVAO->Bind();
        mEBO->Bind();
        mVBO->Bind();
        mVBO->UpdateSubData(mVertexData, mVertexVector.size() * sizeof(Vertex));

        Renderer::DrawTrianglesEBO(indexCount, GL_UNSIGNED_INT, nullptr);
    }


};

#endif //OPENGLSTUDY_SHAPETORUS_H

//
// Created by xiaodong.lxd on 2023/10/27.
//

#ifndef OPENGLSTUDY_SHAPETRIANGLE_H
#define OPENGLSTUDY_SHAPETRIANGLE_H

#include "BaseShape.h"

class ShapeTriangle : public BaseShape {

public:

    ShapeTriangle() {
        std::cout << "Create ShapeTriangle" << std::endl;

        mType = S_Triangle;

        float size = 0.8f;
        mVertexVector.push_back({glm::vec4(-size, -size, +size, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}); // left bottom
        mVertexVector.push_back({glm::vec4(+size, -size, +size, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}); // right bottom
        mVertexVector.push_back({glm::vec4(+0.0f, -size, -size, 1.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)}); // back
        mVertexVector.push_back({glm::vec4(+0.0f, +size, +0.0f, 1.0f), glm::vec4(0.4f, 0.3f, 0.5f, 1.0f)}); // top

        mVertexData = new float[mVertexVector.size() * sizeof(Vertex)];

        //index array
        const uint32_t indexGroupCount = 4;
        indexCount = indexGroupCount * 3;
        mIndexData = new GLuint[indexCount];

        uint32_t i = 0;
        // front
        mIndexData[i++] = 0;
        mIndexData[i++] = 1;
        mIndexData[i++] = 3;
        // right
        mIndexData[i++] = 1;
        mIndexData[i++] = 2;
        mIndexData[i++] = 3;
        // left
        mIndexData[i++] = 2;
        mIndexData[i++] = 0;
        mIndexData[i++] = 3;
        // bottom
        mIndexData[i++] = 0;
        mIndexData[i++] = 1;
        mIndexData[i++] = 2;

        mVB = new VertexBuffer(nullptr, mVertexVector.size() * sizeof(Vertex), true);
        mIB = new IndexBuffer(mIndexData, indexCount);

        mVA = new VertexArray();
        mVA->Bind();
        VertexBufferLayout layout;
        VertexBufferLayout::makeDefaultLayout(layout);
        mVA->AddVertexBuffer(*mVB, layout);

        memcpy(mVertexData, &mVertexVector[0], mVertexVector.size() * sizeof(Vertex));
    }

    void Draw(double delta) override {
        mVA->Bind();
        mIB->Bind();
        mVB->Bind();
        mVB->UpdateSubData(mVertexData, mVertexVector.size() * sizeof(Vertex));

        GLCall(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));
    }

    ~ShapeTriangle() override {
        std::cout << "Delete ShapeTriangle" << std::endl;
    }

};

#endif //OPENGLSTUDY_SHAPETRIANGLE_H

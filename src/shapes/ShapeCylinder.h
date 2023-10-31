//
// Created by xiaodong.lxd on 2023/10/27.
//

#ifndef OPENGLSTUDY_SHAPECYLINDER_H
#define OPENGLSTUDY_SHAPECYLINDER_H

#include "BaseShape.h"

class ShapeCylinder  : public BaseShape {

public:
    ShapeCylinder() {
        std::cout << "Create ShapeCylinder" << std::endl;
        mType = S_Cylinder;

        std::vector<Vertex> vertexTop;
        std::vector<Vertex> vertexBottom;

        float radius = 0.8f;
        const int divideCount = 10;
        const float y = 0.9f;
        float angleE = 90.0f / divideCount;
        float angle = 0.0f;

        glm::vec4 colorTop = Color::getRandomColor().getColorVec4();
        glm::vec4 colorBottom = Color::getRandomColor().getColorVec4();
//        glm::vec4 colorTop = Color(1.0f, 0.0f, 0.0f).getColorVec4();
//        glm::vec4 colorBottom = Color(0.0f, 0.0f, 1.0f).getColorVec4();

        for(uint8_t i = 0; i < divideCount; i++) {
            float radians = glm::radians(angle);
            float x = radius * glm::cos(radians);
            float z = -radius * glm::sin(radians);

            vertexTop.push_back({glm::vec4(x, y, z, 1.0f), colorTop});
            vertexBottom.push_back({glm::vec4(x, -y, z, 1.0f), colorBottom});
            angle += angleE;
        }

        for(uint8_t i = 0; i < divideCount; i++) {
            float radians = glm::radians(angle);
            float x = radius * glm::cos(radians);
            float z = -radius * glm::sin(radians);

            vertexTop.push_back({glm::vec4(x, y, z, 1.0f), colorTop});
            vertexBottom.push_back({glm::vec4(x, -y, z, 1.0f), colorBottom});
            angle += angleE;
        }
        for(uint8_t i = 0; i < divideCount; i++) {
            float radians = glm::radians(angle);
            float x = radius * glm::cos(radians);
            float z = -radius * glm::sin(radians);

            vertexTop.push_back({glm::vec4(x, y, z, 1.0f), colorTop});
            vertexBottom.push_back({glm::vec4(x, -y, z, 1.0f), colorBottom});
            angle += angleE;
        }
        for(uint8_t i = 0; i < divideCount; i++) {
            float radians = glm::radians(angle);
            float x = radius * glm::cos(radians);
            float z = -radius * glm::sin(radians);

            vertexTop.push_back({glm::vec4(x, y, z, 1.0f), colorTop});
            vertexBottom.push_back({glm::vec4(x, -y, z, 1.0f), colorBottom});
            angle += angleE;
        }
        mVertexVector.insert(mVertexVector.end(), vertexTop.begin(), vertexTop.end());
        mVertexVector.insert(mVertexVector.end(), vertexBottom.begin(), vertexBottom.end());
        mVertexVector.push_back({glm::vec4(0.0f, 2.5f, 0.0f, 1.0f), colorBottom});
        mVertexVector.push_back({glm::vec4(0.0f, -1.5f, 0.0f, 1.0f), colorTop});

        int iSize = vertexTop.size();
        for(int i = 0; i<iSize; i++) {
            if(i == (iSize - 1)) {
                //connect the first vertex
                mIndexVector.push_back(i);
                mIndexVector.push_back(0);
                mIndexVector.push_back(i + iSize);
                mIndexVector.push_back(i + iSize);
                mIndexVector.push_back(0);
                mIndexVector.push_back(iSize);
            } else{
                mIndexVector.push_back(i);
                mIndexVector.push_back(i + 1);
                mIndexVector.push_back(i + iSize);
                mIndexVector.push_back(i + iSize);
                mIndexVector.push_back(i + 1);
                mIndexVector.push_back(i + iSize + 1);
            }
        }
        int topCenterVertexIndex = iSize * 2;
        int bottomCenterVertexIndex = topCenterVertexIndex + 1 ;
        for(int i = 0; i<iSize; i++) {
            mIndexVector.push_back(topCenterVertexIndex);
            mIndexVector.push_back(i);
            if(i == (iSize - 1)) {
                mIndexVector.push_back(0);
            } else {
                mIndexVector.push_back(i + 1);
            }
        }
        for(int i = 0; i<iSize; i++) {
            mIndexVector.push_back(bottomCenterVertexIndex);
            mIndexVector.push_back(i + iSize);
            if(i == (iSize - 1)) {
                mIndexVector.push_back(iSize);
            } else {
                mIndexVector.push_back(iSize + i + 1);
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

    ~ShapeCylinder() override {
        std::cout << "Delete ShapeCylinder" << std::endl;
    }
    void Draw(double delta) override {
        mVAO->Bind();
        mEBO->Bind();
        mVBO->Bind();
        mVBO->UpdateSubData(mVertexData, mVertexVector.size() * sizeof(Vertex));

        Renderer::DrawTrianglesEBO(indexCount, GL_UNSIGNED_INT, nullptr);
    }

};

#endif //OPENGLSTUDY_SHAPECYLINDER_H

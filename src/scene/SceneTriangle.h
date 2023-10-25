//
// Created by xiaodong.lxd on 2023/10/25.
//

#ifndef OPENGLSTUDY_SCENETRIANGLE_H
#define OPENGLSTUDY_SCENETRIANGLE_H


#include "BaseScene.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include <vector>

class SceneTriangle : public BaseScene {

public:
    SceneTriangle() {
        std::cout << "Create SceneTriangle"<< std::endl;

        float size = 0.8f;
        mVertexVector.push_back({glm::vec4(-size, +0.0f, +size, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}); // left bottom
        mVertexVector.push_back({glm::vec4(+size, +0.0f, +size, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}); // right bottom
        mVertexVector.push_back({glm::vec4(+0.0f, +0.0f, -size, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}); // back
        mVertexVector.push_back({glm::vec4(+0.0f, +size, +0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}); // top

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


        mVA = new VertexArray();
        mVA->Bind();
        VertexBufferLayout layout;
        layout.push<float>(Vertex::getPosSize());
        layout.push<float>(Vertex::getColorSize());
        layout.push<float>(Vertex::getTextCordSize());
        layout.push<float>(Vertex::getNormalSize());

        mVB = new VertexBuffer(nullptr, mVertexVector.size() * sizeof(Vertex), true);
        mIB = new IndexBuffer(mIndexData, indexCount);
        mVA->AddVertexBuffer(*mVB, layout);

        int iVertexSize = sizeof(Vertex);
        memcpy(mVertexData, &mVertexVector[0], mVertexVector.size() * iVertexSize);
    }
    SceneTriangle (const SceneTriangle& rhs) = delete;
    SceneTriangle& operator=(const SceneTriangle& rhs) = delete;

    ~SceneTriangle() override {
        delete[] mIndexData;
        delete[] mVertexData;
        delete mIB;
        delete mVA;
        delete mVB;
        std::cout << "Delete SceneTriangle"<< std::endl;
    }

    void OnEnter() override {
        BaseScene::OnEnter();
    }

    void OnExit() override {
        BaseScene::OnExit();
    }

    void Draw(double delta) override {

        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        mVA->Bind();
        mIB->Bind();
        mVB->Bind();

        mVB->UpdateSubData(mVertexData, mVertexVector.size() * sizeof(Vertex));
        GLCall(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));
    }

private:
    std::vector<Vertex> mVertexVector;
    float* mVertexData;
    GLuint* mIndexData;
    int indexCount;

    VertexArray *mVA;
    VertexBuffer *mVB;
    IndexBuffer *mIB;

    glm::mat4 mProj;
    glm::mat4 mView;
    glm::mat4 mModel;
    glm::mat4 mMVP;

};


#endif //OPENGLSTUDY_SCENETRIANGLE_H

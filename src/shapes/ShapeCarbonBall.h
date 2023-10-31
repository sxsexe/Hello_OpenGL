//
// Created by xiaodong.lxd on 2023/10/31.
//

#ifndef OPENGLSTUDY_SHAPECARBONBALL_H
#define OPENGLSTUDY_SHAPECARBONBALL_H

#include "BaseShape.h"

class ShapeCarbonBall : public BaseShape {

public:
    ShapeCarbonBall() {
        std::cout << "Create ShapeCarbonBall" << std::endl;

        mType = S_CarbonBall;

        float size = 0.8f;
        mVertexVector.push_back({glm::vec4(-size, -size, +size, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}); // left bottom
        mVertexVector.push_back({glm::vec4(+size, -size, +size, 1.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)}); // right bottom
        mVertexVector.push_back({glm::vec4(+0.0f, -size, -size, 1.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)}); // back
        mVertexVector.push_back({glm::vec4(+0.0f, +size, +0.0f, 1.0f), glm::vec4(0.4f, 0.3f, 0.5f, 1.0f)}); // top

        mVertexData = new float[mVertexVector.size() * sizeof(Vertex)];
        memcpy(mVertexData, &mVertexVector[0], mVertexVector.size() * sizeof(Vertex));
        // dynamic update data
        mVBO = new VertexBuffer(nullptr, mVertexVector.size() * sizeof(Vertex), true);

        mVAO = new VertexArray();
        mVAO->Bind();
        VertexBufferLayout layout;
        VertexBufferLayout::makeDefaultLayout(layout);
        mVAO->AddVertexBuffer(*mVBO, layout);


        mShaderProxy = new ShaderProxy("E:\\OpenGLWorld\\Projects\\OpenGLStudy\\glsl\\baseshape.vert",
                                       "E:\\OpenGLWorld\\Projects\\OpenGLStudy\\glsl\\carbon_ball.frag");

    }


    ~ShapeCarbonBall() override {
        std::cout << "Delete ShapeCarbonBall" << std::endl;
    }

    void Draw(double delta) override {
        mVAO->Bind();
        mVBO->Bind();
        mVBO->UpdateSubData(mVertexData, mVertexVector.size() * sizeof(Vertex));

        Renderer::DrawPoints(mVertexVector.size(), 50);
    }

    void SetupShader(glm::mat4 mvp) override {
        mShaderProxy->Bind();
        mShaderProxy->setUniformMat4f("u_MVP", mvp);
    }


};

#endif //OPENGLSTUDY_SHAPECARBONBALL_H

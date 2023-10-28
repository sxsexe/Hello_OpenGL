//
// Created by xiaodong.lxd on 2023/10/25.
//

#ifndef OPENGLSTUDY_SCENETRIANGLE_H
#define OPENGLSTUDY_SCENETRIANGLE_H


#include "BaseScene.h"
#include "../shapes/BaseShape.h"
#include "../shapes/ShapeTriangle.h"


#include <vector>

class SceneTriangle : public BaseScene {

public:
    SceneTriangle() : mShape(nullptr) {
        std::cout << "Create SceneTriangle"<< std::endl;

        mShader = new ShaderProxy("E:\\OpenGLWorld\\Projects\\OpenGLStudy\\glsl\\baseshape.vert", "E:\\OpenGLWorld\\Projects\\OpenGLStudy\\glsl\\baseshape.frag");
        mShape = new ShapeTriangle();

    }
    SceneTriangle (const SceneTriangle& rhs) = delete;
    SceneTriangle& operator=(const SceneTriangle& rhs) = delete;

    ~SceneTriangle() override {
        DELETE_PTR(mShape);
        std::cout << "Delete SceneTriangle"<< std::endl;
    }

    void OnEnter() override {
        BaseScene::OnEnter();
    }

    void OnExit() override {
        BaseScene::OnExit();
    }

    void Draw(double delta) override {

        GLCall(glClearColor(0.2f, 0.2f, 0.4f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLCall(glEnable(GL_DEPTH_TEST));

        mShader->Bind();
        mMVP = mProj * mCamera->getCameraViewMatrix() * mModel;
        mShader->setUniformMat4f("u_MVP", mMVP);

        mShape->Draw(delta);
    }

    void OnMouseDrag(MouseDragDirection directionX, MouseDragDirection directionY) override {
        BaseScene::OnMouseDrag(directionX, directionY);
    }

private:
    BaseShape* mShape;

};


#endif //OPENGLSTUDY_SCENETRIANGLE_H

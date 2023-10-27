//
// Created by xiaodong.lxd on 2023/10/26.
//

#ifndef OPENGLSTUDY_GEOMETRYSCENE_H
#define OPENGLSTUDY_GEOMETRYSCENE_H

#include "BaseScene.h"
#include "src/shapes/ShapeCylinder.h"

class GeometryScene : public BaseScene {


public:
    GeometryScene (const GeometryScene& rhs) = delete;
    GeometryScene& operator=(const GeometryScene& rhs) = delete;

    GeometryScene() : mShape(nullptr) {
        std::cout << "Create GeometryScene"<< std::endl;

        mShader = new ShaderProxy("E:\\OpenGLWorld\\Projects\\OpenGLStudy\\glsl\\baseshape.vert", "E:\\OpenGLWorld\\Projects\\OpenGLStudy\\glsl\\baseshape.frag");
        mCamera = new Camera();

        mShape = new ShapeCylinder();
    }

    ~GeometryScene() override{
        DELETE_PTR(mShape);
        std::cout << "Delete GeometryScene"<< std::endl;
    }

    void OnEnter() override {
        BaseScene::OnEnter();
    }

    void OnExit() override {
        BaseScene::OnExit();
    }

    void Draw(double delta) override {

        GLCall(glClearColor(0.5f, 0.5f, 0.5f, 1.0f));
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

#endif //OPENGLSTUDY_GEOMETRYSCENE_H

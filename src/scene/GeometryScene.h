//
// Created by xiaodong.lxd on 2023/10/26.
//

#ifndef OPENGLSTUDY_GEOMETRYSCENE_H
#define OPENGLSTUDY_GEOMETRYSCENE_H

#include "BaseScene.h"
#include "src/shapes/ShapeCylinder.h"
#include "../shapes/ShapeTorus.h"
#include "../shapes/ShapePoints.h"

class GeometryScene : public BaseScene {


public:
    GeometryScene (const GeometryScene& rhs) = delete;
    GeometryScene& operator=(const GeometryScene& rhs) = delete;

    GeometryScene() : mShape(nullptr) {
        std::cout << "Create GeometryScene" << std::endl;

        mShader = new ShaderProxy("E:\\OpenGLWorld\\Projects\\OpenGLStudy\\glsl\\baseshape.vert",
                                  "E:\\OpenGLWorld\\Projects\\OpenGLStudy\\glsl\\baseshape.frag");
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



        CreateShapeByType();
        if(mShape) {

            mMVP = mProj * mCamera->getCameraViewMatrix() * mModel;
            if(mShape->getShader()) {
                // use specified shader
                mShape->SetupShader(mMVP);
            } else {
                mShader->Bind();
                mShader->setUniformMat4f("u_MVP", mMVP);

                double time = glfwGetTime();
                mShader->setUniform1i("usingTime", 1);
                mShader->setUniform1f("time", time);
                mShader->setUniform1f("windowWidth", WINDOW_WIDTH);
                mShader->setUniform1f("windowHeight", WINDOW_HEIGHT);
            }
            mShape->Draw(delta);
        }

        DrawGUI();
    }

    void DrawGUI() override {
        ImGui::Begin("OpenGL SubEntries");

        ImGui::RadioButton("Cylinders", &sCurrentType, S_Cylinder);
        ImGui::RadioButton("Triangles", &sCurrentType, S_Triangle);
        ImGui::RadioButton("Torus", &sCurrentType, S_Torus);
        ImGui::RadioButton("CarbonBall", &sCurrentType, S_Points);

        ImGui::End();
    }

private:
    BaseShape* mShape;

    void CreateShapeByType() {
        if(mShape == nullptr) {
            if(sCurrentType == S_Triangle) {
                mShape = new ShapeTriangle();
            }
            if(sCurrentType == S_Cylinder) {
                mShape = new ShapeCylinder();
            }
            if(sCurrentType == S_Torus) {
                mShape = new ShapeTorus();
            }
            if(sCurrentType == S_Points) {
                mShape = new ShapePoints();
            }

        } else {
            if(mShape->getType() != S_Triangle && sCurrentType == S_Triangle) {
                DELETE_PTR(mShape);
                mShape = new ShapeTriangle();
            }
            if(mShape->getType() != S_Cylinder && sCurrentType == S_Cylinder) {
                DELETE_PTR(mShape);
                mShape = new ShapeCylinder();
            }
            if(mShape->getType() != S_Torus && sCurrentType == S_Torus) {
                DELETE_PTR(mShape);
                mShape = new ShapeTorus();
            }

            if(mShape->getType() != S_Points && sCurrentType == S_Points) {
                DELETE_PTR(mShape);
                mShape = new ShapePoints();
            }
        }
    }

public:
    static int sCurrentType;

};

int GeometryScene::sCurrentType = 0;

#endif //OPENGLSTUDY_GEOMETRYSCENE_H

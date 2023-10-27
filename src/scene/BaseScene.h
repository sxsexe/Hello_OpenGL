//
// Created by xiaodong.lxd on 2023/10/25.
//

#ifndef OPENGLSTUDY_BASESCENE_H
#define OPENGLSTUDY_BASESCENE_H

#include "common.h"
#include "ShaderProxy.h"
#include "Camera.h"

class BaseScene {

public:
    BaseScene(): mShader(nullptr), mCamera(nullptr) {};
    virtual ~BaseScene() {
        DELETE_PTR(mShader);
        DELETE_PTR(mCamera);
    };
    BaseScene (const BaseScene& rhs) = delete;
    BaseScene& operator=(const BaseScene& rhs) = delete;

    virtual void Draw(double delta) = 0;
    virtual void OnEnter() { InUse = true; };
    virtual void OnExit() { InUse = false; };
    inline bool CanDraw() const { return InUse; }

    virtual void OnScroll(double xOffset, double yOffset) {
        std::cout << "OnScroll xOffset="<<xOffset<< ", yOffset=" << yOffset<< std::endl;
        if(yOffset > 0) {
            mCamera->ZoomIn();
        } else if(yOffset < 0) {
            mCamera->ZoomOut();
        }
    }

    virtual void OnKey(MouseDragDirection directionX, MouseDragDirection directionY) {
        auto angle = 5.0f;
        if(directionX == MouseDragDirection::DIR_LEFT) {
            mModel =  glm::rotate(mModel, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
            if(directionY == DIR_UP) {
                mModel =  glm::rotate(mModel, glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
            } else if(directionY == DIR_DOWN) {
                mModel =  glm::rotate(mModel, glm::radians(-angle), glm::vec3(1.0, 0.0, 0.0));
            }
        } else if(directionX == MouseDragDirection::DIR_RIGHT) {
            mModel =  glm::rotate(mModel, glm::radians(-angle), glm::vec3(0.0, 1.0, 0.0));
            if(directionY == DIR_UP) {
                mModel =  glm::rotate(mModel, glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
            } else if(directionY == DIR_DOWN) {
                mModel =  glm::rotate(mModel, glm::radians(-angle), glm::vec3(1.0, 0.0, 0.0));
            }
        } else {
            if(directionY == DIR_UP) {
                mModel =  glm::rotate(mModel, glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
            } else if(directionY == DIR_DOWN) {
                mModel =  glm::rotate(mModel, glm::radians(-angle), glm::vec3(1.0, 0.0, 0.0));
            }
        }
    }

    virtual void OnMouseDrag(MouseDragDirection directionX, MouseDragDirection directionY){
        auto angle = 2.0f;
        if(directionX == MouseDragDirection::DIR_LEFT) {
            mModel =  glm::rotate(mModel, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
            if(directionY == DIR_UP) {
                mModel =  glm::rotate(mModel, glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
            } else if(directionY == DIR_DOWN) {
                mModel =  glm::rotate(mModel, glm::radians(-angle), glm::vec3(1.0, 0.0, 0.0));
            }
        } else if(directionX == MouseDragDirection::DIR_RIGHT) {
            mModel =  glm::rotate(mModel, glm::radians(-angle), glm::vec3(0.0, 1.0, 0.0));
            if(directionY == DIR_UP) {
                mModel =  glm::rotate(mModel, glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
            } else if(directionY == DIR_DOWN) {
                mModel =  glm::rotate(mModel, glm::radians(-angle), glm::vec3(1.0, 0.0, 0.0));
            }
        } else {
            if(directionY == DIR_UP) {
                mModel =  glm::rotate(mModel, glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
            } else if(directionY == DIR_DOWN) {
                mModel =  glm::rotate(mModel, glm::radians(-angle), glm::vec3(1.0, 0.0, 0.0));
            }
        }
    }
private:

    bool InUse = false;

protected:

    glm::mat4 mProj = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 100.0f);
    glm::mat4 mModel = glm::mat4(1.0f);
    glm::mat4 mMVP = glm::mat4(1.0f);

    ShaderProxy* mShader;
    Camera* mCamera;


};

#endif //OPENGLSTUDY_BASESCENE_H

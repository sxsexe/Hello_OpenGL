//
// Created by xiaodong.lxd on 2023/2/6.
//

#ifndef OPENGLFUN_CAMERA_H
#define OPENGLFUN_CAMERA_H


#include "common.h"

class Camera {

private:
    const float Z_Max = 7.0f;
    const float Z_Min = 3.0f;
    const float Z_STEP = 0.3f;
    float zDist = (Z_Max + Z_Min) / 2;
    glm::vec3 mTrans = {0.0f, 0.0f, zDist};
    glm::vec3 mUp = {0.0f, 1.0f, 0.0f};
    glm::mat4 mViewMatrix;

public:

    Camera() {
        mViewMatrix = glm::lookAt(mTrans,                                   // 相机位置
                                  glm::vec3(0.0f, 0.0f, 0.0f),              // 相机target
                                  mUp);                                     //up分量
    };

    ~Camera() = default;

    glm::mat4 getCameraViewMatrix() const {
        return mViewMatrix;
    }

    glm::vec3 getCameraPos() {
        return mTrans;
    }

    void ZoomIn() {
        zDist -= Z_STEP;
        if(zDist < Z_Min) {
            zDist = Z_Min;
        }
        mTrans.z = zDist;
        mViewMatrix = glm::lookAt(mTrans,                                   // 相机位置
                                  glm::vec3(0.0f, 0.0f, 0.0f),              // 相机target
                                  mUp);
    }

    void ZoomOut() {
        zDist += Z_STEP;
        if(zDist > Z_Max) {
            zDist = Z_Max;
        }
        mTrans.z = zDist;
        mViewMatrix = glm::lookAt(mTrans,                                   // 相机位置
                                  glm::vec3(0.0f, 0.0f, 0.0f),              // 相机target
                                  mUp);
    }

};


#endif //OPENGLFUN_CAMERA_H

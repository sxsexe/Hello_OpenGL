//
// Created by xiaodong.lxd on 2023/2/6.
//

#ifndef OPENGLFUN_CAMERA_H
#define OPENGLFUN_CAMERA_H


#include "common.h"

class Camera {

private:
    glm::vec3 mTrans = {0.0f, 0.0f, 5.0f};
    glm::vec3 mUp = {0.0f, 1.0f, 0.0f};
    glm::mat4 mViewMatrix;

public:

    Camera() {
        mViewMatrix = glm::lookAt(mTrans,                                   // 相机位置
                                  glm::vec3(0.0f, 0.0f, 0.0f),              // 相机target
                                  mUp);                                     //up分量
    };

    ~Camera() = default;

    glm::mat4 getCameraMatrix() const {
        return mViewMatrix;
    }

    glm::vec3 getCameraPos() {
        return mTrans;
    }

};


#endif //OPENGLFUN_CAMERA_H

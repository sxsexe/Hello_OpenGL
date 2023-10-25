//
// Created by xiaodong.lxd on 2023/2/6.
//

#ifndef OPENGLFUN_CAMERA_H
#define OPENGLFUN_CAMERA_H


#include "common.h"

class Camera {

private:
    glm::vec3 m_Trans = {0.0f, 0.0f, 10.0f};
    glm::vec3 m_Up = {0.0f, 1.0f, 0.0f};

public:

    Camera() = default;

    ~Camera() {}

    glm::mat4 getCameraMatrix() {
        return glm::lookAt(m_Trans,           // 相机位置
                           glm::vec3(0.0f, 0.0f, 0.0f),            // 相机target
                           m_Up);           //up分量
    }

    glm::vec3 getCameraPos() {
        return m_Trans;
    }

};


#endif //OPENGLFUN_CAMERA_H

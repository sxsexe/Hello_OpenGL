//
// Created by xiaodong.lxd on 2023/10/27.
//

#ifndef OPENGLSTUDY_COLOR_H
#define OPENGLSTUDY_COLOR_H

#include "common.h"
#include <random>

class Color {

private:
    float r, g, b, a;

public:

    Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {
    }
    Color(float rr, float gg, float bb, float aa = 1.0f) : r(rr), g(gg), b(bb), a(aa) {
    }

    inline glm::vec4 getColorVec4() const {
        return {r, g, b, a};
    }

    static Color getRandomColor() {
        float min = 0.0f,max = 1.0f;
        std::random_device seed;//硬件生成随机数种子
        std::ranlux48 engine(seed());//利用种子生成随机数引擎
        std::uniform_real_distribution<float> distrib(min, max);
//        uniform_int_distribution<> distrib(min, max);//设置随机数范围，并为均匀分布
        float r = distrib(engine);//随机数
        float g = distrib(engine);//随机数
        float b = distrib(engine);//随机数

        std::cout<< "{r=" << r << ", g=" << g << ", b=" << b << "}" << std::endl;

        return {r, g, b};
    }



};

#endif //OPENGLSTUDY_COLOR_H

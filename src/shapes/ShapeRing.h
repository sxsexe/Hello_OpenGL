//
// Created by xiaodong.lxd on 2023/10/28.
//

#ifndef OPENGLSTUDY_SHAPERING_H
#define OPENGLSTUDY_SHAPERING_H

#include "BaseShape.h"

class ShapeRing : public BaseShape {

public:
    ShapeRing() {
        std::cout << "Create ShapeRing" << std::endl;
        mType = S_Ring;
    }

    ~ShapeRing() override {
        std::cout << "Delete ShapeRing" << std::endl;
    }


    void Draw(double delta) override {

    }


};

#endif //OPENGLSTUDY_SHAPERING_H

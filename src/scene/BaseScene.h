//
// Created by xiaodong.lxd on 2023/10/25.
//

#ifndef OPENGLSTUDY_BASESCENE_H
#define OPENGLSTUDY_BASESCENE_H

#include "common.h"

class BaseScene {

public:
    BaseScene() {};
    virtual ~BaseScene() {};
    BaseScene (const BaseScene& rhs) = delete;
    BaseScene& operator=(const BaseScene& rhs) = delete;

    virtual void Draw(double delta) = 0;
    virtual void OnEnter() { InUse = true; };
    virtual void OnExit() { InUse = false; };
    inline bool CanDraw() const { return InUse; }

private:

    bool InUse = false;

};

#endif //OPENGLSTUDY_BASESCENE_H

#pragma once

#include "raylib.h"
#include "Director.h"
#include "../Utils/MathUtils.hpp"
#include <string>

class RenderState {
private:
protected:
    RenderState();
public:
    virtual ~RenderState();
    virtual void Update();
    virtual void Draw() const;
    virtual void Enter();
    virtual void Exit();
}; 
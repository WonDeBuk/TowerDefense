#pragma once

#include "raylib.h"
#include "Director.h"
#include <string>

class Director;

class RenderState {
protected:
    RenderState();
    std::string StateTitle;
public:
    virtual ~RenderState();
    virtual void Update();
    virtual void Draw() const;
}; 
#include "RenderState.h"

RenderState::RenderState()
{
}

RenderState::~RenderState()
{
}

void RenderState::Update()
{
    // Default implementation does nothing
}

void RenderState::Enter()
{
    // Default implementation does nothing
}

void RenderState::Exit()
{
    // Default implementation does nothing
}


void RenderState::Draw() const
{
    size_t Time = Director::GetInstance().GetTime();
    Vector3 HSV = ColorCalculate();
    Color Lighter = ColorFromHSV(HSV.x, HSV.y, HSV.z);
    Color Darker = ColorFromHSV(HSV.x, HSV.y, HSV.z * 0.95f);
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            DrawRectangle(64 * j - (Time % 64), 64 * i - (Time % 64), 64, 64, ((i + j) % 2 == 0) ? Lighter : Darker);
        }
                
    }
}
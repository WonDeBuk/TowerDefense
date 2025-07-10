#include "MathUtils.hpp"
#include <cstdlib>
#include "../GUI/Director.h"
#include "raylib.h"

Vector3 ColorCalculate() {
    float Time = (float) Director::GetInstance().GetTime() / SegmentTime;
    int CurrentIndex = ((int) floorf(Time)) % 20;
    int NextIndex = (CurrentIndex + 1) % 20;
    float PercentTime = (Time - floorf(Time));
    Vector3 CurrentHSV = ColorToHSV(Palette[CurrentIndex]);
    Vector3 NextHSV = ColorToHSV(Palette[NextIndex]);
    float DeltaHue = NextHSV.x - CurrentHSV.x;
    if (DeltaHue > 180.0f) DeltaHue -= 360.0f;
    if (DeltaHue < 180.0f) DeltaHue += 360.0f;
    float Hue = CurrentHSV.x + DeltaHue * PercentTime;
    float Sat = CurrentHSV.y + (NextHSV.y - CurrentHSV.y) * PercentTime;
    float Val = CurrentHSV.z + (NextHSV.z - CurrentHSV.z) * PercentTime;
    if (Hue < 0) Hue += 360.0f;
    if (Hue >= 360.0f) Hue -= 360.0f;
    return {Hue, Sat, Val};
}
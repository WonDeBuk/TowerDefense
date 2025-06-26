#pragma once

#include <cmath>
#include <cstdlib>
#include "raylib.h"

Vector2 Lerp(const Vector2& p0, const Vector2& p1, float t) {
    return {
        p0.x + t * (p1.x - p0.x),
        p0.y + t * (p1.y - p0.y)
    };
}

Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t) {
    float u = 1.0f - t;
    return {
        u * u * p0.x + 2.0f * u * t * p1.x + t * t * p2.x,
        u * u * p0.y + 2.0f * u * t * p1.y + t * t * p2.y
    };
}

float BezierDerivative(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t) {
    return 2.0f * (1.0f - t) * (p1.x - p0.x) + 2.0f * t * (p2.x - p1.x);
}

Vector2 Normalize(const Vector2& v) {
    float length = sqrt(v.x * v.x + v.y * v.y);
    if (length > 0.0f) {
        return { v.x / length, v.y / length };
    }
    return { 0.0f, 0.0f };
}

Vector2 Perpendicular(const Vector2& v) {
    return { -v.y, v.x };
}

// Vector2 BezierCubic(const Vector2& p0, const Vector2& p1, const Vector2& p2, const Vector2& p3, float t) {
//     float u = 1.0f - t;
//     return {
//         u * u * u * p0.x + 3.0f * u * u * t * p1.x + 3.0f * u * t * t * p2.x + t * t * t * p3.x,
//         u * u * u * p0.y + 3.0f * u * u * t * p1.y + 3.0f * u * t * t * p2.y + t * t * t * p3.y
//     };
// }

float length(const Vector2& v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

float randomOffset(float range) {
    return (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f) * range;
}

Vector2 Subtract(const Vector2& v1, const Vector2& v2) {
    return { v1.x - v2.x, v1.y - v2.y };
}

Vector2 Multiply(const Vector2& v, float scalar) {
    return { v.x * scalar, v.y * scalar };
}

Vector2 Add(const Vector2& v1, const Vector2& v2) {
    return { v1.x + v2.x, v1.y + v2.y };
}

void generateBezierWithNoise(
    const Vector2& startPoint,
    const Vector2& arrivePoint,
    Vector2& control1,
    Vector2& control2,
    float noiseStrength = 30.0f
) {
    Vector2 dir = Normalize(Subtract(arrivePoint, startPoint));
    Vector2 perp = Perpendicular(dir);
    float distance = length(Subtract(arrivePoint, startPoint));

    float offset1 = randomOffset(noiseStrength);
    float offset2 = randomOffset(noiseStrength);

    control1 = Add(startPoint, Add(Multiply(dir, (distance * 0.3f)), Multiply(perp, offset1)));
    control2 = Add(startPoint, Add(Multiply(dir, (distance * 0.6f)), Multiply(perp, offset2)));
}
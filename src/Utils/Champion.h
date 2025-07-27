#pragma once

#include <string>
#include "Define.h"
#include "raylib.h"

class Champion {
public:
    ChampionTierType ChampionTier;
    Texture2D* ChampionIcon;
    Texture2D* ChampionTextureIdle;
    Texture2D* ChampionTextureCast;

    void ChampionDraw(const ChampionAnimationState& _ChampionAnimationState, const Vector2& _DrawPosition, const bool& _IsOutline, const size_t& _Timer) const;
};
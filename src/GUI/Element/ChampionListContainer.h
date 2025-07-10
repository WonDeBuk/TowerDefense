#pragma once

#include "PagedContainer.h"
#include "Utils/ResourceManager.h"
#include <string>

class ChampionListContainer : public PagedContainer<ChampionData>
{
private:
    Texture2D** ChampionTexture;
    Texture2D** ItemBorder;
    Texture2D** ItemCover;
    Texture2D* ItemBackground;
    Texture2D* NextButtonTexture;
    Texture2D* PreviousButtonTexture;
    Texture2D* BoxIndicator;
    Font* ContentFont;
    Rectangle* BoxIndicatorDimension;
    Rectangle* ContentDimension;
    Rectangle* CoverDimension;
    Rectangle* BackgroundDimension;
    Rectangle* ChampionIconDimension;
    float ScaleFactor;
    const float ContentFontSize = 24.0f;
public:
    ChampionListContainer(Rectangle, const int&, const int&, const ChampionData*, const int&);
    void Update() override;
    void Draw() const override;
    void UpdateContentDimension();
    ~ChampionListContainer() override;
}; 
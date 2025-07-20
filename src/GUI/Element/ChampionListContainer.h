#pragma once

#include "PagedContainer.h"
#include "Utils/ResourceManager.h"
#include <string>

class DictionaryState;

class ChampionListContainer : public PagedContainer<Champion>
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
    DictionaryState* OwnerDictionary;
    float ScaleFactor;
    const float ContentFontSize = 24.0f;
public:
    ChampionListContainer(Rectangle, const int&, const int&, const Champion*, const int&, DictionaryState*);
    void SetSelectedIndex(const int& _Index);
    void Update() override;
    void Draw() const override;
    void UpdateContentDimension();
    ~ChampionListContainer() override;
}; 
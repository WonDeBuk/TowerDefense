#include "ChampionListContainer.h"

#include "PagedContainer.h"
#include "Utils/AssetManager.h"

ChampionListContainer::ChampionListContainer(const Rectangle &__ContainerBound, const size_t &__NumRow, const size_t &__NumColumn, ChampionInfo* __ItemList, const size_t &__ItemListSize, const float &__ItemHeightPadding, const float &__ItemWidthPadding)
: PagedContainer<ChampionInfo>(__ContainerBound, __NumRow, __NumColumn, __ItemList, __ItemListSize, __ItemHeightPadding, __ItemWidthPadding)
{
}

ChampionListContainer::~ChampionListContainer()
{
}

void ChampionListContainer::DrawItem(const ChampionInfo &__Champion, const Rectangle &__ItemBound, const bool &__IsSelected, const bool &__IsHovered) const
{
    float ScaleFactorX = __ItemBound.width / 80.0f;
    float ScaleFactorY = __ItemBound.height / 112.0f;

    DrawTexturePro(AssetManager::GetInstance().LoadTexture("ui/Champion_Background.png"), 
        { 0.0f, 0.0f, 68.0f, 92.0f }, 
        { __ItemBound.x + 6.0f * ScaleFactorX, __ItemBound.y + 10.0f * ScaleFactorY, 68.0f * ScaleFactorX, 92.0f * ScaleFactorY }, 
        { 0.0f, 0.0f }, 
        0.0f, 
        WHITE);

    DrawTexturePro(AssetManager::GetInstance().LoadTexture("ui/" + __Champion.ChampionName + "_icon.png"), 
        { 16.0f, 16.0f, 32.0f, 48.0f }, 
        { __ItemBound.x + 8.0f * ScaleFactorX, __ItemBound.y + 6.0f * ScaleFactorY, 64.0f * ScaleFactorX, 96.0f * ScaleFactorY }, 
        { 0.0f, 0.0f }, 
        0.0f, 
        WHITE);

    DrawTexturePro(AssetManager::GetInstance().LoadTexture("ui/" + __Champion.ChampionTier + "_Border.png"), 
        { 0.0f, 0.0f, 80.0f, 112.0f }, 
        __ItemBound, 
        { 0.0f, 0.0f }, 
        0.0f, 
        WHITE);

    DrawTexturePro(AssetManager::GetInstance().LoadTexture("ui/" + __Champion.ChampionTier + "_Cover.png"), 
        { 0.0f, 0.0f, 68.0f, 22.0f }, 
        { __ItemBound.x + 6.0f * ScaleFactorX, __ItemBound.y + 80.0f * ScaleFactorY, 68.0f * ScaleFactorX, 22.0f * ScaleFactorY}, 
        { 0.0f, 0.0f },
        0.0f,
        WHITE);
    if (__IsSelected)
    {
        DrawRectangleLinesEx(__ItemBound, 2.0f, RED);
    }
    else if (__IsHovered)
    {
        DrawRectangleLinesEx(__ItemBound, 2.0f, BLUE);
    }
}

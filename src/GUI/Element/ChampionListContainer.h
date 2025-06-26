#pragma once

#include "PagedContainer.h"
#include "Utils/AssetManager.h"
#include <string>

typedef struct ChampionInfo
{
    std::string ChampionName;
    std::string ChampionTier;
};

class ChampionListContainer : public PagedContainer<ChampionInfo>
{
public:
    ChampionListContainer(const Rectangle &__ContainerBound, const size_t &__NumRow, const size_t &__NumColumn, ChampionInfo* __ItemList = nullptr, const size_t& __ItemListSize = 0, const float &__ItemHeightPadding = 0.0f, const float &__ItemWidthPadding = 0.0f);
    ~ChampionListContainer();
    void DrawItem(const ChampionInfo& __Champion, const Rectangle& __ItemBound, const bool& __IsSelected, const bool& __IsHovered) const override;
}; 
#pragma once
#include "PagedContainer.hpp"
#include "TowerInfo.hpp"
#include "../Utils/AssetManager.hpp"
#include <string>

class TowerListContainer : public PagedContainer<TowerInfo> {
public:
    std::vector<Texture2D> towerIcon;
    TowerListContainer(Rectangle bounds, size_t numsRows, size_t numsColumns, std::vector<TowerInfo> items)
        : PagedContainer<TowerInfo>(bounds, numsRows, numsColumns) {
        this->setItems(items);
        towerIcon.resize(items.size());
        for (size_t i = 0; i < items.size(); i++) {
            towerIcon[i] = AssetManager::getInstance().loadTexture("ui/" + items[i].name + ".png");
        }
    }

    ~TowerListContainer() {
        for (size_t i = 0; i < towerIcon.size(); i++) {
            AssetManager::getInstance().unloadTexture(towerIcon[i]);
        }
    }

protected:
    void drawItem(const TowerInfo& tower, Rectangle bounds, bool isSelected) override {
        // Draw item background
        DrawRectangleRec(bounds, isSelected ? SKYBLUE : WHITE);
        DrawRectangleLinesEx(bounds, 1, BLACK);
        DrawTexturePro(towerIcon[tower.id], {0, 0, 128.0f, 128.0f}, bounds, {0.0f, 0.0f}, 0, WHITE);
    }
}; 
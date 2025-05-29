#pragma once
#include "MenuState.hpp"
#include "MenuDirector.hpp"
#include "MenuType.hpp"
#include "TowerListContainer.hpp"
#include "TowerInfo.hpp"

class DictionaryMenuState : public MenuState {
private:
    TowerListContainer towerList;
    Rectangle infoPanelBounds;

    static std::vector<TowerInfo> initializeTowers() {
        std::vector<TowerInfo> towers;
        towers.push_back({"Devil", "A simple tower with balanced stats", 10, 100.0f, 1.0f, 100, 0});
        towers.push_back({"Gunner", "Long range, high damage, slow attack speed", 50, 200.0f, 0.5f, 200, 1});
        towers.push_back({"Wizard", "Fast attack speed, low damage", 5, 80.0f, 2.0f, 150, 2});
        towers.push_back({"Angel", "Deals splash damage to multiple enemies", 15, 120.0f, 0.8f, 250, 3});
        towers.push_back({"Samurai", "Slows down enemies", 8, 90.0f, 1.2f, 175, 4});
        return towers;
    }

public:
    DictionaryMenuState(MenuDirector* director, int screenWidth, int screenHeight)
        : MenuState(director),
          towerList(
              Rectangle{50.0f, 100.0f, screenWidth * 0.7f - 50.0f, screenHeight - 200.0f},
              5,  // Show 5 items per column
              5,  // Show 5 items per row
              initializeTowers()
          ),
          infoPanelBounds{
              screenWidth * 0.7f + 50.0f,
              100.0f,
              screenWidth * 0.3f - 100.0f,
              screenHeight - 200.0f
          }
    {
        title = "Tower Dictionary";
        position = Vector2{0, 0};
        size = Vector2{(float)screenWidth, (float)screenHeight};
    }

    void enter() override {
        // Reset tower selection when entering
        towerList.setSelectedIndex(-1);
    }

    void exit() override {
        // Nothing special needed for dictionary exit
    }

    void update() override {
        if (isBackButtonClicked()) {
            director->transitionTo(MenuType::MAIN);
            return;
        }

        // Handle tower list updates
        towerList.update();

        // Handle tower selection
        Vector2 mousePos = GetMousePosition();
        size_t clickedIndex;
        if (towerList.checkItemClick(mousePos, clickedIndex)) {
            towerList.setSelectedIndex(clickedIndex);
        }
    }

    void draw() override {
        drawBase();

        // Draw tower list
        towerList.draw();

        // Draw info panel
        DrawRectangleRec(infoPanelBounds, WHITE);
        DrawRectangleLinesEx(infoPanelBounds, 1, BLACK);

        // Draw detailed info if a tower is selected
        int selectedIndex = towerList.getSelectedIndex();
        if (selectedIndex >= 0) {
            TowerInfo selectedTower = towerList.getSelectedItem();
            DrawText("Detailed Tower Information",
                    infoPanelBounds.x + 20,
                    infoPanelBounds.y + 20,
                    24, BLACK);
            DrawText(selectedTower.name.c_str(),
                    infoPanelBounds.x + 20,
                    infoPanelBounds.y + 50,
                    20, BLACK);
            DrawText(selectedTower.description.c_str(),
                    infoPanelBounds.x + 20,
                    infoPanelBounds.y + 80,
                    16, DARKGRAY);
            
            char buffer[100];
            sprintf(buffer, "Damage: %d", selectedTower.damage);
            DrawText(buffer,
                    infoPanelBounds.x + 20,
                    infoPanelBounds.y + 110,
                    16, DARKGRAY);
            
            sprintf(buffer, "Range: %.0f", selectedTower.range);
            DrawText(buffer,
                    infoPanelBounds.x + 20,
                    infoPanelBounds.y + 140,
                    16, DARKGRAY);
            
            sprintf(buffer, "Attack Speed: %.1f", selectedTower.attackSpeed);
            DrawText(buffer,
                    infoPanelBounds.x + 20,
                    infoPanelBounds.y + 170,
                    16, DARKGRAY);
            
            sprintf(buffer, "Cost: %d", selectedTower.cost);
            DrawText(buffer,
                    infoPanelBounds.x + 20,
                    infoPanelBounds.y + 200,
                    16, DARKGRAY);
        }
    }
}; 
#pragma once
#include "raylib.h"
#include <vector>
#include <string>
#include <cmath>

template<typename T>
class PagedContainer {
public:
    PagedContainer(Rectangle bounds, size_t numsRows, size_t numsColumns)
        : bounds(bounds), numsRows(numsRows), numsColumns(numsColumns), currentPage(0)
    {
        // Calculate button dimensions
        float buttonWidth = 100.0f;
        float buttonHeight = 30.0f;
        prevButton = Rectangle{
            bounds.x,
            bounds.y + bounds.height + 10.0f,
            buttonWidth,
            buttonHeight
        };
        nextButton = Rectangle{
            bounds.x + bounds.width - buttonWidth,
            bounds.y + bounds.height + 10.0f,
            buttonWidth,
            buttonHeight
        };
    }

    void setItems(const std::vector<T>& newItems) {
        items = newItems;
        currentPage = 0;
        totalPages = (items.size() + numsRows * numsColumns - 1) / (numsRows * numsColumns);  // Ceiling division
    }

    // Const version returns const reference
    const T& getSelectedItem() const {
        return items[selectedIndex];
    }

    void update() {
        Vector2 mousePos = GetMousePosition();

        // Handle previous button
        if (currentPage > 0 && 
            CheckCollisionPointRec(mousePos, prevButton) && 
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            currentPage--;
        }

        // Handle next button
        if (currentPage < totalPages - 1 && 
            CheckCollisionPointRec(mousePos, nextButton) && 
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            currentPage++;
        }
    }

    void draw() {
        // Draw container background
        DrawRectangleRec(bounds, LIGHTGRAY);

        // Draw items for current page
        size_t startIdx = currentPage * numsRows * numsColumns;
        size_t endIdx = std::min(startIdx + numsRows * numsColumns, items.size());

        float itemWidth = bounds.width / static_cast<float>(numsColumns);
        float itemHeight = bounds.height / ( static_cast<float>(numsRows));
        for (size_t i = startIdx; i < endIdx; i++) {
            Rectangle itemBounds = {
                bounds.x + (i % numsColumns) * itemWidth,
                bounds.y + (i / numsColumns) * itemHeight,
                itemWidth,
                itemHeight
            };
            drawItem(items[i], itemBounds, i == selectedIndex);
        }

        // Draw navigation buttons
        if (currentPage > 0) {
            DrawRectangleRec(prevButton, GRAY);
            DrawText("Previous",
                    prevButton.x + 10,
                    prevButton.y + 5,
                    20, BLACK);
        }

        if (currentPage < totalPages - 1) {
            DrawRectangleRec(nextButton, GRAY);
            DrawText("Next",
                    nextButton.x + 30,
                    nextButton.y + 5,
                    20, BLACK);
        }

        // Draw page indicator
        char pageText[32];
        sprintf(pageText, "Page %zu of %zu", currentPage + 1, totalPages);
        float textWidth = MeasureText(pageText, 20);
        DrawText(pageText,
                bounds.x + (bounds.width - textWidth) / 2,
                bounds.y + bounds.height + 15,
                20, BLACK);
    }

    int getSelectedIndex() const { return selectedIndex; }
    void setSelectedIndex(int index) { selectedIndex = index; }

    bool checkItemClick(Vector2 mousePos, size_t& clickedIndex) {
        if (!CheckCollisionPointRec(mousePos, bounds)) return false;

        size_t startIdx = currentPage * numsRows * numsColumns;
        size_t endIdx = std::min(startIdx + numsRows * numsColumns, items.size());

        float itemWidth = bounds.width / static_cast<float>(numsColumns);
        float itemHeight = bounds.height / static_cast<float>(numsRows);

        for (size_t i = startIdx; i < endIdx; i++) {
            Rectangle itemBounds = {
                bounds.x + (i % numsColumns) * itemWidth,
                bounds.y + (i / numsColumns) * itemHeight,
                itemWidth,
                itemHeight
            };

            if (CheckCollisionPointRec(mousePos, itemBounds)&& 
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                clickedIndex = i;
                return true;
            }
        }

        return false;
    }

protected:
    virtual void drawItem(const T& item, Rectangle bounds, bool isSelected) = 0;

private:
    Rectangle bounds;
    Rectangle prevButton;
    Rectangle nextButton;
    std::vector<T> items;
    size_t numsRows;
    size_t numsColumns;
    size_t currentPage;
    size_t totalPages;
    int selectedIndex = -1;
}; 
#pragma once

#include "raylib.h"
#include <string>
#include "././Utils/UnicodeText.hpp"

extern Font TestFont;

template<typename T>
class PagedContainer {
private:
    Rectangle ContainerBound;
    Rectangle PreviousButton;
    Rectangle NextButton;
    const T* ItemList;
    size_t ItemListSize;
    size_t NumRow;
    size_t NumColumn;
    size_t CurrentPage;
    size_t TotalPage;
    int SelectedIndex = -1;
    int HoveredIndex = -1;
    float ItemHeightPadding;
    float ItemWidthPadding;
public:
    PagedContainer(const Rectangle& __ContainerBound, const size_t& __NumRow, const size_t& __NumColumn, const T* __ItemList = nullptr, const size_t& __ItemListSize = 0, 
                   const float& __ItemHeightPadding = 0.0f, const float& __ItemWidthPadding = 0.0f);
    void SetItems(const T*& __ItemList, const size_t& __ItemListSize);
    const T& GetSelectedItem() const;
    void Update();
    void Draw() const;
    int GetSelectedIndex() const;
    void SetSelectedIndex(const int& __Index);

protected:
    virtual void DrawItem(const T& __Item, const Rectangle& __ItemBound, const bool& __IsSelected, const bool& __IsHovered) const = 0;
};

template <typename T>
inline PagedContainer<T>::PagedContainer(const Rectangle &__ContainerBound, const size_t &__NumRow, const size_t &__NumColumn, const T* __ItemList, const size_t& __ItemListSize, const float &__ItemHeightPadding, const float &__ItemWidthPadding)
    : ItemHeightPadding(__ItemHeightPadding), ItemWidthPadding(__ItemWidthPadding), CurrentPage(0), TotalPage(0), SelectedIndex(-1), HoveredIndex(-1),
      ContainerBound(__ContainerBound), PreviousButton(), NextButton(), ItemList(__ItemList), ItemListSize(__ItemListSize),
      NumRow(__NumRow), NumColumn(__NumColumn) 
{
    float ButtonWidth = 100.0f;
    float ButtonHeight = 30.0f;

    PreviousButton = Rectangle{
        ContainerBound.x,
        ContainerBound.y + ContainerBound.height + 10.0f,
        ButtonWidth,
        ButtonHeight
    };

    NextButton = Rectangle{
        ContainerBound.x + ContainerBound.width - ButtonWidth,
        ContainerBound.y + ContainerBound.height + 10.0f,
        ButtonWidth,
        ButtonHeight
    };

    TotalPage = (ItemListSize + NumRow * NumColumn - 1) / (NumRow * NumColumn);
}

template <typename T>
void PagedContainer<T>::SetItems(const T *&__ItemList, const size_t &__ItemListSize)
{
    ItemList = __ItemList;
    ItemListSize = __ItemListSize;
    CurrentPage = 0;
    TotalPage = (ItemListSize + NumRow * NumColumn - 1) / (NumRow * NumColumn);
}

template <typename T>
const T& PagedContainer<T>::GetSelectedItem() const
{
    return ItemList[SelectedIndex];
}

template <typename T>
void PagedContainer<T>::Update()
{
    Vector2 MousePosition = GetMousePosition();

    if (CurrentPage > 0 &&
        CheckCollisionPointRec(MousePosition, PreviousButton) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        CurrentPage--;
    }

    if (CurrentPage < TotalPage - 1 &&
        CheckCollisionPointRec(MousePosition, NextButton) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        CurrentPage++;
    }

    if (CheckCollisionPointRec(MousePosition, ContainerBound))
    {
        size_t StartIndex = CurrentPage * NumRow * NumColumn;
        size_t EndIndex = std::min(StartIndex + NumRow * NumColumn, ItemListSize);

        float ItemWidth = ContainerBound.width / static_cast<float>(NumColumn) - ItemWidthPadding;
        float ItemHeight = ContainerBound.height / static_cast<float>(NumRow) - ItemHeightPadding;

        size_t NumPageItem = EndIndex - StartIndex;
        for (size_t i = 0; i < NumPageItem; i++)
        {
            Rectangle ItemBound = {
                ContainerBound.x + (i % NumColumn) * (ItemWidth + ItemWidthPadding) + ItemWidthPadding / 2.0f,
                ContainerBound.y + (i / NumColumn) * (ItemHeight + ItemHeightPadding) + ItemHeightPadding / 2.0f,
                ItemWidth,
                ItemHeight
            };

            if (CheckCollisionPointRec(MousePosition, ItemBound))
            {
                HoveredIndex = i + StartIndex;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    SelectedIndex = i + StartIndex;
                }
            }
        }
        
    }
    else
    {
        HoveredIndex = -1; // Reset hovered index if not in container
    }
}

template <typename T>
void PagedContainer<T>::Draw() const
{
    size_t StartIndex = CurrentPage * NumRow * NumColumn;
    size_t EndIndex = std::min(StartIndex + NumRow * NumColumn, ItemListSize);

    float ItemWidth = ContainerBound.width / static_cast<float>(NumColumn) - ItemWidthPadding;
    float ItemHeight = ContainerBound.height / static_cast<float>(NumRow) - ItemHeightPadding;

    size_t NumPageItem = EndIndex - StartIndex;
    for (size_t i = 0; i < NumPageItem; i++)
    {
        Rectangle ItemBound = {
            ContainerBound.x + (i % NumColumn) * (ItemWidth + ItemWidthPadding) + ItemWidthPadding / 2.0f,
            ContainerBound.y + (i / NumColumn) * (ItemHeight + ItemHeightPadding) + ItemHeightPadding / 2.0f,
            ItemWidth,
            ItemHeight
        };

        bool IsSelected = (SelectedIndex == i + StartIndex);
        bool IsHovered = (HoveredIndex == i + StartIndex);
        DrawItem(ItemList[i + StartIndex], ItemBound, IsSelected, IsHovered);
    }

    if (CurrentPage > 0) {
        DrawRectangleRec(PreviousButton, GRAY);
        DrawText("Previous",
                 PreviousButton.x + 10,
                 PreviousButton.y + 5,
                 20, BLACK);
    }
    if (CurrentPage < TotalPage - 1) {
        DrawRectangleRec(NextButton, GRAY);
        DrawText("Next",
                 NextButton.x + 30,
                 NextButton.y + 5,
                 20, BLACK);
    }
}

template <typename T>
int PagedContainer<T>::GetSelectedIndex() const
{
    return SelectedIndex;
}

template <typename T>
void PagedContainer<T>::SetSelectedIndex(const int &__Index)
{
    SelectedIndex = __Index;
}
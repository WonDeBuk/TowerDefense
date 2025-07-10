#pragma once

#include "raylib.h"
#include <iostream>
#include <string>

extern Font TestFont;

template<typename T>
class PagedContainer {
protected:
    Rectangle ContainerBound;
    Rectangle PreviousButton;
    Rectangle NextButton;
    Rectangle* ItemBound;
    bool IsNextButtonHover, IsPreviousButtonHover, IsNextButtonShow, IsPreviousButtonShow;
    T* ItemList;
    int ItemListSize, ItemPerRow, ItemPerColumn, CurrentPage, TotalPage, PageStartIndex, PageEndIndex, PageNumItem, SelectedIndex, HoveredIndex;
    virtual void Update() = 0;
    virtual void Draw() const = 0;
public:
    PagedContainer(const Rectangle&, const int&, const int&, const T*, const int&);
    const T& GetSelectedItem() const;
    int GetSelectedIndex() const;
    virtual ~PagedContainer();
};

template <typename T>
inline PagedContainer<T>::PagedContainer(const Rectangle& _CB, const int& _IPR, const int& _IPC, const T* _IL, const int& _ILS)
: ContainerBound(_CB), ItemPerRow(_IPR), ItemPerColumn(_IPC), ItemList(const_cast<T*>(_IL)), ItemListSize(_ILS), SelectedIndex(-1), HoveredIndex(-1), CurrentPage(0), IsNextButtonHover(false), IsPreviousButtonHover(false), IsPreviousButtonShow(false)
{
    std::cout << ContainerBound.x << " " << ContainerBound.y << " " << ContainerBound.width << " " << ContainerBound.height << std::endl;
    TotalPage = (int) ItemListSize / (ItemPerColumn * ItemPerRow) + 1;
    ItemBound = new Rectangle[ItemPerColumn * ItemPerRow];
    PageStartIndex = 0;
    PageEndIndex = std::min(ItemPerColumn * ItemPerRow, ItemListSize);
    PageNumItem = PageEndIndex;
    if (ItemPerRow * ItemPerColumn < ItemListSize) {
        IsNextButtonShow = true;
    } else {
        IsNextButtonShow = true;
    }
}

template <typename T>
const T& PagedContainer<T>::GetSelectedItem() const
{
    return ItemList[SelectedIndex];
}

template <typename T>
int PagedContainer<T>::GetSelectedIndex() const
{
    return SelectedIndex;
}

template <typename T>
inline PagedContainer<T>::~PagedContainer()
{
    delete[] ItemBound;
}
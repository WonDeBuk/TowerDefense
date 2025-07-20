#include "ChampionListContainer.h"
#include "GUI/Director.h"
#include "GUI/State/DictionaryState.h"
#include "././Utils/SoundManager.h"
#include <iostream>

ChampionListContainer::ChampionListContainer(Rectangle _CB, const int& _IPR, const int& _IPC, const Champion* _IL, const int& _ILS, DictionaryState* _OD)
: PagedContainer<Champion>(_CB, _IPR, _IPC, _IL, _ILS), OwnerDictionary(_OD) {
    ChampionTexture = new Texture2D*[ItemListSize];
    ItemBorder = new Texture2D*[(int) ChampionTierType::COUNTING];
    ItemCover = new Texture2D*[(int) ChampionTierType::COUNTING]; 
    for (int i = 0; i < (int) ChampionTierType::COUNTING; i++) {
        ItemBorder[i] = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/" + ResourceManager::ParseTierToString[i] + "Border.png"));
        ItemCover[i] = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/" + ResourceManager::ParseTierToString[i] + "Cover.png"));
    }
    for (int i = 0; i < ItemListSize; i++)
    {
        ChampionTexture[i] = ResourceManager::ChampionDataList[i].ChampionIcon;
    }
    
    ItemBackground = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/ChampionBackground.png"));
    NextButtonTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/RightIndicator.png"));
    PreviousButtonTexture = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/LeftIndicator.png"));
    BoxIndicator = const_cast<Texture2D*>(&ResourceManager::GetInstance().LoadTexture("ui/BoxIndicator.png"));
    BoxIndicatorDimension = new Rectangle[4];
    ContentDimension = new Rectangle[ItemPerColumn * ItemPerRow];
    CoverDimension = new Rectangle[ItemPerColumn * ItemPerRow];
    BackgroundDimension = new Rectangle[ItemPerColumn * ItemPerRow];
    ChampionIconDimension = new Rectangle[ItemPerColumn * ItemPerRow];
    ContentFont = &ResourceManager::GlobalFont;
    Vector2 ItemBorderSize = {(float) ItemBorder[0]->width, (float) ItemBorder[0]->height};
    ScaleFactor = 1.75f;
    std::cout << ScaleFactor << " " << ItemBorderSize.x << " " << ItemBorderSize.y << std::endl;
    float SeparateSpace = (ContainerBound.height - ItemBorderSize.y * ScaleFactor * ItemPerColumn) / (ItemPerColumn - 1);
    Vector2 ItemSize = {ItemBorderSize.x * ScaleFactor, ItemBorderSize.y * ScaleFactor};
    float LeftPadding = (ContainerBound.width - SeparateSpace * (ItemPerColumn - 1) - ItemSize.x * ItemPerRow)/ 2;
    for (int i = 0; i < ItemPerColumn * ItemPerRow; i++) {
        ItemBound[i] = {ContainerBound.x + (i % ItemPerRow) * (SeparateSpace + ItemSize.x) + LeftPadding, ContainerBound.y + (i / ItemPerColumn) * (SeparateSpace + ItemSize.y), ItemSize.x, ItemSize.y};
        BackgroundDimension[i] = {ItemBound[i].x + ScaleFactor * 4.0f, ItemBound[i].y + ScaleFactor * 4.0f, (float) ItemBackground->width * ScaleFactor, (float) ItemBackground->height * ScaleFactor};
        CoverDimension[i] = {ItemBound[i].x + ScaleFactor * 4.0f, ItemBound[i].y + ScaleFactor * 74.0f, ceilf((float) ItemCover[0]->width * ScaleFactor), ceilf((float) ItemCover[0]->height * ScaleFactor)};
        ChampionIconDimension[i] = {ItemBound[i].x + ScaleFactor * 4.0f, ItemBound[i].y, 32.0f * 2.125f * ScaleFactor, 48.0f * 2.125f * ScaleFactor};
    }
    PreviousButton = {ContainerBound.x, ContainerBound.y + (ContainerBound.height - 64.0f) / 2, 64.0f, 64.0f};
    NextButton = {ContainerBound.x + ContainerBound.width - 64.0f, ContainerBound.y + (ContainerBound.height - 64.0f) / 2, 64.0f, 64.0f};
    ChampionListContainer::UpdateContentDimension();
}

void ChampionListContainer::SetSelectedIndex(const int &_Index)
{
    if (_Index == -1) {
        SelectedIndex = -1;
        PageStartIndex = 0;
        PageEndIndex = std::min(ItemPerColumn * ItemPerRow, ItemListSize);
        PageNumItem = PageEndIndex;
        CurrentPage = 0;
    }
}

void ChampionListContainer::Draw() const {
    size_t Time = Director::GetInstance().GetTime();
    for (int i = 0; i < PageNumItem; i++) {
        int GlobalIndex = PageStartIndex + i;
        DrawTexturePro(*ItemBackground, {0.0f, 0.0f, 68.0f, 92.0f}, BackgroundDimension[i], {0.0f, 0.0f}, 0.0f, WHITE);
        DrawTexturePro(*ChampionTexture[GlobalIndex], {16.0f, 16.0f, 32.0f, 48.0f}, ChampionIconDimension[i], {0.0f, 0.0f}, 0.0f, WHITE);
        DrawTexturePro(*ItemCover[(int) ItemList[GlobalIndex].ChampionTier], {0.0f, 0.0f, 68.0f, 22.0f}, CoverDimension[i], {0.0f, 0.0f}, 0.0f, WHITE);
        DrawTexturePro(*ItemBorder[(int) ItemList[GlobalIndex].ChampionTier], {0.0f, 0.0f, 76.0f, 100.0f}, ItemBound[i], {0.0f, 0.0f}, 0.0f, WHITE);
        DrawTextEx(*ContentFont, ResourceManager::ParseChampionTypeToString[GlobalIndex].c_str(), {(float) ((int) ContentDimension[i].x), (float) ((int) ContentDimension[i].y)}, ContentFontSize, 1.0f, WHITE);
    }

    if (IsNextButtonShow) {
        if (!IsNextButtonHover) {
            DrawTexturePro(*NextButtonTexture, {0.0f, 64.0f, 32.0f, 32.0f}, NextButton, {0.0f, 0.0f}, 0.0f, WHITE);
        } else {
            DrawTexturePro(*NextButtonTexture, {0.0f, 32.0f * ((Time / 7) % 3), 32.0f, 32.0f}, NextButton, {0.0f, 0.0f}, 0.0f, WHITE);
        }
    }

    if (IsPreviousButtonShow) {
        if (!IsPreviousButtonHover) {
            DrawTexturePro(*PreviousButtonTexture, {0.0f, 64.0f, 32.0f, 32.0f}, PreviousButton, {0.0f, 0.0f}, 0.0f, WHITE);
        } else {
            DrawTexturePro(*PreviousButtonTexture, {0.0f, 32.0f * ((Time / 7) % 3), 32.0f, 32.0f}, PreviousButton, {0.0f, 0.0f}, 0.0f, WHITE);
        }
    }

    if (HoveredIndex != -1) {
        for (int i = 0; i < 4; i++) {
            DrawTexturePro(*BoxIndicator, {12.0f * (i % 2), 24.0f * ((Time / 7) % 3) + 12.0f * (i / 2), 12.0f, 12.0f}, BoxIndicatorDimension[i], {0.0f, 0.0f}, 0.0f, WHITE);
        }
    }
}

void ChampionListContainer::Update() {
    if (CurrentPage == TotalPage - 1) {
        IsNextButtonShow = false;
    } else {
        IsNextButtonShow = true;
    }

    if (CurrentPage == 0) {
        IsPreviousButtonShow = false;
    } else {
        IsPreviousButtonShow = true;
    }

    Vector2 MousePosition = GetMousePosition();

    if (IsNextButtonShow) {
        if (CheckCollisionPointRec(MousePosition, NextButton)) {
            IsNextButtonHover = true;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                SoundManager::GetInstance().PlaySFX("click.ogg");
                CurrentPage++;
                PageStartIndex = CurrentPage * ItemPerColumn * ItemPerRow;
                PageEndIndex = std::min(PageStartIndex + ItemPerColumn * ItemPerRow, ItemListSize);
                PageNumItem = PageEndIndex - PageStartIndex;
                ChampionListContainer::UpdateContentDimension();
            }
        } else {
            IsNextButtonHover = false;
        }
    }

    if (IsPreviousButtonShow) {
        if (CheckCollisionPointRec(MousePosition, PreviousButton)) {
            IsPreviousButtonHover = true;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                SoundManager::GetInstance().PlaySFX("click.ogg");
                CurrentPage--;
                PageStartIndex = CurrentPage * ItemPerColumn * ItemPerRow;
                PageEndIndex = std::min(PageStartIndex + ItemPerColumn * ItemPerRow, ItemListSize);
                PageNumItem = PageEndIndex - PageStartIndex;
                ChampionListContainer::UpdateContentDimension();
            }
        } else {
            IsPreviousButtonHover = false;
        }
    }

    int i;

    for (i = 0; i < PageNumItem; i++) {
        if (CheckCollisionPointRec(MousePosition, ItemBound[i])) {
            HoveredIndex = i;
            BoxIndicatorDimension[0] = {ItemBound[i].x - 16.0f, ItemBound[i].y - 16.0f, 24.0f, 24.0f};
            BoxIndicatorDimension[1] = {ItemBound[i].x - 8.0f + ItemBound[i].width, ItemBound[i].y - 16.0f, 24.0f, 24.0f};
            BoxIndicatorDimension[2] = {ItemBound[i].x - 16.0f, ItemBound[i].y - 8.0f + ItemBound[i].height, 24.0f, 24.0f};
            BoxIndicatorDimension[3] = {ItemBound[i].x - 8.0f + ItemBound[i].width, ItemBound[i].y - 8.0f + ItemBound[i].height, 24.0f, 24.0f};
            break;
        } else {
            HoveredIndex = -1;
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (HoveredIndex != -1) {
            SoundManager::GetInstance().PlaySFX("click.ogg");
            SelectedIndex = i + PageStartIndex;
            OwnerDictionary->UpdateInformationPanel();
        } else {
            if (!IsPreviousButtonHover && !IsNextButtonShow) SelectedIndex = -1;
        }
    }
    
}

void ChampionListContainer::UpdateContentDimension() {
    for (int i = 0; i < PageNumItem; i++) {
        Vector2 TextDimension = MeasureTextEx(*ContentFont, ResourceManager::ParseChampionTypeToString[PageStartIndex + i].c_str(), ContentFontSize, 1.0f);
        ContentDimension[i] = {floorf(CoverDimension[i].x + (68.0f * ScaleFactor - TextDimension.x) / 2), floorf(CoverDimension[i].y + 6.0f * ScaleFactor + (16.0f * ScaleFactor - TextDimension.y) / 2), TextDimension.x, TextDimension.y};
    }
}

ChampionListContainer::~ChampionListContainer(){
}
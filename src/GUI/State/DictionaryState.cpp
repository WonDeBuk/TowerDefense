#include "DictionaryState.h"

#include "../Element/ChampionListContainer.h"
#include "../Director.h"

ChampionInfo ChampionListData[] = {
    { "Frieren", "Mythic" },
    { "Rimuru", "Legendary" },
    { "Milim", "Legendary" },
    { "Stark", "Epic" },
    { "Fern", "Epic" },
    { "Shuna", "Rare" },
    { "Maam", "Uncommon" },
    { "Xellos", "Uncommon" },
    { "Dai", "Common" },
    { "Lina", "Common" },
    { "Gourry", "Common" }
};

DictionaryState::DictionaryState() : ChampionList({ 267.0f, 145.0f, 480.0f, 600.0f }, 3, 3, ChampionListData, sizeof(ChampionListData) / sizeof(ChampionInfo), 2.0f, 10.0f)
{
    StateTitle = "Champion Dictionary";
    BackButton = { 10.0f, 10.0f, 100.0f, 50.0f };
}

void DictionaryState::Update()
{
    ChampionList.Update();
    Vector2 MousePosition = GetMousePosition();
    if (CheckCollisionPointRec(MousePosition, BackButton)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Director::GetInstance().TransitionTo(RENDER_STATE::MAIN);
        }
    }
}

void DictionaryState::Draw() const
{
    DrawTexturePro(AssetManager::GetInstance().LoadTexture("ui/Book_Background.png"), 
        { 0.0f, 0.0f, 1280.0f, 768.0f }, 
        { 160.0f, 96.0f, 1280.0f, 768.0f }, 
        { 0.0f, 0.0f }, 
        0.0f, 
        WHITE);


    ChampionList.Draw();

    if (ChampionList.GetSelectedIndex() != -1) {
        const ChampionInfo &SelectedChampion = ChampionList.GetSelectedItem();
        DrawText(("Selected Champion: " + SelectedChampion.ChampionName).c_str(), 930, 145, 20, WHITE);
    } else {
        DrawText("No champion selected", 930, 145, 20, WHITE);
    }

    DrawRectangleRec(BackButton, GRAY);
    DrawText("Back", BackButton.x + 10, BackButton.y + 10, 20, WHITE);
}

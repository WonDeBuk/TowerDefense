#pragma once

#include "../RenderState.h"
#include "../Element/ChampionListContainer.h"

class DictionaryState : public RenderState
{
private:
    ChampionListContainer ChampionList;
    Rectangle BackButton;
public:
    DictionaryState();

    void Update() override;

    void Draw() const override;
}; 
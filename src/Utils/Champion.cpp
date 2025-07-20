#include "Champion.h"
#include "ResourceManager.h"
#include "./GUI/Director.h"

void Champion::ChampionDraw(const ChampionAnimationState &_ChampionAnimationState, const Vector2 &_DrawPosition, const bool& _IsOutline, const size_t& _Timer) const {
    if (_ChampionAnimationState == ChampionAnimationState::IDLE) {
        DrawTexturePro(*ChampionTextureIdle, {CHAMPION_TEXTURE_SIZE * ((_Timer / 7) % CHAMPION_FRAME_AMOUNT), 0.0f, CHAMPION_TEXTURE_SIZE, CHAMPION_TEXTURE_SIZE}, {_DrawPosition.x - CHAMPION_TEXTURE_SIZE, _DrawPosition.y + CHAMPION_TEXTURE_Y_OFFSET - CHAMPION_TEXTURE_DRAW_SIZE, CHAMPION_TEXTURE_DRAW_SIZE, CHAMPION_TEXTURE_DRAW_SIZE}, {0.0f, 0.0f}, 0.0f, WHITE);
    } else if (_ChampionAnimationState == ChampionAnimationState::CAST) {
        DrawTexturePro(*ChampionTextureCast, {CHAMPION_TEXTURE_SIZE * ((_Timer / 7) % CHAMPION_FRAME_AMOUNT), 0.0f, CHAMPION_TEXTURE_SIZE, CHAMPION_TEXTURE_SIZE}, {_DrawPosition.x - CHAMPION_TEXTURE_SIZE, _DrawPosition.y + CHAMPION_TEXTURE_Y_OFFSET - CHAMPION_TEXTURE_DRAW_SIZE, CHAMPION_TEXTURE_DRAW_SIZE, CHAMPION_TEXTURE_DRAW_SIZE}, {0.0f, 0.0f}, 0.0f, WHITE);
    }

}

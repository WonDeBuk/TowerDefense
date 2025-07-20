#pragma once

#include "raylib.h"
#include "Define.h"
#include "Champion.h"
#include <string>
#include <unordered_map>
#include <map>

class ResourceManager {
private:
    std::unordered_map<std::string, Texture2D> TextureCache;
    std::unordered_map<std::string, std::string> PlaceholderCache;
    std::unordered_map<std::string, Music> BGMCache;
    std::unordered_map<std::string, Sound> SFXCache;

    ResourceManager();
public:
    static ResourceManager& GetInstance();
    const std::string GetResourcePath(const std::string&);

    void ReadChampionData();
    void ReadLanguage();
    void ChangeLanguage(const Language&);

    const Texture2D& LoadTexture(const std::string&);
    const Music& LoadMusic(const std::string&);
    const Sound& LoadSFX(const std::string&);
    const std::string& LoadPlaceholder(const std::string&) const;

    static Font GlobalFont;
    static Language CurrentLanguage;
    static Champion ChampionDataList[(int) ChampionType::COUNTING];
    static const std::string ParseChampionTypeToString[(int) ChampionType::COUNTING];
    static const std::string ParseChampionAnimationStateToString[(int) ChampionAnimationState::COUNTING];
    static const std::string ParseLanguageToString[];
    static const std::string ParseTierToString[];
    static const std::string ParseMapTypeToString[];
    static const std::map<std::string,EnemyType> ParseStringToEnemyType;
    static const std::map<std::string,ChampionTierType> ParseStringToChampionTierType;

    ~ResourceManager();
};
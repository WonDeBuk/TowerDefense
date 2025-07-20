#include "ResourceManager.h"
#include <iostream>
#include <assert.h>
#include <fstream>
#include <string>

// Static member definitions
Font ResourceManager::GlobalFont = {};
Language ResourceManager::CurrentLanguage = Language::VIETNAMESE;
Champion ResourceManager::ChampionDataList[(int) ChampionType::COUNTING];
const std::string ResourceManager::ParseChampionTypeToString[(int) ChampionType::COUNTING] = {"Frieren", "Rimuru", "Milim", "Stark", "Fern", "Shuna", "Dai", "Lina", "Gourry", "Maam", "Xellos", "Popp"};
// FRIEREN, RIMURU, MILIM, STARK, FERN, SHUNA, DAI, LINA, GOURRY, MAAM, XELLOS, POPP, COUNTING
const std::string ResourceManager::ParseChampionAnimationStateToString[(int) ChampionAnimationState::COUNTING] = {"Idle", "Cast"};
const std::string ResourceManager::ParseLanguageToString[] = {"EN", "VI", "DU", "FR", "IT", "SP", "PT", "RU", "ID"};
const std::string ResourceManager::ParseTierToString[] = {"Common", "Uncommon", "Rare", "Epic", "Legendary", "Mythic"};
const std::string ResourceManager::ParseMapTypeToString[] = {"Forest", "Frozen", "Desert"};
const std::map<std::string, EnemyType> ResourceManager::ParseStringToEnemyType = {{"SLIME", EnemyType::SLIME}, {"BANDIT", EnemyType::BANDIT}, {"HORNET", EnemyType::HORNET}, { "GOLEM", EnemyType::GOLEM }, {"GRUMBLE", EnemyType::GRUMBLE}, {"TITAN", EnemyType::TITAN}, {"REVENANT", EnemyType::REVENANT}};
const std::map<std::string,ChampionTierType> ResourceManager::ParseStringToChampionTierType = {{"Uncommon", ChampionTierType::UNCOMMON}, {"Common", ChampionTierType::COMMON}, {"Rare", ChampionTierType::RARE}, {"Epic", ChampionTierType::EPIC}, {"Legendary", ChampionTierType::LEGENDARY}, {"Mythic", ChampionTierType::MYTHIC}};

ResourceManager::ResourceManager() {
    // Load Custom Font
    std::fstream GlyphFile(ResourceManager::GetResourcePath("font/Glyphs.txt"), std::ios::in);
    assert(GlyphFile.is_open() && "ResourceManager * Cannot Open Font Data File ");
    int GlyphPerRow;
    GlyphFile >> GlobalFont.glyphCount >> GlobalFont.baseSize >> GlobalFont.glyphPadding >> GlyphPerRow;
    GlobalFont.texture = RAYLIB_H::LoadTexture(ResourceManager::GetResourcePath("font/Glyphs.png").c_str());
    GlobalFont.glyphs = new GlyphInfo[GlobalFont.glyphCount];
    GlobalFont.recs = new Rectangle[GlobalFont.glyphCount];
    for (size_t i = 0; i < GlobalFont.glyphCount; i++) {
        GlyphFile >> GlobalFont.glyphs[i].value;
        GlyphFile >> GlobalFont.glyphs[i].advanceX;
        GlobalFont.recs[i] = {24.0f * (i % GlyphPerRow), 48.0f * (i / GlyphPerRow), (float) GlobalFont.glyphs[i].advanceX, (float) GlobalFont.baseSize};
        GlobalFont.glyphs[i].offsetX = 0;
        GlobalFont.glyphs[i].offsetY = 0;
    }

    ResourceManager::ReadChampionData();

    // Set Current Language
    ResourceManager::ChangeLanguage(Language::VIETNAMESE);
}

ResourceManager& ResourceManager::GetInstance() {
    static ResourceManager Instance;
    return Instance;
}

const std::string ResourceManager::GetResourcePath(const std::string& __RelativePath) {
    #ifdef RESOURCE_PATH
        return std::string(RESOURCE_PATH) + "/" + __RelativePath;
    #else
        
        return "resource/" + __RelativePath;
    #endif
}

void ResourceManager::ReadChampionData() {
    std::string LineData;
    char ChampionTierBuffer[128];
    for (int i = 0; i < (int) ChampionType::COUNTING; i++) {
        std::fstream ChampionConfigFile(ResourceManager::GetResourcePath("champion/" + ParseChampionTypeToString[i] + ".txt"), std::ios::in);
        std::getline(ChampionConfigFile, LineData);
        sscanf(LineData.c_str(), "Tier: %[^\n]", &ChampionTierBuffer[0]);
        ChampionDataList[i].ChampionTier = ParseStringToChampionTierType.find(std::string(ChampionTierBuffer))->second;
        ChampionDataList[i].ChampionIcon = const_cast<Texture2D*>(&ResourceManager::LoadTexture("champion/" + ParseChampionTypeToString[i] + "Icon.png"));
        ChampionDataList[i].ChampionTextureCast = const_cast<Texture2D*>(&ResourceManager::LoadTexture("champion/" + ParseChampionTypeToString[i] + "Cast.png"));
        ChampionDataList[i].ChampionTextureIdle = const_cast<Texture2D*>(&ResourceManager::LoadTexture("champion/" + ParseChampionTypeToString[i] + "Idle.png"));
    }
}

void ResourceManager::ReadLanguage()
{
    std::fstream LanguageFile(ResourceManager::GetResourcePath("language/Language_" + ParseLanguageToString[(int) CurrentLanguage] + ".txt"), std::ios::in);
    assert(LanguageFile.is_open() && "ResourceManager * Cannot Open Language Data File");

    std::string LineData;
    char FieldBuffer[2048];
    char DataBuffer[2048];

    while (!LanguageFile.eof())
    {
        getline(LanguageFile, LineData);
        sscanf(LineData.c_str(), "%[^:]: %[^\n]", FieldBuffer, DataBuffer);
        PlaceholderCache[std::string(FieldBuffer)] = std::string(DataBuffer);
    }

    LanguageFile.close();
}

void ResourceManager::ChangeLanguage(const Language& __Language)
{
    Language* ConfigCurrentLanguage = const_cast<Language*>(&CurrentLanguage);
    *ConfigCurrentLanguage = __Language;
    ResourceManager::ReadLanguage();
}

const Texture2D& ResourceManager::LoadTexture(const std::string& __Path) {
    auto TempTexture = TextureCache.find(__Path);

    if (TempTexture != TextureCache.end())
    {
        return TempTexture->second;
    }
    else
    {
        TextureCache[__Path] = {RAYLIB_H::LoadTexture(GetResourcePath("texture/" + __Path).c_str())};
        return TextureCache.find(__Path)->second;
    }
}

const Music& ResourceManager::LoadMusic(const std::string& __Path) {
    auto TempMusic = BGMCache.find(__Path);

    if (TempMusic != BGMCache.end()) {
        return TempMusic->second;
    }
    else
    {
        BGMCache[__Path] = { RAYLIB_H::LoadMusicStream(GetResourcePath("sound/" + __Path).c_str()) };
        return BGMCache.find(__Path)->second;
    }
}

const Sound& ResourceManager::LoadSFX(const std::string& __Path) {
    auto TempSound = SFXCache.find(__Path);

    if (TempSound != SFXCache.end()) {
        return TempSound->second;
    }
    else
    {
        SFXCache[__Path] = { RAYLIB_H::LoadSound(GetResourcePath("sound/" + __Path).c_str()) };
        return SFXCache.find(__Path)->second;
    }
}


const std::string& ResourceManager::LoadPlaceholder(const std::string& __Field) const {  
   auto PlaceholderInstance = PlaceholderCache.find(__Field);  

   if (PlaceholderInstance != PlaceholderCache.end()) {  
       return PlaceholderInstance->second;  
   } else {  
       return PlaceholderCache.find("Error")->second;  
   }  
}

ResourceManager::~ResourceManager()
{
    for (auto Item: TextureCache)
    {
        RAYLIB_H::UnloadTexture(Item.second);
    }

    for (auto& Item : BGMCache) {
        RAYLIB_H::UnloadMusicStream(Item.second);
    }

    for (auto& Item : SFXCache) {
        RAYLIB_H::UnloadSound(Item.second);
    }

    TextureCache.clear();
    PlaceholderCache.clear();
    SFXCache.clear();
    BGMCache.clear();
    
    Font* ConfigGlobalFont = const_cast<Font*>(&GlobalFont);
    delete[] GlobalFont.recs;
    delete[] GlobalFont.glyphs;
}

#include "ResourceManager.h"
#include <iostream>
#include <assert.h>
#include <fstream>
#include <string>

// Static member definitions
Font ResourceManager::GlobalFont = {};
Language ResourceManager::CurrentLanguage = Language::VIETNAMESE;
const ChampionData ResourceManager::ChampionDataList[] = 
{
    {"Frieren", ChampionTier::MYTHIC},
    {"Rimuru", ChampionTier::LEGENDARY},
    {"Milim", ChampionTier::LEGENDARY},
    {"Stark", ChampionTier::EPIC},
    {"Fern", ChampionTier::EPIC},
    {"Shuna", ChampionTier::RARE},
    {"Dai", ChampionTier::RARE},
    {"Xellos", ChampionTier::UNCOMMON},
    {"Gourry", ChampionTier::UNCOMMON},
    {"Lina", ChampionTier::COMMON},
    {"Maam", ChampionTier::COMMON},
    {"Popp", ChampionTier::COMMON},

};
const std::string ResourceManager::ParseLanguageToString[] = {"EN", "VI", "DU", "FR", "IT", "SP", "PT", "RU", "ID"};
const std::string ResourceManager::ParseTierToString[] = {"Common", "Uncommon", "Rare", "Epic", "Legendary", "Mythic"};
const std::string ResourceManager::ParseMapTypeToString[] = {"Forest", "Frozen", "Desert"};
const std::map<std::string,EnemyType> ResourceManager::ParseStringToEnemyType = {{"SLIME", EnemyType::SLIME}};


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

void ResourceManager::ReadLanguage() {
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
    TextureCache.clear();
    PlaceholderCache.clear();
    
    Font* ConfigGlobalFont = const_cast<Font*>(&GlobalFont);
    delete[] GlobalFont.recs;
    delete[] GlobalFont.glyphs;
}

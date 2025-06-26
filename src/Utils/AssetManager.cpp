#include "AssetManager.h"
#include <iostream>

std::string AssetManager::GetAssetPath(const std::string& __RelativePath)
{
    #ifdef ASSETS_PATH
        return std::string(ASSETS_PATH) + "/" + __RelativePath;
    #else
        // If ASSETS_PATH is not defined, return an empty string or handle the error appropriately
        // You might want to log an error or throw an exception here
        std::cerr << "ASSETS_PATH is not defined!" << std::endl;
        return "assets/" + __RelativePath;
    #endif
}

AssetManager& AssetManager::GetInstance()
{
    static AssetManager Instance;
    return Instance;
}

const Texture2D& AssetManager::LoadTexture(const std::string& __Path)
{
    std::string FullPath = GetAssetPath("textures/" + __Path);
    auto TempTexture = TextureCache.find(FullPath);

    if (TempTexture != TextureCache.end())
    {
        return TempTexture->second;
    }
    else
    {
        TextureCache[FullPath] = {RAYLIB_H::LoadTexture(FullPath.c_str())};
        return TextureCache.find(FullPath)->second;
    }
}

const Font& AssetManager::LoadFont(const std::string& __Path)
{
    std::string FullPath = GetAssetPath("fonts/" + __Path);
    auto TempFont = FontCache.find(FullPath);

    if (TempFont != FontCache.end())
    {
        return TempFont->second;
    }
    else
    {
        FontCache[FullPath] = {RAYLIB_H::LoadFont(FullPath.c_str())};
        return FontCache.find(FullPath)->second;
    }
}

const Sound& AssetManager::LoadSound(const std::string& __Path)
{
    std::string FullPath = GetAssetPath("sounds/" + __Path);
    auto TempSound = SoundCache.find(FullPath);

    if (TempSound != SoundCache.end())
    {
        return TempSound->second;
    }
    else
    {
        SoundCache[FullPath] = {RAYLIB_H::LoadSound(FullPath.c_str())};
        return SoundCache.find(FullPath)->second;
    }
}

void AssetManager::UnloadTexture(const std::string& __Path)
{
    auto TempTexture = TextureCache.find(__Path);

    if (TempTexture != TextureCache.end())
    {
        RAYLIB_H::UnloadTexture(TempTexture->second);
        TextureCache.erase(TempTexture);
    }
    else
    {
        std::cerr << "Texture with path: " << __Path << " was not loaded!" << std::endl;
    }
}

void AssetManager::UnloadFont(const std::string& __Path)
{
    auto TempFont = FontCache.find(__Path);

    if (TempFont != FontCache.end())
    {
        RAYLIB_H::UnloadFont(TempFont->second);
        FontCache.erase(TempFont);
    }
    else
    {
        std::cerr << "Font with path: " << __Path << " was not loaded!" << std::endl;
    }
}

void AssetManager::UnloadSound(const std::string& __Path)
{
    auto TempSound = SoundCache.find(__Path);

    if (TempSound != SoundCache.end())
    {
        RAYLIB_H::UnloadSound(TempSound->second);
        SoundCache.erase(TempSound);
    }
    else
    {
        std::cerr << "Sound with path: " << __Path << " was not loaded!" << std::endl;
    }
}

void AssetManager::UnloadAll()
{
    for (auto& [__Path, __Texture] : TextureCache)
    {
        AssetManager::UnloadTexture(__Path);
    }
    
    for (auto& [__Path, __Font] : FontCache)
    {
        AssetManager::UnloadFont(__Path);
    }

    for (auto& [__Path, __Sound] : SoundCache)
    {
        AssetManager::UnloadTexture(__Path);
    }

    TextureCache.clear();
    FontCache.clear();
    SoundCache.clear();
}

AssetManager::~AssetManager()
{
    AssetManager::UnloadAll();
}
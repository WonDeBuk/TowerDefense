#pragma once

#include "raylib.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <filesystem>

class AssetManager
{
private:
    AssetManager() = default;

    

    std::unordered_map<std::string, Texture2D> TextureCache;
    std::unordered_map<std::string, Font> FontCache;
    std::unordered_map<std::string, Sound> SoundCache;
public:
    static std::string GetAssetPath(const std::string& __RelativePath);
    static AssetManager& GetInstance();

    const Texture2D& LoadTexture(const std::string&);
    const Font& LoadFont(const std::string&);
    const Sound& LoadSound(const std::string&);

    void UnloadTexture(const std::string&);
    void UnloadFont(const std::string&);
    void UnloadSound(const std::string&);

    void UnloadAll();

    ~AssetManager();
};
#pragma once
#include "raylib.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <filesystem>

struct TextureResource {
    Texture2D texture;
    int refCount;
};

class AssetManager {
public:
    static AssetManager& getInstance() {
        static AssetManager instance;
        return instance;
    }

    // Get asset path helpers
    static std::string getTexturePath(const std::string& filename) {
        return getAssetPath("textures/" + filename);
    }

    static std::string getFontPath(const std::string& filename) {
        return getAssetPath("fonts/" + filename);
    }

    static std::string getSoundPath(const std::string& filename) {
        return getAssetPath("sounds/" + filename);
    }

    static std::string getMusicPath(const std::string& filename) {
        return getAssetPath("music/" + filename);
    }

    // Texture loading with reference counting
    Texture2D loadTexture(const std::string& filename) {
        std::string fullPath = getTexturePath(filename);
        auto it = textureCache.find(fullPath);
        
        if (it != textureCache.end()) {
            it->second.refCount++;
            return it->second.texture;
        }
        
        Texture2D texture = LoadTexture(fullPath.c_str());
        textureCache[fullPath] = {texture, 1};
        return texture;
    }

    // Texture unloading with reference counting
    void unloadTexture(const Texture2D& texture) {
        for (auto it = textureCache.begin(); it != textureCache.end(); ++it) {
            if (it->second.texture.id == texture.id) {
                it->second.refCount--;
                if (it->second.refCount <= 0) {
                    UnloadTexture(it->second.texture);
                    textureCache.erase(it);
                }
                return;
            }
        }
    }

    // Font loading with caching
    Font loadFont(const std::string& filename) {
        std::string fullPath = getFontPath(filename);
        if (fontCache.find(fullPath) != fontCache.end()) {
            return fontCache[fullPath];
        }
        
        Font font = LoadFont(fullPath.c_str());
        fontCache[fullPath] = font;
        return font;
    }

    // Sound loading with caching
    Sound loadSound(const std::string& filename) {
        std::string fullPath = getSoundPath(filename);
        if (soundCache.find(fullPath) != soundCache.end()) {
            return soundCache[fullPath];
        }
        
        Sound sound = LoadSound(fullPath.c_str());
        soundCache[fullPath] = sound;
        return sound;
    }

    // Music loading with caching
    Music loadMusic(const std::string& filename) {
        std::string fullPath = getMusicPath(filename);
        if (musicCache.find(fullPath) != musicCache.end()) {
            return musicCache[fullPath];
        }
        
        Music music = LoadMusicStream(fullPath.c_str());
        musicCache[fullPath] = music;
        return music;
    }

    // Cleanup resources
    void unloadAll() {
        for (auto& [path, resource] : textureCache) {
            UnloadTexture(resource.texture);
        }
        for (auto& [path, font] : fontCache) {
            UnloadFont(font);
        }
        for (auto& [path, sound] : soundCache) {
            UnloadSound(sound);
        }
        for (auto& [path, music] : musicCache) {
            UnloadMusicStream(music);
        }
        
        textureCache.clear();
        fontCache.clear();
        soundCache.clear();
        musicCache.clear();
    }

    ~AssetManager() {
        unloadAll();
    }

private:
    AssetManager() = default;
    
    static std::string getAssetPath(const std::string& relativePath) {
        #ifdef ASSETS_PATH
            return std::string(ASSETS_PATH) + "/" + relativePath;
        #else
            return "assets/" + relativePath;
        #endif
    }

    std::unordered_map<std::string, TextureResource> textureCache;
    std::unordered_map<std::string, Font> fontCache;
    std::unordered_map<std::string, Sound> soundCache;
    std::unordered_map<std::string, Music> musicCache;
}; 
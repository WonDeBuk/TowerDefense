#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "ResourceManager.h"
#include "raylib.h"
#include <unordered_map>
#include <string>

class SoundManager {
public:
    static SoundManager& GetInstance();
    void Update();

    // BGM
    void PlayBGM(const std::string& name, bool loop = true);
    void StopBGM();
    void SetBGMVolume(float volume); // [0.0, 1.0]
    void ToggleBGMMute();
    bool IsBGMMuted() const;

    // SFX
    void PlaySFX(const std::string& name);
    void SetSFXVolume(float volume); // [0.0, 1.0]
    void ToggleSFXMute();
    bool IsSFXMuted() const;
    float GetBGMVolume() const;
    float GetSFXVolume() const;

private:
    SoundManager() ;
    ~SoundManager() = default;

    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    Music currentBGM{};
    std::string currentBGMPath;
    bool bgmMuted = false;
    bool sfxMuted = false;
    float bgmVolume = 0.5f;
    float sfxVolume = 0.5f;
};

#endif // SOUND_MANAGER_H





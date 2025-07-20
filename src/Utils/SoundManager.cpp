#include "SoundManager.h"
#include "ResourceManager.h"
#include <iostream>
#include <algorithm>

SoundManager::SoundManager()
    : bgmVolume(0.5f), sfxVolume(0.5f),
    bgmMuted(false), sfxMuted(false) {
}

SoundManager& SoundManager::GetInstance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::Update() {
    if (!currentBGMPath.empty() && IsMusicStreamPlaying(currentBGM)) {
        UpdateMusicStream(currentBGM);
    }
}

void SoundManager::PlayBGM(const std::string& path, bool loop) {
    if (path == currentBGMPath && IsMusicStreamPlaying(currentBGM)) {
        return;
    }
    StopBGM();
    const Music& music = ResourceManager::GetInstance().LoadMusic(path);
    currentBGM = music;
    currentBGMPath = path;
    SetMusicVolume(currentBGM, bgmMuted ? 0.0f : bgmVolume);
    PlayMusicStream(currentBGM);
}

void SoundManager::StopBGM() {
    StopMusicStream(currentBGM);
}

void SoundManager::SetBGMVolume(float volume) {
    bgmVolume = std::clamp(volume, 0.0f, 1.0f);
    if (!bgmMuted)
        SetMusicVolume(currentBGM, bgmVolume);
}

void SoundManager::ToggleBGMMute() {
    bgmMuted = !bgmMuted;
    SetMusicVolume(currentBGM, bgmMuted ? 0.0f : bgmVolume);
}

bool SoundManager::IsBGMMuted() const {
    return bgmMuted;
}

void SoundManager::PlaySFX(const std::string& path) {
    if (IsSFXMuted()) return;
    const Sound& sfx = ResourceManager::GetInstance().LoadSFX(path);
    SetSoundVolume(sfx, sfxVolume);
    PlaySound(sfx);
}

void SoundManager::SetSFXVolume(float volume) {
    sfxVolume = std::clamp(volume, 0.0f, 1.0f);
}

void SoundManager::ToggleSFXMute() {
    sfxMuted = !sfxMuted;
}

bool SoundManager::IsSFXMuted() const {
    return sfxMuted;
}

float SoundManager::GetBGMVolume() const {
    return bgmVolume;
}

float SoundManager::GetSFXVolume() const {
    return sfxVolume;
}







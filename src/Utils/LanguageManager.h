#pragma once

#include <raylib.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include "AssetManager.h"

enum Language
{
	NONE,
	ENGLISH,
	VIETNAMESE,
	CHINESE,
	JAPANESE,
	KOREAN
};



class LanguageManager
{
private:
	LanguageManager() = default;

	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> translator;
	Language currentLanguage;
public:
	static LanguageManager& GetInstance();
	void LoadLanguage();
	void ChangeLanguage(const Language&);
	std::string Extract(const char*, const char*);

	std::string LanguageToFont(const Language&);
	std::string LanguageToFile(const Language&);

};
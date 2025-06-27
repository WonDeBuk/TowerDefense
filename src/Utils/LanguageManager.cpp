#include "LanguageManager.h"

std::string LanguageManager::LanguageToFont(const Language& lang)
{
	switch (lang)
	{
	case CHINESE:
	case KOREAN:
	case JAPANESE:
		return "NotoSnasKR.ttf";
	case ENGLISH:
	case VIETNAMESE:
		return "Roboto-Regular.ttf";
	}
}

std::string LanguageManager::LanguageToFile(const Language & lang)
{
	std::string file = "Language";
	switch (lang)
	{
	case CHINESE:
		file += "CHINESE.txt";
		break;
	case KOREAN:
		file += "KOREAN.txt";
		break;
	case JAPANESE:
		file += "JAPANESE.txt";
		break;
	case ENGLISH:
		file += "ENGLISH.txt";
		break;
	case VIETNAMESE:
		file += "VIETNAMESE.txt";
		break;
	}
	return file;
}

void LanguageManager::LoadLanguage()
{
	currentLanguage = ENGLISH; //this will be user data - later tho

	std::ifstream fin((std::string)ASSETS_PATH + "/languages/" + LanguageToFile(currentLanguage));
	std::cout << (std::string)"Language Load Status: " + ((fin.is_open()) ? "Successful" : "Failed") << "\n";
	if (!fin.is_open()) return;

	translator.clear();

	std::string toGet;
	while (getline(fin, toGet))
	{
		std::string fieldName = toGet;
		while (getline(fin, toGet) && !toGet.empty())
		{
			std::stringstream str(toGet);
			std::string memberName;
			str >> memberName;
			std::string memberValue;
			str >> memberValue;
			translator[fieldName][memberName] = memberValue.substr(1, memberValue.length() - 2);	
		}
	}
	fin.close();
}

void LanguageManager::ChangeLanguage(const Language& lang)
{
	if (lang == currentLanguage) return;
	currentLanguage = lang;
	LoadLanguage();
}

LanguageManager& LanguageManager::GetInstance()
{
	static LanguageManager Instance;
	return Instance;
}

std::string LanguageManager::Extract(const char* field, const char* member)
{
	return translator[field][member];
}
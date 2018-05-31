#pragma once
#include <vector>
#include <string>
class KeywordManager
{
public:
	static bool dictionarySearch(std::wstring);
	static void getKeywords(std::wstring , std::vector <std::wstring> &);
	static void generateObjectID (std::wstring mySource, std::wstring & myTarget);
};
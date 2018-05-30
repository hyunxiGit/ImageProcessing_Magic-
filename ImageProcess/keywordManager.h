#pragma once
#include <vector>
#include <string>
class KeywordManager
{
public:
	static bool dictionarySearch(wchar_t *);
	static void getKeywords(std::wstring , std::vector <std::wstring> &);
};
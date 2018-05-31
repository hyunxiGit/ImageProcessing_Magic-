#pragma once
#include <set>
#include <vector>
#include <string>
class KeywordManager
{
private:
	static KeywordManager* instance;
	KeywordManager();

	char dictionaryPath [MAX_PATH];
	~KeywordManager();
public:
	std::set<std::wstring> dictionary;
	static KeywordManager* getInstance();
	bool dictionarySearch(std::wstring);
	void getKeywords(std::wstring , std::vector <std::wstring> &);
	void generateObjectID (std::wstring mySource, std::wstring & myTarget);
};
#pragma once
#include "keywordManager.h"
#include "asset2D.h"
#include <vector>
using namespace std;
class ObjectSet
{
public :
	ObjectSet();
	bool init(wstring, wstring, wstring);
	bool generateID();
	wstring getObjectID();
	void generateTextureSet();
	bool setPath(wstring, wstring);
	void exportSet();
	short analyseObjectSet();
private:
	FileManager * _FM;
	KeywordManager * _KM;
	vector <Asset2D> asset2;
	wstring sourcePath;//object Folder
	wstring targetPath;//object folder
	wstring megaScanId;
	wstring objectId;
};
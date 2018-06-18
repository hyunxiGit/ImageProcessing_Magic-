#pragma once
#include "keywordManager.h"
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

	wstring sourcePath;//object Folder
	wstring targetPath;//object folder
	wstring megaScanId;
	wstring objectId;
};
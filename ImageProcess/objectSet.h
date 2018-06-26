#pragma once
#include "keywordManager.h"
#include "asset2D.h"
#include "asset3D.h"
#include "textet.h"
#include <vector>
using namespace std;
class ObjectSet
{
public :
	ObjectSet();
	bool init(wstring, wstring, wstring);
	bool generateID();
	bool setTst(Tst);
	wstring getObjectID();
	bool setPath(wstring, wstring);
	void exportSet();
	void makeObjectTargetFolder();
	
private:
	FileManager * _FM;
	KeywordManager * _KM;
	Tst tst;
	vector <Asset2D> asset2;
	vector <Asset3D> asset3;
	Textet textet;
	void generateAsset();
	wstring sourcePath;//object Folder
	wstring targetPath;//object folder
	wstring megaScanId;
	wstring objectId;
	bool makeTextet(wstring);
};
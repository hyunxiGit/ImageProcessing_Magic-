#pragma once
#include "tst.h"
#include "textet.h"
#include "asset2D.h"
#include "fileManager.h"

class TextureSetManager
{
public:
	static TextureSetManager * getInstance();
	bool checkTstByName(wstring myTstName);
	Tst getTstByName(wstring);
	Textet makeTextset(wstring objId, vector<Asset2D> & asset, wstring tstName);
	bool exportTextet(wstring path, Textet);
	bool initFile(wstring tstDir , wstring textetImgSourceDir, wstring textetImgDesteDir);
	Textet makeEmptyTextet(Tst myTst);
	int getTexetSNodeIndxByName(wstring name ,Textet );
	wstring formatPath(wstring path, wstring sStr, wstring dStr);
private:

	FileManager * _FM;
	wstring textetSourceDir;
	wstring textetDestDir;
	static TextureSetManager * instance;
	vector<Tst> tsts;
	TextureSetManager();
	bool parseTstFile(wstring myPath);
};
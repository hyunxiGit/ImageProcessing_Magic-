#pragma once
class TextureSetManager
{
public:
	static TextureSetManager * getInstance();
	bool checkTstByName(wstring myTstName);
	Tst getTstByName(wstring tstName);
	Textet makeTextset(wstring objId, vector<Asset2D> & asset, wstring tstName);
	bool exportTextet(wstring path, Textet);
	bool initFile(wstring tstDir , wstring textetImgSourceDir, wstring textetImgDesteDir);
	Textet makeEmptyTextet(Tst myTst);
	int getTexetSNodeIndxByName(wstring name ,Textet );
	int getTexetDNodeIndxByID(wstring ID, Textet);
private:

	FileManager * _FM;
	wstring textetSourceDir;
	wstring textetDestDir;
	static TextureSetManager * instance;
	map<wstring, Tst> tstFileMap;
	TextureSetManager();
	bool parseTstFile(wstring myPath);
	~TextureSetManager();
};
#pragma once
class TextureSetManager
{
public:
	static TextureSetManager * getInstance();
	bool checkTstByName(wstring myTstName);
	Tst getTstByName(wstring);
	wstring getNameByTst(Tst);
	Textet makeTextset(wstring objId, vector<Asset2D> & asset, wstring tstName);
	bool exportTextet(wstring path, Textet);
	bool initFile(wstring tstDir , wstring textetImgSourceDir, wstring textetImgDesteDir);
	Textet makeEmptyTextet(Tst myTst);
	int getTexetSNodeIndxByName(wstring name ,Textet );
private:

	FileManager * _FM;
	wstring textetSourceDir;
	wstring textetDestDir;
	static TextureSetManager * instance;
	vector<Tst> tsts;
	TextureSetManager();
	bool parseTstFile(wstring myPath);
	~TextureSetManager();
};
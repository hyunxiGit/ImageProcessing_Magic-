#pragma once
class TextureSetManager
{
public:
	static TextureSetManager * getInstance();
	bool checkTstByName(wstring myTstName);
	Tst getTstByName(wstring tstName);
	Textet makeTextset(wstring objId, vector<Asset2D> & asset, wstring tstName);
	bool exportTextet(wstring path, Textet);
	bool initTstFile(wstring initFileDir);
private:
	static TextureSetManager * instance;
	map<wstring, Tst> tstFileMap;
	TextureSetManager();
	bool parseTstFile(wstring myPath);
	~TextureSetManager();
};
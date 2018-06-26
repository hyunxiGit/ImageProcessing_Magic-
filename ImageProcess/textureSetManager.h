#pragma once
class TextureSetManager
{
public:
	static TextureSetManager * getInstance();
	Tst getTstByName(wstring tstName);
	Textet makeTextset(wstring objId, vector<wstring> imgDir, wstring tstName);
	bool exportTextet(wstring path, Textet);
	bool initTstFile(wstring initFileDir);
private:
	static TextureSetManager * instance;
	map<wstring, Tst> tstFileMap;
	TextureSetManager();
	bool parseTstFile(wstring myPath);
	~TextureSetManager();
};
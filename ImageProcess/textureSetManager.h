#pragma once
class TextureSetManager
{
public:
	static TextureSetManager * getInstance();
	Tst getTstByName(wstring tstName);
	
	bool initTstFile(wstring initFileDir);
private:
	static TextureSetManager * instance;
	map<wstring, Tst> tstFileMap;
	TextureSetManager();
	bool parseTstFile(wstring myPath);
	~TextureSetManager();
};
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


#include <iostream>
#include <fstream>

//file manager
#include <windows.h>
#include <strsafe.h>
#include "fileManager.h"

//serialize
#include <comdef.h>
#include "serialize.h"
//json
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/writer.h"
#include <stdio.h> //json file读

//keywordManager
#include "keywordManager.h"

//Asset2D
#include <Magick++.h>
#include "Asset2D.h"

using namespace Magick;
using namespace std;


#pragma comment(lib, "User32.lib")

// TODO: reference additional headers your program requires here

#pragma once
#include "stdafx.h"
#include "tst.h"

Tst::Tst():version(L"0"){}
Tst::Tst(vector<TstSource> mySourceNode, vector<TstDest> myDestNodes)
{
	version = L"0";
	sourceNodes = mySourceNode;
	destNodes = myDestNodes;
}

Tst :: ~Tst()
{
	vector<TstSource>().swap(sourceNodes);
	vector<TstDest>().swap(destNodes);
}
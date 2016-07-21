#ifndef PREPROC_H
#define PREPROC_H

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <time.h>
#include <set>

#include "../utilities/globalDefinitions.hpp"
#include "../datastructures/vit.h"
#include "../DDM//DDM.h"
#include "../datastructures/context.h"



class Preproc {
private:
	float count;
	int vitSize;
	int dataSize;

	set<string> eRules;
	vector<string> mapInfo;
	vector<pair<int, string>> *data;
	bool *dataInfo;


public:
	Preproc(char *fileName, Context &context);

	void makeVIT(char *fileName, Context &context);
	void makePart(Context &context);
	void makeBinaryPart(Context &context);

	void setMapInfo(vector<string> mapInfo, set<char> eRules);

	int getNumOfPartitions();
	~Preproc();	
};

#endif

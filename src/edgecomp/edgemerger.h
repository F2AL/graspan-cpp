#ifndef EDGEMERGER_H
#define EDGEMERGER_H

#include <iostream>
#include <ctime>
#include <limits>
#include <unordered_set>
#include <queue>

#include "../datastructures/minset.h"
#include "../../test/timer.h"
#include "../utilities/globalDefinitions.hpp"


class EdgeMerger
{
	int deltaPtr;		// index into the vector of new edges
	int oUnUdPtr;		// index into the vector of ALL edges
	int currID;			// the current vertex ID (increasing order)

	std::unordered_set<char> currEvals;		// the current edge values (to check for duplicates)
	std::priority_queue<MinSet, vector<MinSet>, compare> minEdges;

	vector<int> srcoUnUdEdges;		// ALL edges (current source edges and NEW edges)
	vector<char> srcoUnUdVals;

	vector<int> srcDeltaEdges;		// ONLY NEW edges
	vector<char> srcDeltaVals;


	// FUNCTIONS
	void fillPriorityQueue(vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge, int srcID);

	void removeExtraSpace();

	void updateMinSet(MinSet &minset, vector<int> &edges, vector<char> &vals);

	void processMinSets(MinSet &srcMS, MinSet &tgtMS, vector<int> &srcEdgesToMerge,
		vector<char> &srcValsToMerge, vector<int> &tgtEdgesToMerge,
		vector<char> &tgtValsToMerge);

	void updateVector(int vid, char val, vector<int> &edges, vector<char> &vals, int &ptr);

	public:
	// constructor
	EdgeMerger();

	// getters
	inline vector<int> &getoUnUdEdges() { return srcoUnUdEdges; }
	inline vector<char> &getoUnUdVals() { return srcoUnUdVals; }

	inline vector<int> &getDeltaEdges() { return srcDeltaEdges; }
	inline vector<char> &getDeltaVals() { return srcDeltaVals; }

	inline int getNumNewEdges() { return deltaPtr + 1; }

	// given all new edges and their values, merge with the source creating a vector of old U new edges
	// and only new edges
	void mergeVectors(vector< vector<int> > &edgeVecsToMerge, vector< vector<char> > &valVecsToMerge, int srcID);
};

#endif

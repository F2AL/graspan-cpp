#include <ctime>

#include <fstream>

#include "../datastructures/vertex.h"
#include "../datastructures/loadedvertexinterval.h"
#include "../datastructures/computationset.h"
#include "../loader/loader.h"
#include "compute.h"
#include "../../test/timer.h"
#include "../utilities/globalDefinitions.hpp"

long totNewEdges;
long newEdgesThisIter;
int iterNo;

bool newEdgesPart1;
bool newEdgesPart2;

// FUNCTION DEFS
void initCompSets(ComputationSet compsets[], vector<Vertex> &part1, vector<Vertex> &part2);

void initLVIs(vector<LoadedVertexInterval> &intervals, vector<Vertex> &part1, vector<Vertex> &part2);


/**
 * compute the new edges of each vertex simultaneously
 *
 * @param vertices
 * @param compSets
 * @param intervals
 */
void computeOneIteration(ComputationSet compSets[],
		vector<LoadedVertexInterval> &intervals, Grammar &gram)
{
//	if (vertices[0].getNumOutEdges() != 0) {
//		cout << "Updating vertex " << vertices[2].getVertexID() << "..." << endl;
//		updateEdges(2, compSets, intervals, gram);
//	}
//	else cout << "Vertex " << vertices[0].getVertexID() << " has no edges" << endl;

	assert(intervals[1].getIndexEnd() == 8, "not equal");
	#pragma omp parallel for
	for (int i = 0; i < 9; i++)
	{
		long newEdges = 0;

		newEdges += updateEdges(i, compSets, intervals, gram);

		#pragma omp atomic
		newEdgesThisIter += newEdges;
	}
}


/**
 * Get start and end indices of each partition
 *
 * @param vertices
 * @param compSets
 * @param intervals
 */
void computeEdges(ComputationSet compSets[], vector<LoadedVertexInterval> &intervals, Grammar &gram)
{
	iterNo = 0;
	totNewEdges = 0;
	
	do {
		iterNo++;
		cout << "ITERATION: " << iterNo << endl;
		newEdgesThisIter = 0;
		computeOneIteration(compSets, intervals, gram);

		totNewEdges += newEdgesThisIter;

		cout << endl << endl;
	} while (newEdgesThisIter > 0);
}

/**
 * TEST SETUP
 * generates a random vector of vertices representing a graph, then sets up computation
 * sets and vertex intervals to have a test setup for computing new edges
 */
int main(int argc, char *argv[])
{
	Timer compTime;

	compTime.startTimer();

	// load partitions into memory
	Partition p1, p2;
	Loader::loadPartition(3, p1, true);
	Loader::loadPartition(4, p2, true);
	vector<Vertex> &part1 = p1.getData(), &part2 = p2.getData();

//	vector<Vertex> vertices;
//	vertices.reserve(part1.size() + part2.size());
//
//	vertices.insert(vertices.end(), part1.begin(), part1.end());
//	vertices.insert(vertices.end(), part2.begin(), part2.end());
//
//	for (int j = 0; j < vertices.size(); j++)
//		cout << vertices[j].toString() << endl;

	// load grammar into memory
	Grammar gram;
	gram.loadGrammar("grammar");

	ComputationSet *compSets = new ComputationSet[part1.size() + part2.size()];

	initCompSets(compSets, part1, part2);
	
	// replace with primitive array
	vector<LoadedVertexInterval> intervals;
	intervals.reserve(2);
	initLVIs(intervals, part1, part2);

	for (int i = 0; i < 2; i++)
	{
		LoadedVertexInterval lvi = intervals[i];
		cout << i << ": (" << lvi.getFirstVertex() << "-" << lvi.getLastVertex() << "), (" << lvi.getIndexStart() << "-" << lvi.getIndexEnd() << ")";
		cout << endl;
	}

	computeEdges(compSets, intervals, gram);

	delete[] compSets;

	compTime.endTimer();


	cout << "TOTAL TIME: " << compTime.toString() << endl;

	return 0;
}

void initCompSets(ComputationSet compsets[], vector<Vertex> &part1, vector<Vertex> &part2)
{
	for (int i = 0; i < part1.size(); i++)
	{
		compsets[i].setNewEdges(part1[i].getOutEdges());
		compsets[i].setNewVals(part1[i].getOutEdgeValues());
		compsets[i].setoldUnewEdges(part1[i].getOutEdges());
		compsets[i].setoldUnewVals(part1[i].getOutEdgeValues());
	}

	int offset = part1.size();
	for (int j = part1.size(); j < part1.size() + part2.size(); j++)
	{
		compsets[j].setNewEdges(part2[j - offset].getOutEdges());
		compsets[j].setNewVals(part2[j - offset].getOutEdgeValues());
		compsets[j].setoldUnewEdges(part2[j - offset].getOutEdges());
		compsets[j].setoldUnewVals(part2[j - offset].getOutEdgeValues());
	}
}

void initLVIs(vector<LoadedVertexInterval> &intervals, vector<Vertex> &part1, vector<Vertex> &part2)
{
	intervals.push_back(LoadedVertexInterval{part1[0].getVertexID(), part1[part1.size() - 1].getVertexID(), 0});
	intervals[0].setIndexStart(0);
	intervals[0].setIndexEnd(part1.size()-1);

	intervals.push_back(LoadedVertexInterval{part2[0].getVertexID(), part2[part2.size() - 1].getVertexID(), 1});
	intervals[1].setIndexStart(part1.size());
	intervals[1].setIndexEnd(part1.size() + part2.size()-1);
}

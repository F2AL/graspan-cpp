#include "../../include/loadedvertexinterval.h"

// Constructor
LoadedVertexInterval::LoadedVertexInterval(int firstVertex, int lastVertex, int partitionID)
{
	this->firstVertex = firstVertex;
	this->lastVertex = lastVertex;
	this->partitionID = partitionID;
}

// Getters
int LoadedVertexInterval::getFirstVertex() { return firstVertex; }
int LoadedVertexInterval::getLastVertex() { return lastVertex; }
int LoadedVertexInterval::getIndexStart() { return indexStart; }
int LoadedVertexInterval::getIndexEnd() { return indexEnd; }
int LoadedVertexInterval::getPartitionID() { return partitionID; }

bool LoadedVertexInterval::hasNewEdges() { return newEdgeAdded; }
bool LoadedVertexInterval::hasNewEdgesCurrRound() { return newEdgeAddedCurrRound; }

// Setters
void LoadedVertexInterval::setFirstVertex(int firstVertex)
{ this->firstVertex = firstVertex; }
void LoadedVertexInterval::setLastVertex(int lastVertex)
{ this->lastVertex = lastVertex; }
void LoadedVertexInterval::setIndexStart(int indexStart)
{ this->indexStart = indexStart; }
void LoadedVertexInterval::setIndexEnd(int indexEnd)
{ this->indexEnd = indexEnd; }
void LoadedVertexInterval::setPartitionID(int partitionID)
{ this->partitionID = partitionID; }

void LoadedVertexInterval::setNewEdgeAdded(bool newEdgeAdded)
{ this->newEdgeAdded = newEdgeAdded; }
void LoadedVertexInterval::setNewEdgeAddedCurrRound(bool newEdgeCurrRound)
{ this->newEdgeAddedCurrRound = newEdgeCurrRound; }


// string representation
std::string LoadedVertexInterval::toString()
{
	std::stringstream output;

	output << std::endl << "(PartID: " << partitionID << ", VRange: " << firstVertex << " - " << lastVertex << ", IDRange: " << indexStart << " - " << indexEnd << ")";

	return output.str();
}

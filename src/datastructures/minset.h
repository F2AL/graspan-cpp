#ifndef MINSET_H
#define MINSET_H

#include <unordered_set>
#include <string>
#include <sstream>

#include "../utilities/globalDefinitions.hpp"

class MinSet
{
	int ptr;				// pointer into the current vector of edges
	
	int minSetID;			// index in the vectors to merge of the current minset
	int currentVID;			// current value of the minset
	std::unordered_set<char> evals;		// all edge values that are associated with
										// the current VID


	public:
	// constructor
	MinSet();

	// getters
	inline int getMinSetID() { return minSetID; }
	inline int getCurrVID() const { return currentVID; }
	inline int getPtr() { return ptr; }
	inline std::unordered_set<char> &getEvals() { return evals; }

	// setters
	inline void setMinSetID(int id) { minSetID = id; }
	inline void setCurrVID(int vid) { currentVID = vid; }
	inline void resetPtr() { ptr = 0; }

	inline void incPtr() { ptr++; }
	inline void addEval(char eval) { evals.insert(eval); }
	inline void clearEvalSet() { evals.clear(); }
	
	string toString();
};

// sort minsets in a priority queue
class compare
{
	public:
	bool operator()(const MinSet &m1, const MinSet &m2) const
	{
		return m1.getCurrVID() > m2.getCurrVID();
	}
};

#endif

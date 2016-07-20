#ifndef DDM_H
#define DDM_H

#include "../utilities/globalDefinitions.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
// There should be only one DDM object in the whole execution
// ==> implement Singleton pattern

class DDM{
 private:
  //TODO: merge these two vectors into 1
  //TODO: implement scheduling policy described in the paper
  int max_size;
  vector<vector<double> > ddmMap; //array for storing ddmInfo
	int numPartition;

 public:
  //default constructor, the numPartition should be obtained thru the Context object
  DDM(); 
  DDM(int numPartition); 
	~DDM();
  inline vector<vector<double> >& getDdmMap(){
	return ddmMap;
  };
  //small methods should be inlined for efficiency
  inline void set(partitionid_t p, partitionid_t q, double rate) {
    ddmMap[p][q] = rate;
  }
  void adjust(int p);


  // the indices p and q tell which partitionRate[p][q] is max: i.e., this is our scheduler
  // the bool return value indicate whether or not we should terminate the whole system
  bool nextPartitionPair(int& p, int &q);
  inline void setNumPartition(int numPartition){
	this->numPartition = numPartition;
  };
  // if repartitioning happens, 1 or 2 new partition can happen, that means DDM needs to be enlarged
  // you should figure out how to implement this resizing logic efficiently
  void enlarge();

  bool load_DDM();
  bool save_DDM();

  string toString();
  
};

#endif

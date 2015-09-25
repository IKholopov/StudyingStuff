#ifndef _CUSTOM_GENERATOR_H__
#define _CUSTOM_GENERATOR_H__

#include <iostream>
#include "UnorientedGraphValuedEdge.hpp"

void GenerateToStream();
void GenerateToStream(std::ostream& outstr, std::istream& instr);
UnorientedGraphValuedEdge<double>* GenerateGraph(unsigned int size, int percentage);
UnorientedGraphValuedEdge<double>* GenerateGraphFrom(std::istream& str);
UnorientedGraphValuedEdge<double>* GenerateGraphFromCin();

#endif

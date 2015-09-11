#ifndef _CUSTOM_GENERATOR_H__
#define _CUSTOM_GENERATOR_H__

#include <iostream>
#include "GraphValuedEdge.hpp"

void GenerateToStream();
void GenerateToStream(std::ostream& outstr, std::istream& instr);
GraphValuedEdge<double>* GenerateGraph(unsigned int size, int percentage);
GraphValuedEdge<double>* GenerateGraphFrom(std::istream& str);
GraphValuedEdge<double>* GenerateGraphFromCin();

#endif

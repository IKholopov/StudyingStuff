#ifndef _CUSTOM_GENERATOR_H__
#define _CUSTOM_GENERATOR_H__

#include <iostream>
#include "GraphValuedEdge.hpp"

GraphValuedEdge<double>* GenerateGraph(unsigned int size, int percentage);
GraphValuedEdge<double>* GenerateGraphFrom(std::istream& str);
GraphValuedEdge<double>* GenerateGraphFromCin();

#endif

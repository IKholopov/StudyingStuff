#ifndef __GRAPH_MANAGER_H__
#define __GRAPH_MANAGER_H__

#include <vector>
#include <string>
#include <utility>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>

#include "OrientedGraph.h"
#include "UnorientedGraphValuedEdge.hpp"

class GraphManager
{
    public:
        static UnorientedGraph* GetRandomUnorientedGraph(unsigned int size);
        static UnorientedGraph* GetRandomUnorientedGraph(unsigned int size, double probability);
        static OrientedGraph* GetRandomGraph(unsigned int size);
        static OrientedGraph* GetRandomGraph(unsigned int size, double probability);
        static void RandomizeGraph(OrientedGraph* g, double probability);
        //static void RandomizeUnorientedGraph(OrientedGraph *g, double probability);
        static IGraph* ReadFromFile(std::string path);
    private:
        static OrientedGraph* ReadFromFileGraphRegular(std::ifstream& file);
        static UnorientedGraphValuedEdge<int>* ReadFromFileGraphIntValuedEdge(std::ifstream& file);
};

/*      File format:
 *          <GRAPH_TYPE/>
 *              SIZE        //unsigned int value
 *              <EDGES>
 *              AMOUNT      //unsigned int value
 *              from to ...
 *              </EDGES>
 *
*/
#endif

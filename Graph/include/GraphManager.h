#ifndef __GRAPH_MANAGER_H__
#define __GRAPH_MANAGER_H__

#include <vector>
#include <string>
#include <utility>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>

#include "Graph.h"

class GraphManager
{
    public:
        static Graph* GetRandomUnorientedGraph(unsigned int size);
        static Graph* GetRandomUnorientedGraph(unsigned int size, double probability);
        static Graph* GetRandomGraph(unsigned int size);
        static Graph* GetRandomGraph(unsigned int size, double probability);
        static void RandomizeGraph(Graph* g, double probability);
        static void RandomizeUnorientedGraph(Graph *g, double probability);
        static Graph* ReadFromFile(std::string path);
    private:
        static Graph* ReadFromFileGraphRegular(std::ifstream& file);
        static Graph* ReadFromFileGraphValuedEdge(std::ifstream& file);
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

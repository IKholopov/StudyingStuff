#include "TestMST.h"

#include <fstream>
#include <time.h>
#include "CustomGenerator.h"
#include "Kruskal.h"
#include "Prim.h"
#include "Boruvka.h"

void TestMST()
{
    GraphValuedEdge<double>* graph = GenerateGraph(1000, 100);
    /*GraphValuedEdge<double>* graph = new GraphValuedEdge<double>(10);
    std::ifstream file("mst");
    graph->ReadFromFile(file);
    file.close();*/
    graph->WriteToFile("~/mst");
    GraphValuedEdge<double>* mstK = Kruskal(graph);
    std::vector<Edge*> edgesK = mstK->GetAllEdgesSorted();
    GraphValuedEdge<double>* mstP = Prim(graph);
    std::vector<Edge*> edgesP = mstP->GetAllEdgesSorted();
    GraphValuedEdge<double>* mstB = Boruvka(graph);
    std::vector<Edge*> edgesB = mstB->GetAllEdgesSorted();
    std::cout << "Boruvka" << std::endl;
    for(int i = 0; i < edgesB.size(); ++i)
        std::cout << edgesB[i]->From << " " << edgesB[i]->To << std::endl;
    std::cout << "Kruskal" << std::endl;
    for(int i = 0; i < edgesK.size(); ++i)
        std::cout << edgesK[i]->From << " " << edgesK[i]->To << std::endl;
    std::cout << "Prime" << std::endl;
    for(int i = 0; i < edgesP.size(); ++i)
        std::cout << edgesP[i]->From << " " << edgesP[i]->To << std::endl;
    if(edgesB.size() != edgesK.size() || edgesK.size() != edgesP.size())
    {
        std::cout << "Test Failed: " << "Diff sizes" << std::endl;
        return;
    }
    for(int i = 0; i < edgesB.size(); ++i)
    {
        if(edgesB[i]->From != edgesP[i]->From || edgesB[i]->From != edgesK[i]->From)
            std::cout << "Test Failed: " << "Diff Froms at " << i << std::endl;
        if(edgesB[i]->To != edgesP[i]->To || edgesB[i]->To != edgesK[i]->To)
            std::cout << "Test Failed: " << "Diff Tos at " << i << std::endl;
        if(((ValuedEdge<double>*)edgesB[i])->GetValue() != ((ValuedEdge<double>*)edgesP[i])->GetValue() ||
                ((ValuedEdge<double>*)edgesB[i])->GetValue() != ((ValuedEdge<double>*)edgesK[i])->GetValue() )
            std::cout << "Test Failed: " << "Diff Vals at " << i << std::endl;
    }
    delete mstP;
    delete mstK;
    delete mstB;
    delete graph;
}

void TimeTest()
{
    GraphValuedEdge<double> *mstk, *mstb, *mstp;
    const int testsPerPercentage = 10;
    for(int i = 10; i <= 100; i += 10)
    {
        clock_t start_t, end_t;
        double sumKr = 0;
        double sumP = 0;
        double sumB = 0;
        for(int j = 0; j < testsPerPercentage; ++j)
        {
            GraphValuedEdge<double>* graph = GenerateGraph(1000, i);
            start_t = clock();
            mstk = Kruskal(graph);
            end_t = clock();
            sumKr += (float)(end_t - start_t)/CLOCKS_PER_SEC;
            delete mstk;
            start_t = clock();
            mstp = Prim(graph);
            end_t = clock();
            sumP += (float)(end_t - start_t)/CLOCKS_PER_SEC;
            delete mstp;
            start_t = clock();
            mstb = Boruvka(graph);
            end_t = clock();
            sumB += (float)(end_t - start_t)/CLOCKS_PER_SEC;
            delete mstb;
            delete graph;
        }
        std::cout << "percentage " << i << std::endl;
        std::cout << "Kruskal " << sumKr << std::endl;
        std::cout << "Boruvka " << sumB << std::endl;
        std::cout << "Prim " << sumP << std::endl;
    }
}

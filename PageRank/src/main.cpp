#include <iostream>
#include <vector>
#include <time.h>
#include <map>
#include <algorithm>
#include <fstream>
#include "OrientedGraph.h"
#include "GraphManager.h"
#include "PageRank.hpp"

#define RANGE 7

void Normalize(std::string& s)
{
    if (s.empty())
        return;
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    if(s.find_first_of(" ,\n\t\"().:;") != std::string::npos)
        s.erase(s.find_first_of(" ,\n\t\"().:;"));
    s.erase(s.find_last_not_of(" ,\n\t\"().:;") + 1);
}

void TestCoverage()
{
    unsigned int tests = 1;
    unsigned int steps = 100;
    for(int i = 0; i < tests; ++i)
    {
        std::cout << "Test " << i << std::endl;
        PageRank<int>* g = new PageRank<int>(6541, 0.2);
        //g->RandomizeGraph(0.05);
        std::ifstream inp("out.txt");
        g->ReadFromFile(inp);
        inp.close();
        std::vector<double> rank = g->GetRank();
        double sum = 0;
        for(int k = 0; k < rank.size(); ++k)
        {
            sum += rank[k];
            std::cout << rank[k] << " ";
        }
        std::cout << std::endl;
        std::cout << sum << std::endl;
        for(int j = 0; j < steps; ++j)
        {
            sum = 0;
            g->PageRankForSteps(1);
            rank = g->GetRank();
            for(int k = 0; k < rank.size(); ++k)
            {
                sum += rank[k];
                std::cout << rank[k] << " ";
            }
            std::cout << std::endl;
            std::cout << sum << std::endl;
        }
        delete g;
    }
}
void TestDictionary(std::string st)
{
    std::ifstream file(("./" + st).c_str());
    unsigned long long i = 0;
    std::string test[RANGE];
    PageRank<std::string>* pr = new PageRank<std::string>(0, 0.1);
    for(int i = 0; i < RANGE - 1; ++i)
    {
        do
        {
            file >> test[i];
            Normalize(test[i]);
        }while(test[i] == "");
        pr->AddPage(test[i % RANGE]);
    }
    i = RANGE - 1;
    while(file.peek() != EOF)
    {
        do
        {
            file >> test[i];
            Normalize(test[i]);
        }while(test[i] == "");
        pr->AddPage(test[i]);
        for(int j = 0; j < RANGE; ++j)
        {
            if(j == i)
                continue;
            //TODO: pr->AddEdge(pr->GetIndexOfPage(test[j]), pr->GetIndexOfPage(test[i]));
            //TODO: pr->AddEdge(pr->GetIndexOfPage(test[i]), pr->GetIndexOfPage(test[j]));
        }
        i = ++i % RANGE;
    }
    file.close();
#ifdef DEBUG
    std::ofstream out("out.txt");
    pr->WriteToFile(out);
    out.close();
#endif
    pr->InitRank();

    pr->PageRankToConverge();
    std::vector<double> rank = pr->GetRank();
    std::multimap<double, std::string> sorted;
    for(std::map<std::string, unsigned int>::iterator it = pr->Data.begin(); it != pr->Data.end(); ++it)
        sorted.insert(std::pair<double, std::string>(rank[it->second], it->first));
    for(std::multimap<double, std::string>::iterator it = sorted.begin(); it != sorted.end(); ++it)
        std::cout << it->second << " " << it->first << " " << std::endl;
    delete pr;
}

int main(int argc, char** argv)
{   
    //TestCoverage();
    if(argc > 0)
        TestDictionary(argv[1]);
}

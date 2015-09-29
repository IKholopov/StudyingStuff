#include"BaseGraph.h"

unsigned int BaseGraph::Size() const
{
    return graph->Size();
}
unsigned int BaseGraph::NumberOfEdges() const
{
    return graph->NumberOfEdges();
}
std::vector<unsigned int> BaseGraph::GetChilds(unsigned int vertex) const
{
    return graph->GetChilds(vertex);
}
std::vector<unsigned int> BaseGraph::GetParents(unsigned int vertex) const
{
    return graph->GetParents(vertex);
}
std::vector<Edge *> BaseGraph::GetAllEdges() const
{
    return graph->GetAllEdges();
}
std::vector<Edge *> BaseGraph::GetAllEdgesSorted() //const
{
    return graph->GetAllEdgesSorted();
}
void BaseGraph::AddNodes(size_t amount)
{
    graph->AddNodes(amount);
}
bool BaseGraph::AddEdge(int from, int to)
{
    return graph->AddEdge(from, to);
}
bool BaseGraph::AddEdge(Edge *edge)
{
    return graph->AddEdge(edge);
}
bool BaseGraph::CheckEdge(int from, int to)
{
    return graph->CheckEdge(from, to);
}
Edge *BaseGraph::GetEdge(int from, int to)
{
    return graph->GetEdge(from, to);
}
void BaseGraph::DeleteAllEdges()
{
    return graph->DeleteAllEdges();
}
void BaseGraph::InitializeNewGraph(unsigned int size)
{
    this->graph->InitializeNewGraph(size);
}
BaseGraph::BaseGraph(IGraph &graph)
{
    this->graph = &graph;
}
BaseGraph::BaseGraph(IGraph *graph)
{
    this->graph = graph;
}
BaseGraph::BaseGraph(unsigned int size, IGraph &graph)
{
    this->graph = &graph;
    this->graph->InitializeNewGraph(size);
}
BaseGraph::BaseGraph(unsigned int size, IGraph* graph)
{
    this->graph = graph;
    this->graph->InitializeNewGraph(size);
}

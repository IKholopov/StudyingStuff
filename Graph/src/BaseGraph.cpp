#include"BaseGraph.h"

unsigned long long BaseGraph::Size() const
{
    return graph->Size();
}
unsigned long long BaseGraph::NumberOfEdges() const
{
    return graph->NumberOfEdges();
}
std::vector<unsigned long long> BaseGraph::GetChilds(unsigned long long vertex) const
{
    return graph->GetChilds(vertex);
}
std::vector<unsigned long long> BaseGraph::GetParents(unsigned long long vertex) const
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
bool BaseGraph::AddEdge(long long from, long long to)
{
    return graph->AddEdge(from, to);
}
bool BaseGraph::AddEdge(Edge *edge)
{
    return graph->AddEdge(edge);
}
bool BaseGraph::CheckEdge(long long from, long long to)
{
    return graph->CheckEdge(from, to);
}
Edge *BaseGraph::GetEdge(long long from, long long to)
{
    return graph->GetEdge(from, to);
}
void BaseGraph::DeleteEdge(long long from, long long to)
{
    this->graph->DeleteEdge(from, to);
}
void BaseGraph::DeleteNodeEdges(unsigned long long v)
{
    this->graph->DeleteNodeEdges(v);
}
void BaseGraph::DeleteAllEdges()
{
    return graph->DeleteAllEdges();
}
void BaseGraph::InitializeNewGraph(unsigned long long size)
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
BaseGraph::BaseGraph(unsigned long long size, IGraph &graph)
{
    this->graph = &graph;
    this->graph->InitializeNewGraph(size);
}
BaseGraph::BaseGraph(unsigned long long size, IGraph* graph)
{
    this->graph = graph;
    this->graph->InitializeNewGraph(size);
}

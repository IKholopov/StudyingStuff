#include "BaseGraph.h"

unsigned long long BaseGraph::size() const
{
    return graph_->size();
}
unsigned long long BaseGraph::numberOfEdges() const
{
    return graph_->numberOfEdges();
}
std::vector<unsigned long long> *BaseGraph::getChilds(unsigned long long vertex) const
{
    return graph_->getChilds(vertex);
}
std::vector<unsigned long long> *BaseGraph::getParents(unsigned long long vertex) const
{
    return graph_->getParents(vertex);
}
std::vector<Edge *> *BaseGraph::getAllEdges() const
{
    return graph_->getAllEdges();
}
std::vector<Edge *> *BaseGraph::getAllEdgesSorted() //const
{
    return graph_->getAllEdgesSorted();
}
void BaseGraph::addNodes(size_t amount)
{
    graph_->addNodes(amount);
}
bool BaseGraph::addEdge(Edge *edge)
{
    return graph_->addEdge(edge);
}
bool BaseGraph::checkEdge(long long from, long long to)
{
    return graph_->checkEdge(from, to);
}
Edge *BaseGraph::getEdge(long long from, long long to)
{
    return graph_->getEdge(from, to);
}
void BaseGraph::deleteEdge(long long from, long long to)
{
    this->graph_->deleteEdge(from, to);
}
void BaseGraph::deleteNodeEdges(unsigned long long v)
{
    this->graph_->deleteNodeEdges(v);
}
void BaseGraph::deleteAllEdges()
{
    return graph_->deleteAllEdges();
}
void BaseGraph::initializeNewGraph(unsigned long long size)
{
    this->graph_->initializeNewGraph(size);
}
BaseGraph::BaseGraph(IGraph &graph)
{
    this->graph_ = &graph;
}
BaseGraph::BaseGraph(IGraph *graph)
{
    this->graph_ = graph;
}
BaseGraph::BaseGraph(unsigned long long size, IGraph &graph)
{
    this->graph_ = &graph;
    this->graph_->initializeNewGraph(size);
}
BaseGraph::BaseGraph(unsigned long long size, IGraph* graph)
{
    this->graph_ = graph;
    this->graph_->initializeNewGraph(size);
}

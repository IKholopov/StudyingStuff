#include "Edge.h"
namespace GraphLibrary {
Edge::Edge(unsigned long long from, unsigned long long to)
{
    this->From = from;
    this->To = to;
}
/* TODO: Edge* Edge::ReadEdge(std::istream& stream)
{
    unsigned long long from, to;
    stream >> from;
    stream >> to;
    return new Edge*(from, to);
}*/
Edge *Edge::getReversed()
{
    return new Edge(To, From);
}
Edge*Edge::clone()
{
    return new Edge(*this);
}
unsigned long long Edge::getId()
{
    return id_;
}
void Edge::setId(unsigned long long id)
{
    this->id_ = id;
}

}

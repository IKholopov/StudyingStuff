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
Edge *Edge::GetReversed()
{
    return new Edge(To, From);
}
Edge*Edge::Clone()
{
    return new Edge(*this);
}
unsigned long long Edge::GetId()
{
    return id;
}
void Edge::SetId(unsigned long long id)
{
    this->id = id;
}

}

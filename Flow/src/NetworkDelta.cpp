#include "NetworkDelta.h"

NetworkDelta::NetworkDelta(unsigned long long graphId, bool toDelete):graphId_(graphId), toDelete_(toDelete)
{

}

unsigned long long NetworkDelta::getGraphId()
{
    return graphId_;
}
void NetworkDelta::addNodeChange(NetworkNodeChange* change)
{
    nodeChanges_.push_back(change);
}
void NetworkDelta::addEdgeChange(NetworkEdgeChange* change)
{
    edgeChanges_.push_back(change);
}
const std::vector<NetworkNodeChange*>& NetworkDelta::getNodeChanges() const
{
    return nodeChanges_;
}
const std::vector<NetworkEdgeChange*>& NetworkDelta::getEdgeChanges() const
{
    return edgeChanges_;
}
bool NetworkDelta::isToDelete()
{
    return toDelete_;
}
unsigned long long NetworkDelta::getOldGraphId() const
{
    return oldGraphId_;
}
void NetworkDelta::setOldGraphId(unsigned long long value)
{
    oldGraphId_ = value;
}
std::string NetworkDelta::getMessage() const
{
    return message_;
}
void NetworkDelta::setMessage(const std::string& value)
{
    message_ = value;
}

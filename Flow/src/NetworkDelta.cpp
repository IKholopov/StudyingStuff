#include "NetworkDelta.h"

NetworkDelta::NetworkDelta(unsigned long long graphId, bool toDelete):graphId(graphId), toDelete(toDelete)
{

}

unsigned long long NetworkDelta::GetGraphId()
{
    return graphId;
}
void NetworkDelta::AddNodeChange(NetworkNodeChange* change)
{
    nodeChanges.push_back(change);
}
void NetworkDelta::AddEdgeChange(NetworkEdgeChange* change)
{
    edgeChanges.push_back(change);
}
const std::vector<NetworkNodeChange*>& NetworkDelta::GetNodeChanges() const
{
    return nodeChanges;
}
const std::vector<NetworkEdgeChange*>& NetworkDelta::GetEdgeChanges() const
{
    return edgeChanges;
}
bool NetworkDelta::IsToDelete()
{
    return toDelete;
}
unsigned long long NetworkDelta::GetOldGraphId() const
{
    return oldGraphId;
}
void NetworkDelta::SetOldGraphId(unsigned long long value)
{
    oldGraphId = value;
}

#ifndef GRAPH_NETWORKDELTA
#define GRAPH_NETWORKDELTA

#include <vector>
#include "NetworkEdge.h"

class NetworkNodeChange
{
    public:
        NetworkNodeChange(unsigned long long id,
                          unsigned long long potential, bool present = 1):Id(id), Potential(potential),
                          Present(present) {}
        unsigned long long Id;
        unsigned long long OldPotential;
        unsigned long long Potential;
        bool OldPresent;
        bool Present;
};
class NetworkEdgeChange
{
    public:
        NetworkEdgeChange(unsigned long long id, unsigned long long from, unsigned long long to, unsigned long long capacity,
                          unsigned long long flow, unsigned long long present = 1):Id(id), Capacity(capacity),
                          Flow(flow), Present(present), From(from), To(to) {}
        unsigned long long Id;
        unsigned long long Capacity;
        unsigned long long Flow;
        unsigned long long Present;
        unsigned long long From;
        unsigned long long To;
        unsigned long long OldCapacity = 0;
        unsigned long long OldFlow = 0;
        unsigned long long OldPresent = 0;
};

class NetworkDelta
{
    public:
        NetworkDelta(unsigned long long graphId, bool toDelete = 0);
        unsigned long long GetGraphId();
        void AddNodeChange(NetworkNodeChange* change);
        void AddEdgeChange(NetworkEdgeChange* change);
        const std::vector<NetworkNodeChange*>& GetNodeChanges() const;
        const std::vector<NetworkEdgeChange*>& GetEdgeChanges() const;
        bool IsToDelete();
        unsigned long long GetOldGraphId() const;
        void SetOldGraphId(unsigned long long value);

    private:
        unsigned long long graphId;
        unsigned long long oldGraphId = 0;
        std::vector<NetworkEdgeChange*> edgeChanges;
        std::vector<NetworkNodeChange*> nodeChanges;
        bool toDelete;
};

#endif

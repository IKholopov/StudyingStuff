#ifndef GRAPH_NETWORKDELTA
#define GRAPH_NETWORKDELTA

#include "NetworkEdge.h"

#include <vector>

struct NetworkNodeChange
{
    public:
        NetworkNodeChange(unsigned long long id,
                          unsigned long long potential, bool present = 1, bool highlighted = false):Id(id), Potential(potential),
                          Present(present), Highlighted(highlighted) {}
        unsigned long long Id;
        unsigned long long OldPotential;
        unsigned long long Potential;
        bool OldPresent;
        bool Present;
        bool OldHighlighted = false;
        bool Highlighted;
};
struct NetworkEdgeChange
{
    public:
        NetworkEdgeChange(unsigned long long id, unsigned long long from, unsigned long long to, unsigned long long capacity,
                          unsigned long long flow, unsigned long long present = 1, bool highlighted = false):Id(id), Capacity(capacity),
                          Flow(flow), Present(present), From(from), To(to), Highlighted(highlighted) {}
        unsigned long long Id;
        unsigned long long Capacity;
        unsigned long long Flow;
        unsigned long long Present;
        unsigned long long From;
        unsigned long long To;
        unsigned long long OldCapacity = 0;
        unsigned long long OldFlow = 0;
        unsigned long long OldPresent = 0;
        bool OldHighlighted = false;
        bool Highlighted;
};

class NetworkDelta
{
    public:
        NetworkDelta(unsigned long long graphId_, bool toDelete_ = 0);

        unsigned long long getGraphId();
        void addNodeChange(NetworkNodeChange* change);
        void addEdgeChange(NetworkEdgeChange* change);
        const std::vector<NetworkNodeChange*>& getNodeChanges() const;
        const std::vector<NetworkEdgeChange*>& getEdgeChanges() const;
        bool isToDelete();
        unsigned long long getOldGraphId() const;
        void setOldGraphId(unsigned long long value);
        std::string getMessage() const;
        void setMessage(const std::string& value);

    private:
        unsigned long long graphId_;
        unsigned long long oldGraphId_ = 0;
        std::vector<NetworkEdgeChange*> edgeChanges_;
        std::vector<NetworkNodeChange*> nodeChanges_;
        bool toDelete_;
        std::string message_;
};

#endif

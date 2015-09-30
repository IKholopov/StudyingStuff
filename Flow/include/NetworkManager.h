#ifndef FLOW_NETWORKMANAGER_H
#define FLOW_NETWORKMANAGER_H

#include <vector>
#include "NetworkEdge.h"
#include "NetworkGraph.h"
#include "AdjacencyMatrixOriented.h"

template <class FlowType>
class NetworkManager
{
    public:
        static NetworkManager<FlowType>& instance();
        NetworkGraph<FlowType>* ThreeIndiansAlgorithm(std::size_t size, std::vector<ValuedEdge<NetworkEdgeValue<FlowType>* > *> &edges,
                                                      unsigned int source, unsigned int sink);
    private:
        NetworkManager() {}
};

template <class FlowType>
NetworkManager<FlowType> &NetworkManager<FlowType>::instance()
{
    static NetworkManager<FlowType> instance;
    return instance;
}

template <class FlowType>
NetworkGraph<FlowType>* NetworkManager<FlowType>::ThreeIndiansAlgorithm(std::size_t size, std::vector<ValuedEdge<NetworkEdgeValue<FlowType>*>* >& edges,
                                                                        unsigned int source, unsigned int sink)
{
    std::vector<Edge*> edgeData;
    for(auto edge: edgeData)
        edgeData.push_back(edge);
    NetworkGraph<FlowType>* graph = new NetworkGraph<FlowType>(new AdjacencyMatrixOriented(size, edgeData));
    NetworkGraph<FlowType>* residualNetwork = static_cast< NetworkGraph<FlowType>* >(graph->Clone());
    while(true)
    {
        auto layered = residualNetwork->GetLayeredNetwork(source, sink);
        auto distances = layered.second;
        auto layeredNetwork = layered.first;
        if(distances->at(sink) == 0)
            break;
        std::vector<FlowType> capacities(layeredNetwork->Size(), 0);
        std::vector<FlowType> sumIn(layeredNetwork->Size(), 0);
        std::vector<FlowType> sumOut(layeredNetwork->Size(), 0);
        std::function<void(unsigned int i)> updateCapacity = [&capacities, &layeredNetwork, &sumIn, &sumOut, &updateCapacity]
                (unsigned int i){
            std::vector<unsigned int> childs = layeredNetwork->GetChilds(i);
            for(auto v: childs)
                sumOut[i] += static_cast<ValuedEdge<NetworkEdgeValue<FlowType>*>*>(layeredNetwork->GetEdge(i, v))->GetValue()->Capacity;
            std::vector<unsigned int> parents = layeredNetwork->GetParents(i);
            for(auto v: parents)
                sumIn[i] += static_cast<ValuedEdge<NetworkEdgeValue<FlowType>*>*>(layeredNetwork->GetEdge(v, i))->GetValue()->Capacity;
            capacities[i] = sumIn[i] < sumOut[i] ? sumIn[i] : sumOut[i];
            if(capacities[i] == 0)
            {
                layeredNetwork->DeleteNodeEdges(i);
                for(auto v: childs)
                    updateCapacity(v);
                for(auto v: parents)
                    updateCapacity(v);
            }
        };
        for(int i = 0; i < layeredNetwork->Size(); ++i)
        {
            if(i == source || i == sink || capacities[i] != 0)
                continue;
            updateCapacity(i);
        }
        while(layeredNetwork->NumberOfEdges() != 0){
            FlowType min = layeredNetwork->Size();
            unsigned int minIndex = 0;
            for(int j = 0; j < capacities.size(); ++j)
                if(capacities[j] != 0 && min > capacities[j])
                {
                    min = capacities[j];
                    minIndex = j;
                }
            assert(min != layeredNetwork->Size());
            std::vector<unsigned int> parents = layeredNetwork->GetParents(minIndex);
            std::vector<unsigned int> childs = layeredNetwork->GetChilds(minIndex);
            FlowType flow = min;
            for(auto v: parents)
            {
                auto edge = static_cast<ValuedEdge<NetworkEdgeValue<FlowType>*>*>(layeredNetwork->GetEdge(v, minIndex));
                if(edge == NULL)
                    continue;
                if(flow > edge->GetValue()->Capacity)
                {
                    residualNetwork->AddResidiual(v, minIndex, edge->GetValue()->Capacity);
                    flow -= edge->GetValue()->Capacity;
                    sumOut[v] -= edge->GetValue()->Capacity;
                    layeredNetwork->DeleteEdge(v, minIndex);
                }
                else
                {
                    residualNetwork->AddResidiual(v, minIndex, flow);
                    sumOut[v] -= flow;
                    edge->GetValue()->Capacity -= flow;
                    break;
                }
            }
            flow = min;
             for(auto v: childs)
             {
                auto edge = static_cast<ValuedEdge<NetworkEdgeValue<FlowType>*>*>(layeredNetwork->GetEdge(minIndex, v));
                if(edge == NULL)
                    continue;
                if(flow > edge->GetValue()->Capacity)
                {
                    residualNetwork->AddResidiual(minIndex, v, edge->GetValue()->Capacity);
                    flow -= edge->GetValue()->Capacity;
                    sumIn[v] -= edge->GetValue()->Capacity;
                    layeredNetwork->DeleteEdge(minIndex, v);
                }
                else
                {
                    residualNetwork->AddResidiual(minIndex, v, flow);
                    sumIn[v] -= flow;
                    edge->GetValue()->Capacity -= flow;
                    break;
                }
            }
        }
    }

}

#endif

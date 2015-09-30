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
        NetworkGraph<FlowType>* ThreeIndiansAlgorithm(std::size_t size, std::vector<ValuedEdge<NetworkEdgeValue<FlowType> > *> &edges,
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
NetworkGraph<FlowType>* NetworkManager<FlowType>::ThreeIndiansAlgorithm(std::size_t size, std::vector<ValuedEdge<NetworkEdgeValue<FlowType>>* >& edges,
                                                                        unsigned int source, unsigned int sink)
{
    std::vector<Edge*> edgeData;
    for(auto edge: edges)
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
        std::vector<FlowType> flowExceeds(layeredNetwork->Size(), 0);
        std::function<void(unsigned int i)> updateCapacity = [&capacities, &layeredNetwork, &sumIn, &sumOut, &updateCapacity, &source, &sink]
                (unsigned int i){
            if(i == source || i == sink)
                return;
            std::vector<unsigned int> childs = layeredNetwork->GetChilds(i);
            sumOut[i] = 0;
            sumIn[i] = 0;
            for(auto v: childs)
                if(layeredNetwork->CheckEdge(i, v))
                    sumOut[i] += static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(layeredNetwork->GetEdge(i, v))->GetValue().Capacity;
            std::vector<unsigned int> parents = layeredNetwork->GetParents(i);
            for(auto v: parents)
                if(layeredNetwork->CheckEdge(v, i))
                    sumIn[i] += static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(layeredNetwork->GetEdge(v, i))->GetValue().Capacity;
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
        std::function<void(unsigned int v)> backward = [&layeredNetwork, &residualNetwork, &flowExceeds](unsigned int index)
        {
            std::vector<unsigned int> parents = layeredNetwork->GetParents(index);
            FlowType flow = flowExceeds[index];
            for(auto v: parents)
            {
                auto edge = static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(layeredNetwork->GetEdge(v, index));
                if(edge == NULL)
                    continue;
                if(flow >= edge->GetValue().Capacity)
                {
                    residualNetwork->AddResidiual(v, index, edge->GetValue().Capacity);
                    flow -= edge->GetValue().Capacity;
                    flowExceeds[v] += edge->GetValue().Capacity;
                    layeredNetwork->DeleteEdge(v, index);
                }
                else
                {
                    residualNetwork->AddResidiual(v, index, flow);
                    edge->SetValue(NetworkEdgeValue<FlowType>(edge->GetValue().Capacity - flow, edge->GetValue().Flow));
                    flowExceeds[v] += flow;
                    break;
                }
            }
        };
        std::function<void(unsigned int v)> forward = [&layeredNetwork, &residualNetwork, &flowExceeds](unsigned int index)
        {
            std::vector<unsigned int> childs = layeredNetwork->GetChilds(index);
            FlowType flow = flowExceeds[index];
            for(auto v: childs)
            {
                auto edge = static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(layeredNetwork->GetEdge(index, v));
                if(edge == NULL)
                    continue;
                if(flow >= edge->GetValue().Capacity)
                {
                    residualNetwork->AddResidiual(index, v, edge->GetValue().Capacity);
                    flow -= edge->GetValue().Capacity;
                    flowExceeds[v] += edge->GetValue().Capacity;
                    layeredNetwork->DeleteEdge(index, v);
                }
                else
                {
                    residualNetwork->AddResidiual(index, v, flow);
                    edge->SetValue(NetworkEdgeValue<FlowType>(edge->GetValue().Capacity - flow, edge->GetValue().Flow));
                    flowExceeds[v] += flow;
                    break;
                }
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
            flowExceeds[minIndex] = min;
            std::vector<unsigned int> parents = layeredNetwork->GetParents(minIndex);
            std::vector<unsigned int> childs = layeredNetwork->GetChilds(minIndex);
            backward(minIndex);
            forward(minIndex);
            flowExceeds[minIndex] = 0;
            capacities[minIndex] = 0;
            sumIn[minIndex] = 0;
            sumOut[minIndex] = 0;
            for(long i = (distances->at(minIndex) - 1); i > 0; --i)
                for(unsigned int j = 0; j < distances->size(); ++j)
                    if(distances->at(j) == i)
                    {
                        backward(j);
                        flowExceeds[j] = 0;
                    }
            for(unsigned int i = distances->at(minIndex) + 1; i < residualNetwork->Size() - 1; ++i)
                for(unsigned int j = 0; j < distances->size(); ++j)
                    if(distances->at(j) == i)
                    {
                        forward(j);
                        flowExceeds[j] = 0;
                    }
            updateCapacity(minIndex);
            for(auto v: parents)
                updateCapacity(v);
            for(auto v: childs)
                updateCapacity(v);
        }
    }
    return NULL;
}

#endif

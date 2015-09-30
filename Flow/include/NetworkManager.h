#ifndef FLOW_NETWORKMANAGER_H
#define FLOW_NETWORKMANAGER_H

#include <vector>
#include <queue>
#include <istream>
#include <ostream>
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
        void ThreeIndiansAlgorithm(NetworkGraph<FlowType>& graph,
                                                      unsigned int source, unsigned int sink);
        std::pair<std::vector<Edge>*,NetworkGraph<FlowType>*> ReadGraph(std::istream& stream, IGraph *realization);
        void WriteGraphFlow(std::ostream& stream, NetworkGraph<FlowType>* graph, std::vector<Edge>* edges);

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
NetworkGraph<FlowType> *NetworkManager<FlowType>::ThreeIndiansAlgorithm(std::size_t size, std::vector<ValuedEdge<NetworkEdgeValue<FlowType> > *> &edges, unsigned int source, unsigned int sink)
{
    std::vector<Edge*> edgeData;
    for(auto edge = edges.begin(); edge != edges.end(); ++ edge)
        edgeData.push_back(*edge);
    NetworkGraph<FlowType>* graph = new NetworkGraph<FlowType>(new AdjacencyMatrixOriented(size, edgeData));
    this->ThreeIndiansAlgorithm(*graph, source,sink);
    return graph;
}
template <class FlowType>
void NetworkManager<FlowType>::ThreeIndiansAlgorithm(NetworkGraph<FlowType> &graph,
                                                                       unsigned int source, unsigned int sink)
{
    assert(source < graph.Size() && sink < graph.Size());
    NetworkGraph<FlowType>* residualNetwork = static_cast< NetworkGraph<FlowType>* >(graph.Clone());
    while(true)
    {
        auto layered = residualNetwork->GetLayeredNetwork(source, sink);
        auto distances = layered.second;
        auto layeredNetwork = layered.first;
        if(distances->at(sink) == 0)
        {
            delete layeredNetwork;
            delete distances;
            break;
        }
        std::vector<FlowType> capacities(layeredNetwork->Size(), 0);
        std::vector<FlowType> sumIn(layeredNetwork->Size(), 0);
        std::vector<FlowType> sumOut(layeredNetwork->Size(), 0);
        std::vector<FlowType> flowExceeds(layeredNetwork->Size(), 0);
        std::function<void(unsigned int i)> updateCapacity = [&capacities, &layeredNetwork, &sumIn, &sumOut, &updateCapacity, &source, &sink]
                (unsigned int i){
            if(i == source)
                return;
            std::vector<unsigned int> childs = layeredNetwork->GetChilds(i);
            sumOut[i] = 0;
            sumIn[i] = 0;
            for(auto v = childs.begin(); v != childs.end(); ++v)
                if(layeredNetwork->CheckEdge(i, *v))
                    sumOut[i] += static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(layeredNetwork->GetEdge(i, *v))->GetValue().Capacity;
            std::vector<unsigned int> parents = layeredNetwork->GetParents(i);
            for(auto v = parents.begin(); v != parents.end(); ++v)
                if(layeredNetwork->CheckEdge(*v, i))
                    sumIn[i] += static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(layeredNetwork->GetEdge(*v, i))->GetValue().Capacity;
            capacities[i] = sumIn[i] < sumOut[i] ? sumIn[i] : sumOut[i];
            if(capacities[i] == 0)
            {
                if(i == sink)
                {
                    capacities[i] = sumIn[i];
                    return;
                }
                layeredNetwork->DeleteNodeEdges(i);
                for(auto v = childs.begin(); v != childs.end(); ++v)
                    updateCapacity(*v);
                for(auto v = parents.begin(); v != parents.end(); ++v)
                    updateCapacity(*v);
            }
        };
        std::function<void(unsigned int v)> backward = [&layeredNetwork, &residualNetwork, &flowExceeds](unsigned int index)
        {
            std::vector<unsigned int> parents = layeredNetwork->GetParents(index);
            FlowType flow = flowExceeds[index];
            for(auto v = parents.begin(); v != parents.end(); ++v)
            {
                auto edge = static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(layeredNetwork->GetEdge(*v, index));
                if(edge == NULL)
                    continue;
                if(flow >= edge->GetValue().Capacity)
                {
                    residualNetwork->AddFlowToResidiual(*v, index, edge->GetValue().Capacity);
                    flow -= edge->GetValue().Capacity;
                    flowExceeds[*v] += edge->GetValue().Capacity;
                    layeredNetwork->DeleteEdge(*v, index);
                }
                else
                {
                    residualNetwork->AddFlowToResidiual(*v, index, flow);
                    edge->SetValue(NetworkEdgeValue<FlowType>(edge->GetValue().Capacity - flow, edge->GetValue().Flow));
                    flowExceeds[*v] += flow;
                    break;
                }
            }
        };
        std::function<void(unsigned int v)> forward = [&layeredNetwork, &residualNetwork, &flowExceeds](unsigned int index)
        {
            std::vector<unsigned int> childs = layeredNetwork->GetChilds(index);
            FlowType flow = flowExceeds[index];
            for(auto v = childs.begin(); v != childs.end(); ++v)
            {
                auto edge = static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(layeredNetwork->GetEdge(index, *v));
                if(edge == NULL)
                    continue;
                if(flow >= edge->GetValue().Capacity)
                {
                    residualNetwork->AddFlowToResidiual(index, *v, edge->GetValue().Capacity);
                    flow -= edge->GetValue().Capacity;
                    flowExceeds[*v] += edge->GetValue().Capacity;
                    layeredNetwork->DeleteEdge(index, *v);
                }
                else
                {
                    residualNetwork->AddFlowToResidiual(index, *v, flow);
                    edge->SetValue(NetworkEdgeValue<FlowType>(edge->GetValue().Capacity - flow, edge->GetValue().Flow));
                    flowExceeds[*v] += flow;
                    break;
                }
            }
        };
        for(int i = 0; i < layeredNetwork->Size(); ++i)
        {
            if(i == source || capacities[i] != 0)
                continue;
            updateCapacity(i);
        }
        while(layeredNetwork->NumberOfEdges() != 0){
            FlowType min = 0;
            unsigned int minIndex = 0;
            for(int j = 0; j < capacities.size(); ++j)
                if(capacities[j] != 0)
                {
                    min = capacities[j];
                    break;
                }
            for(int j = 0; j < capacities.size(); ++j)
                if(capacities[j] != 0 && min > capacities[j])
                {
                    min = capacities[j];
                    minIndex = j;
                }
            assert(min != 0);
            flowExceeds[minIndex] = min;
            backward(minIndex);
            forward(minIndex);
            flowExceeds[minIndex] = 0;
            capacities[minIndex] = 0;
            sumIn[minIndex] = 0;
            sumOut[minIndex] = 0;
            std::queue<unsigned int> updateQueue;
            updateQueue.push(minIndex);
            for(long i = (distances->at(minIndex) - 1); i > 0; --i)
                for(unsigned int j = 0; j < distances->size(); ++j)
                    if(distances->at(j) == i)
                    {
                        backward(j);
                        updateQueue.push(j);
                        flowExceeds[j] = 0;
                    }
            for(long i = distances->at(minIndex) + 1; i < residualNetwork->Size() - 1; ++i)
                for(unsigned int j = 0; j < distances->size(); ++j)
                    if(distances->at(j) == i)
                    {
                        forward(j);
                        updateQueue.push(j);
                        flowExceeds[j] = 0;
                    }
            while(!updateQueue.empty())
            {
                updateCapacity(updateQueue.front());
                updateQueue.pop();
            }
        }
        delete layeredNetwork;
        delete distances;
    }
    graph.FlowFromResidual(*residualNetwork);
    delete residualNetwork;
}
template <class FlowType>
std::pair<std::vector<Edge> *, NetworkGraph<FlowType> *> NetworkManager<FlowType>::ReadGraph(std::istream &stream, IGraph* realization)
{
    unsigned int n, m, from, to;
    FlowType val;
    stream >> n;
    stream >> m;
    std::vector<Edge>* edges = new std::vector<Edge>();
    NetworkGraph<FlowType>* graph = new NetworkGraph<FlowType>(n, realization);
    for(unsigned int i = 0; i < m; ++i)
    {
        stream >> from;
        stream >> to;
        stream >> val;
        edges->push_back(Edge(from - 1, to - 1));
        graph->AddEdge(from - 1, to - 1, NetworkEdgeValue<FlowType>(val, 0));
    }
    return std::pair<std::vector<Edge>*, NetworkGraph<FlowType>*>(edges, graph);
}
template <class FlowType>
void NetworkManager<FlowType>::WriteGraphFlow(std::ostream &stream, NetworkGraph<FlowType> *graph, std::vector<Edge> *edges)
{
    auto v = graph->GetChilds(0);
    FlowType sum = 0;
    for(auto a = v.begin(); a != v.end(); ++a)
        sum += graph->GetEdgeValue(0, *a).Flow;
    stream << sum << std::endl;
    for(auto a = (*edges).begin(); a != (*edges).end(); ++a)
        stream << graph->GetEdgeValue((*a).From, (*a).To).Flow << std::endl;
}

#endif

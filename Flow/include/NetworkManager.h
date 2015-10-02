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
                                                      unsigned long long source, unsigned long long sink);
        void ThreeIndiansAlgorithm(NetworkGraph<FlowType>& graph,
                                                      unsigned long long source, unsigned long long sink);
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
NetworkGraph<FlowType> *NetworkManager<FlowType>::ThreeIndiansAlgorithm(std::size_t size, std::vector<ValuedEdge<NetworkEdgeValue<FlowType> > *> &edges, unsigned long long source, unsigned long long sink)
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
                                                                       unsigned long long source, unsigned long long sink)
{

    assert(source < graph.Size() && sink < graph.Size());
    NetworkGraph<FlowType>* residualNetwork = static_cast< NetworkGraph<FlowType>* >(graph.Clone());
    while(true)
    {
        auto layered = residualNetwork->GetLayeredNetwork(source, sink);
        auto distances = layered.second;
        auto layeredNetwork = layered.first;
        std::vector<std::vector<bool>> layeredDeleted(layeredNetwork->Size());
        for(int i = 0; i < layeredDeleted.size(); ++i)
            layeredDeleted[i].resize(layeredNetwork->Size(), 0);
        unsigned long long remainingEdges = layeredNetwork->GetAllEdgesConst()->size();
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
        std::function<void(unsigned long long i)> updateCapacity = [&layeredDeleted, &remainingEdges,&capacities, &layeredNetwork, &sumIn, &sumOut, &updateCapacity, &source, &sink]
                (unsigned long long i){
            if(i == source)
                return;
            auto childs = layeredNetwork->GetOutgoing(i);
            sumOut[i] = 0;
            sumIn[i] = 0;
            std::vector<unsigned int> downNodes;
            std::vector<unsigned int> upNodes;
            for(auto v = childs->begin(); v != childs->end(); ++v)
            {
                if(!layeredDeleted[i][(*v)->To])
                {
                    sumOut[i] += static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(*v)->GetValue().Capacity;
                    downNodes.push_back((*v)->To);
                }
            }
            auto parents = layeredNetwork->GetIngoing(i);
            for(auto v = parents->begin(); v != parents->end(); ++v)
            {
                if(!layeredDeleted[(*v)->From][i])
                {
                    sumIn[i] += (static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(*v))->GetValue().Capacity;
                    upNodes.push_back((*v)->From);
                }
            }
            capacities[i] = sumIn[i] < sumOut[i] ? sumIn[i] : sumOut[i];
            if(capacities[i] == 0)
            {
                if(i == sink)
                {
                    capacities[i] = sumIn[i];
                    return;
                }
                for(auto v = childs->begin(); v != childs->end(); ++v)
                {
                    if(!layeredDeleted[i][(*v)->To])
                    {
                        layeredDeleted[i][(*v)->To] = 1;
                        --remainingEdges;
                        updateCapacity((*v)->To);
                    }
                }
                for(auto v = parents->begin(); v != parents->end(); ++v)
                {
                    if(!layeredDeleted[(*v)->From][i])
                    {
                        layeredDeleted[(*v)->From][i] = 1;
                        --remainingEdges;
                        updateCapacity((*v)->From);
                    }
                }
                //layeredNetwork->DeleteNodeEdges(i);
            }
        };
        std::function<void(unsigned long long v)> backward = [&layeredDeleted, &remainingEdges, &layeredNetwork, &residualNetwork, &flowExceeds](unsigned long long index)
        {
            auto parents = layeredNetwork->GetIngoing(index);
            std::vector<unsigned int> edgesToDelete;
            FlowType flow = flowExceeds[index];
            for(auto e = parents->begin(); e != parents->end(); ++e)
            {
                auto edge = static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(*e);
                if(edge == NULL || layeredDeleted[edge->From][edge->To])
                    continue;
                if(flow >= edge->GetValue().Capacity)
                {
                    residualNetwork->AddFlowToResidiual(edge->From, index, edge->GetValue().Capacity);
                    flow -= edge->GetValue().Capacity;
                    flowExceeds[edge->From] += edge->GetValue().Capacity;
                    edgesToDelete.push_back(edge->From);
                }
                else
                {
                    residualNetwork->AddFlowToResidiual(edge->From, index, flow);
                    edge->SetValue(NetworkEdgeValue<FlowType>(edge->GetValue().Capacity - flow, edge->GetValue().Flow));
                    flowExceeds[edge->From] += flow;
                    break;
                }
            }
            for(auto e = edgesToDelete.begin(); e != edgesToDelete.end(); ++e)
            {
                if(!layeredDeleted[(*e)][index])
                {
                    layeredDeleted[(*e)][index] = 1;
                    --remainingEdges;
                }
            }
        };
        std::function<void(unsigned long long v)> forward = [&layeredDeleted, &remainingEdges, &layeredNetwork, &residualNetwork, &flowExceeds](unsigned long long index)
        {
            auto childs = layeredNetwork->GetOutgoing(index);
            std::vector<unsigned int> edgesToDelete;
            FlowType flow = flowExceeds[index];
            for(auto e = childs->begin(); e != childs->end(); ++e)
            {
                auto edge = static_cast<ValuedEdge<NetworkEdgeValue<FlowType>>*>(*e);
                if(edge == NULL || layeredDeleted[edge->From][edge->To])
                    continue;
                if(flow >= edge->GetValue().Capacity)
                {
                    residualNetwork->AddFlowToResidiual(index, edge->To, edge->GetValue().Capacity);
                    flow -= edge->GetValue().Capacity;
                    flowExceeds[edge->To] += edge->GetValue().Capacity;
                    edgesToDelete.push_back(edge->To);
                }
                else
                {
                    residualNetwork->AddFlowToResidiual(index, edge->To, flow);
                    edge->SetValue(NetworkEdgeValue<FlowType>(edge->GetValue().Capacity - flow, edge->GetValue().Flow));
                    flowExceeds[edge->To] += flow;
                    break;
                }
            }
            for(auto e = edgesToDelete.begin(); e != edgesToDelete.end(); ++e)
            {
                if(!layeredDeleted[index][(*e)])
                {
                    layeredDeleted[index][(*e)] = 1;
                    --remainingEdges;
                }
            }
        };
        for(long long i = 0; i < layeredNetwork->Size(); ++i)
        {
            if(i == source || capacities[i] != 0)
                continue;
            updateCapacity(i);
        }
        while(remainingEdges != 0){
            FlowType min = 0;
            unsigned long long minIndex = 0;
            for(long long j = 0; j < capacities.size(); ++j)
                if(capacities[j] != 0)
                {
                    min = capacities[j];
                    break;
                }
            for(long long j = 0; j < capacities.size(); ++j)
                if(capacities[j] != 0 && min > capacities[j])
                {
                    min = capacities[j];
                    minIndex = j;
                }
            if(min == 0)
                break;//assert(min != 0);
            flowExceeds[minIndex] = min;
            backward(minIndex);
            forward(minIndex);
            flowExceeds[minIndex] = 0;
            capacities[minIndex] = 0;
            sumIn[minIndex] = 0;
            sumOut[minIndex] = 0;
            std::queue<unsigned long long> updateQueue;
            updateQueue.push(minIndex);
            for(long i = (distances->at(minIndex) - 1); i > 0; --i)
                for(unsigned long long j = 0; j < distances->size(); ++j)
                    if(distances->at(j) == i)
                    {
                        backward(j);
                        updateQueue.push(j);
                        flowExceeds[j] = 0;
                    }
            for(long i = distances->at(minIndex) + 1; i < residualNetwork->Size() - 1; ++i)
                for(unsigned long long j = 0; j < distances->size(); ++j)
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
    unsigned long long n, m, from, to;
    FlowType val;
    stream >> n;
    stream >> m;
    std::vector<Edge>* edges = new std::vector<Edge>();
    NetworkGraph<FlowType>* graph = new NetworkGraph<FlowType>(n, realization);
    for(unsigned long long i = 0; i < m; ++i)
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
    for(auto a = v->begin(); a != v->end(); ++a)
        sum += graph->GetEdgeValue(0, *a).Flow;
    delete v;
    stream << sum << std::endl;
    for(auto a = (*edges).begin(); a != (*edges).end(); ++a)
        stream << graph->GetEdgeValue((*a).From, (*a).To).Flow << std::endl;
}

#endif

#include "GraphParser.h"
#include "TIARunScene.h"

#include <qevent.h>

TIARunScene::TIARunScene(AlgorithmRunView* parent):GraphScene(parent),
    view(parent),original(NULL), deltas(NULL), layered(NULL), residual(NULL), currentStep(0)
{
}
void TIARunScene::mousePressedOnVertex(Vertex* v)
{
    Q_UNUSED(v)
}
void TIARunScene::Initialize(const std::vector<std::vector<unsigned long long> >& graphData)
{
    if(deltas != NULL)
        delete deltas;
    deltas = GraphParser::parser().GetAlgorithmRun(graphData);
    if(original != NULL)
        delete original;
    original = new VisualGraph(this, view, graphData);
    if(residual != NULL)
        delete residual;
    residual = new VisualGraph(this, view, graphData);
    if(layered != NULL)
        delete layered;
    layered = new VisualGraph(this, view, graphData);
    residual->HideGraph();
    layered->DisableGraph();

    currentGraph = ORIGINAL;
    currentStep = 0;
}
void TIARunScene::NextStep()
{
    if(currentStep == deltas->size())
        return;
    auto delta = deltas->at(currentStep++);
    VisualGraph* graph;
    switch(delta.GetGraphId()){
        case ORIGINAL:
            layered->HideGraph();
            residual->HideGraph();
            original->DisplayGraph();
            graph = original;
            currentGraph = ORIGINAL;
            break;
         case RESIDUAL:
            layered->HideGraph();
            original->HideGraph();
            residual->DisplayGraph();
            graph = residual;
            currentGraph = RESIDUAL;
            break;
         case LAYERED:
            original->HideGraph();
            residual->HideGraph();
            if(delta.IsToDelete())
                layered->DisableGraph();
            layered->DisplayGraph();
            graph = layered;
            currentGraph = LAYERED;
            break;
        deault:
            break;
    }
    for(long long i = 0; i < delta.GetNodeChanges().size(); ++i)
        ProcessNodeChange(graph, delta.GetNodeChanges().at(i));
    for(long long i = 0; i < delta.GetEdgeChanges().size(); ++i)
        ProcessEdgeChange(graph, delta.GetEdgeChanges().at(i));
    }
void TIARunScene::PrevStep()
{
    if(currentStep == 0)
        return;
    auto delta = deltas->at(--currentStep);
    VisualGraph* graph;
    TIADeltas graphToSwitch;
    if(currentStep == 0)
        graphToSwitch = ORIGINAL;
    else
        graphToSwitch = (TIADeltas)deltas->at(currentStep - 1).GetGraphId();
    switch(delta.GetGraphId()){
        case ORIGINAL:
            graph = original;
            break;
         case RESIDUAL:
            graph = residual;
            break;
         case LAYERED:
            graph = layered;
            break;
        default:
            break;
    }
    for(long long i = 0; i < delta.GetNodeChanges().size(); ++i)
        ProcessBackwardNodeChange(graph, delta.GetNodeChanges().at(i));
    for(long long i = 0; i < delta.GetEdgeChanges().size(); ++i)
        ProcessBackwardEdgeChange(graph, delta.GetEdgeChanges().at(i));
    switch(graphToSwitch){
        case ORIGINAL:
            layered->HideGraph();
            residual->HideGraph();
            original->DisplayGraph();
            break;
         case RESIDUAL:
            layered->HideGraph();
            original->HideGraph();
            residual->DisplayGraph();
            break;
         case LAYERED:
            original->HideGraph();
            residual->HideGraph();
            layered->DisplayGraph();
            break;
        default:
            break;
    }
}
std::vector<VisualGraph*> TIARunScene::GetGraphs()
{
    std::vector<VisualGraph*> graphs;
    if(original->IsActive())
        graphs.push_back(original);
    if(residual->IsActive())
        graphs.push_back(residual);
    if(layered->IsActive())
        graphs.push_back(layered);
    return graphs;
}
void TIARunScene::ProcessEdgeChange(VisualGraph* graph, NetworkEdgeChange* change)
{
    assert(change != NULL);
    if(graph->GetEdge(change->Id) == NULL)
    {
        graph->AddEdge(change->From, change->To, change->Capacity);
        if(graph != layered)
        {
            layered->AddEdge(change->From, change->To, change->Capacity);
            layered->HideEdge(change->Id);
        }
        change->OldPresent = false;
    }
    else
        change->OldPresent = graph->GetEdge(change->Id)->GetActive();
    if(change->Present == false)
        graph->HideEdge(change->Id);
    else
        graph->DisplayEdge(change->Id);
    change->OldCapacity = graph->GetEdge(change->Id)->GetCapacity();
    change->OldFlow = graph->GetEdge(change->Id)->GetFlow();
    graph->GetEdge(change->Id)->SetCapacity(change->Capacity);
    graph->GetEdge(change->Id)->SetFlow(change->Flow);
}
void TIARunScene::ProcessNodeChange(VisualGraph* graph, NetworkNodeChange* change)
{
    assert(graph->GetNode(change->Id) != NULL);
    assert(change != NULL);
    if(graph->GetNode(change->Id) == NULL)
        return;
    change->OldPresent = graph->GetNode(change->Id)->GetActive();
    if(change->Present == 0)
        graph->HideNode(change->Id);
    else
        graph->DisplayNode(change->Id);
    change->OldPotential = graph->GetNode(change->Id)->GetPotential();
    graph->GetNode(change->Id)->SetPotential(change->Potential);
}
void TIARunScene::ProcessBackwardEdgeChange(VisualGraph* graph, NetworkEdgeChange* change)
{
    assert(change != NULL);
    assert(graph->GetEdge(change->Id) != NULL);
    if(change->OldPresent == false)
        graph->HideEdge(change->Id);
    else
        graph->DisplayEdge(change->Id);
    graph->GetEdge(change->Id)->SetCapacity(change->OldCapacity);
    graph->GetEdge(change->Id)->SetFlow(change->OldFlow);
}
void TIARunScene::ProcessBackwardNodeChange(VisualGraph* graph, NetworkNodeChange* change)
{
    assert(change != NULL);
    assert(graph->GetNode(change->Id) != NULL);
    if(graph->GetNode(change->Id) == NULL)
        return;
    if(change->OldPresent == 0)
        graph->HideNode(change->Id);
    else
        graph->DisplayNode(change->Id);
    graph->GetNode(change->Id)->SetPotential(change->OldPotential);
}
void TIARunScene::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key::Key_Forward)
        this->NextStep();
    if(event->key() == Qt::Key::Key_Back)
        this->PrevStep();
}


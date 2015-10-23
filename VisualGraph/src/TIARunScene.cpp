#include "GraphParser.h"
#include "TIARunScene.h"

#include <qevent.h>

TIARunScene::TIARunScene(QTextEdit* messageBox, AlgorithmRunView* parent):GraphScene(parent),
    view(parent),original(NULL), deltas(NULL), layered(NULL), residual(NULL), currentStep(0), messageBox(messageBox)
{
}
TIARunScene::~TIARunScene()
{
    if(deltas != NULL)
    {
        for(auto d: *deltas)
        {
            for(auto e: d.GetEdgeChanges())
                delete e;
            for(auto v: d.GetNodeChanges())
                delete v;
        }
        delete deltas;
    }
    if(original != NULL)
        delete original;
    if(residual != NULL)
        delete residual;
    if(layered != NULL)
        delete layered;
}
void TIARunScene::mousePressedOnVertex(Vertex* v)
{
    Q_UNUSED(v)
}
void TIARunScene::Initialize(const std::vector<std::vector<unsigned long long> >& graphData)
{
    if(deltas != NULL)
    {
        for(auto d: *deltas)
        {
            for(auto e: d.GetEdgeChanges())
                delete e;
            for(auto v: d.GetNodeChanges())
                delete v;
        }
        delete deltas;
    }
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
    messageBox->setText(QString());
    original->GetNode(0)->SetColor(QColor(217, 234, 211));
    original->GetNode(original->GetSize()- 1)->SetColor(QColor(244, 204, 204));
    layered->GetNode(0)->SetColor(QColor(217, 234, 211));
    layered->GetNode(layered->GetSize() - 1)->SetColor(QColor(244, 204, 204));
    residual->GetNode(0)->SetColor(QColor(217, 234, 211));
    residual->GetNode(residual->GetSize() - 1)->SetColor(QColor(244, 204, 204));
    original->SetEdgeDisplayType(1);
    layered->SetNodeDisplayType(1);
    currentStep = 0;
}
void TIARunScene::NextStep()
{
    for(auto e: highlightedEdges)
        e->SetHighlighted(false);
    highlightedEdges.clear();
    for(auto v: highlightedNodes)
        v->SetHighlighted(false);
    highlightedNodes.clear();
    if(currentStep == deltas->size())
        return;
    auto delta = deltas->at(currentStep++);
    messageBox->setText(QString::fromStdString(delta.GetMessage()));
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
            {
                residual->DisplayGraph();
                layered->HideGraph();
            }
            else
                layered->DisplayGraph();
            graph = layered;
            currentGraph = LAYERED;
            break;
        default:
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
    {
        messageBox->setText(QString());
        graphToSwitch = ORIGINAL;
    }
    else
    {
        graphToSwitch = (TIADeltas)deltas->at(currentStep - 1).GetGraphId();
        messageBox->setText(QString::fromStdString(deltas->at(currentStep - 1).GetMessage()));
        if(deltas->at(currentStep - 1).IsToDelete())
            graphToSwitch = RESIDUAL;
    }
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
    for(long long i = delta.GetNodeChanges().size() - 1; i >= 0 ; --i)
        ProcessBackwardNodeChange(graph, delta.GetNodeChanges().at(i));
    for(long long i = delta.GetEdgeChanges().size() - 1; i >= 0 ; --i)
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
        highlightedEdges.push_back(graph->GetEdge(change->Id));
        graph->GetEdge(change->Id)->SetHighlighted(true);
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
    change->OldHighlighted = graph->GetEdge(change->Id)->GetHighlighted();
    if(graph->GetEdge(change->Id)->GetCapacity() != change->Capacity ||
            graph->GetEdge(change->Id)->GetFlow() != change->Flow)
    {
        highlightedEdges.push_back(graph->GetEdge(change->Id));
        graph->GetEdge(change->Id)->SetHighlighted(true);
    }
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
    change->OldHighlighted = graph->GetNode(change->Id)->GetHighlighted();
    if(change->Highlighted)
    {
        highlightedNodes.push_back(graph->GetNode(change->Id));
        graph->GetNode(change->Id)->SetHighlighted(true);
    }
    else
        graph->GetNode(change->Id)->SetHighlighted(false);
}
void TIARunScene::ProcessBackwardEdgeChange(VisualGraph* graph, NetworkEdgeChange* change)
{
    assert(change != NULL);
    assert(graph->GetEdge(change->Id) != NULL);
    if(change->OldPresent == false)
        graph->HideEdge(change->Id);
    else
        graph->DisplayEdge(change->Id);
    /*if(graph->GetEdge(change->Id)->GetCapacity() != change->OldCapacity ||
            graph->GetEdge(change->Id)->GetFlow() != change->OldFlow)
    {
        highlightedEdges.push_back(graph->GetEdge(change->Id));
        graph->GetEdge(change->Id)->SetHighlighted(true);
    }*/
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
    /*if(change->OldHighlighted)
        graph->GetNode(change->Id)->SetHighlighted(true);
    else
        graph->GetNode(change->Id)->SetHighlighted(false);*/
}
void TIARunScene::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key::Key_Forward)
        this->NextStep();
    if(event->key() == Qt::Key::Key_Back)
        this->PrevStep();
}


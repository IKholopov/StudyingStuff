#include "GraphParser.h"

#include "TIARunScene.h"
#include <qevent.h>

TIARunScene::TIARunScene(QTextEdit* messageBox, LayeredResidualSwitcher* switcher, AlgorithmRunView* parent):GraphScene(parent),
    view_(parent),original_(NULL), deltas_(NULL), layered_(NULL), residual_(NULL), currentStep_(0),
    messageBox_(messageBox), switcher_(switcher)
{
    switcher->disable();
    switcher->setScene(this);
}
TIARunScene::~TIARunScene()
{
    if(deltas_ != NULL) {
        for(auto d: *deltas_) {
            for(auto e: d.GetEdgeChanges())
                delete e;
            for(auto v: d.GetNodeChanges())
                delete v;
        }
        delete deltas_;
    }
    if(original_ != NULL)
        delete original_;
    if(residual_ != NULL)
        delete residual_;
    if(layered_ != NULL)
        delete layered_;
}
void TIARunScene::mousePressedOnVertex(Vertex* v)
{
    Q_UNUSED(v)
}
void TIARunScene::initialize(const std::vector<std::vector<unsigned long long> >& graphData)
{
    if(deltas_ != NULL) {
        for(auto d: *deltas_) {
            for(auto e: d.GetEdgeChanges())
                delete e;
            for(auto v: d.GetNodeChanges())
                delete v;
        }
        delete deltas_;
    }
    deltas_ = GraphParser::parser().getAlgorithmRun(graphData);
    if(original_ != NULL)
        delete original_;
    original_ = new VisualGraph(this, view_, graphData);
    if(residual_ != NULL)
        delete residual_;
    residual_ = new VisualGraph(this, view_, graphData);
    if(layered_ != NULL)
        delete layered_;
    layered_ = new VisualGraph(this, view_, graphData);
    residual_->hideGraph();
    layered_->disableGraph();
    switcher_->checkLayeredOption(POTENTIAL);
    switcher_->disable();
    currentGraph_ = ORIGINAL;
    messageBox_->setText(QString());
    original_->getNode(0)->setColor(QColor(217, 234, 211));
    original_->getNode(original_->getSize()- 1)->setColor(QColor(244, 204, 204));
    layered_->getNode(0)->setColor(QColor(217, 234, 211));
    layered_->getNode(layered_->getSize() - 1)->setColor(QColor(244, 204, 204));
    residual_->getNode(0)->setColor(QColor(217, 234, 211));
    residual_->getNode(residual_->getSize() - 1)->setColor(QColor(244, 204, 204));
    original_->setEdgeDisplayType(1);
    layered_->setNodeDisplayType(POTENTIAL);
    currentStep_ = 0;
}
void TIARunScene::nextStep()
{
    for(auto e: highlightedEdges_)
        e->setHighlighted(false);
    highlightedEdges_.clear();
    for(auto v: highlightedNodes_)
        v->setHighlighted(false);
    highlightedNodes_.clear();
    if(currentStep_ == deltas_->size())
        return;
    auto delta = deltas_->at(currentStep_++);
    messageBox_->setText(QString::fromStdString(delta.GetMessage()));
    VisualGraph* graph;
    switch(delta.GetGraphId()) {
        case ORIGINAL:
            switcher_->disable();
            layered_->hideGraph();
            residual_->hideGraph();
            original_->displayGraph();
            graph = original_;
            currentGraph_ = ORIGINAL;
            break;
         case RESIDUAL:
            switcher_->enable(RESIDUAL);
            layered_->hideGraph();
            original_->hideGraph();
            residual_->displayGraph();
            graph = residual_;
            currentGraph_ = RESIDUAL;
            break;
         case LAYERED:
            switcher_->enable(LAYERED);
            original_->hideGraph();
            residual_->hideGraph();
            if(delta.IsToDelete()) {
                residual_->displayGraph();
                layered_->hideGraph();
            }
            else
                layered_->displayGraph();
            graph = layered_;
            currentGraph_ = LAYERED;
            break;
        default:
            break;
    }
    for(unsigned long long i = 0; i < delta.GetNodeChanges().size(); ++i)
        processNodeChange(graph, delta.GetNodeChanges().at(i));
    for(unsigned long long i = 0; i < delta.GetEdgeChanges().size(); ++i)
        processEdgeChange(graph, delta.GetEdgeChanges().at(i));
}
void TIARunScene::prevStep()
{
    if(currentStep_ == 0)
        return;
    auto delta = deltas_->at(--currentStep_);
    VisualGraph* graph;
    TIADeltas graphToSwitch;
    if(currentStep_ == 0) {
        messageBox_->setText(QString());
        graphToSwitch = ORIGINAL;
    }
    else {
        graphToSwitch = (TIADeltas)deltas_->at(currentStep_ - 1).GetGraphId();
        messageBox_->setText(QString::fromStdString(deltas_->at(currentStep_ - 1).GetMessage()));
        if(deltas_->at(currentStep_ - 1).IsToDelete())
            graphToSwitch = RESIDUAL;
    }
    switch(delta.GetGraphId()) {
        case ORIGINAL:
            graph = original_;
            break;
         case RESIDUAL:
            graph = residual_;
            break;
         case LAYERED:
            graph = layered_;
            break;
        default:
            break;
    }
    for(long long i = delta.GetNodeChanges().size() - 1; i >= 0 ; --i)
        processBackwardNodeChange(graph, delta.GetNodeChanges().at(i));
    for(long long i = delta.GetEdgeChanges().size() - 1; i >= 0 ; --i)
        processBackwardEdgeChange(graph, delta.GetEdgeChanges().at(i));
    switch(graphToSwitch) {
        case ORIGINAL:
            switcher_->disable();
            layered_->hideGraph();
            residual_->hideGraph();
            original_->displayGraph();
            break;
         case RESIDUAL:
            switcher_->enable(RESIDUAL);
            layered_->hideGraph();
            original_->hideGraph();
            residual_->displayGraph();
            break;
         case LAYERED:
            switcher_->enable(LAYERED);
            original_->hideGraph();
            residual_->hideGraph();
            layered_->displayGraph();
            break;
        default:
            break;
    }
}
std::vector<VisualGraph*> TIARunScene::getGraphs()
{
    std::vector<VisualGraph*> graphs;
    if(original_->isActive())
        graphs.push_back(original_);
    if(residual_->isActive())
        graphs.push_back(residual_);
    if(layered_->isActive())
        graphs.push_back(layered_);
    return graphs;
}
void TIARunScene::processEdgeChange(VisualGraph* graph, NetworkEdgeChange* change)
{
    assert(change != NULL);
    if(graph->getEdge(change->Id) == NULL) {
        graph->addEdge(change->From, change->To, change->Capacity);
        highlightedEdges_.push_back(graph->getEdge(change->Id));
        graph->getEdge(change->Id)->setHighlighted(true);
        if(graph != layered_) {
            layered_->addEdge(change->From, change->To, change->Capacity);
            layered_->hideEdge(change->Id);
        }
        change->OldPresent = false;
    }
    else
        change->OldPresent = graph->getEdge(change->Id)->getActive();
    if(change->Present == false)
        graph->hideEdge(change->Id);
    else
        graph->displayEdge(change->Id);
    change->OldCapacity = graph->getEdge(change->Id)->getCapacity();
    change->OldFlow = graph->getEdge(change->Id)->getFlow();
    change->OldHighlighted = graph->getEdge(change->Id)->getHighlighted();
    if(graph->getEdge(change->Id)->getCapacity() != change->Capacity ||
            graph->getEdge(change->Id)->getFlow() != change->Flow) {
        highlightedEdges_.push_back(graph->getEdge(change->Id));
        graph->getEdge(change->Id)->setHighlighted(true);
    }
    graph->getEdge(change->Id)->setCapacity(change->Capacity);
    graph->getEdge(change->Id)->setFlow(change->Flow);
}
void TIARunScene::processNodeChange(VisualGraph* graph, NetworkNodeChange* change)
{
    assert(graph->getNode(change->Id) != NULL);
    assert(change != NULL);
    if(graph->getNode(change->Id) == NULL)
        return;
    change->OldPresent = graph->getNode(change->Id)->getActive();
    if(change->Present == 0)
        graph->hideNode(change->Id);
    else
        graph->displayNode(change->Id);
    change->OldPotential = graph->getNode(change->Id)->getPotential();
    graph->getNode(change->Id)->setPotential(change->Potential);
    change->OldHighlighted = graph->getNode(change->Id)->getHighlighted();
    if(change->Highlighted) {
        highlightedNodes_.push_back(graph->getNode(change->Id));
        graph->getNode(change->Id)->setHighlighted(true);
    }
    else
        graph->getNode(change->Id)->setHighlighted(false);
}
void TIARunScene::processBackwardEdgeChange(VisualGraph* graph, NetworkEdgeChange* change)
{
    assert(change != NULL);
    assert(graph->getEdge(change->Id) != NULL);
    if(change->OldPresent == false)
        graph->hideEdge(change->Id);
    else
        graph->displayEdge(change->Id);
    graph->getEdge(change->Id)->setCapacity(change->OldCapacity);
    graph->getEdge(change->Id)->setFlow(change->OldFlow);
}
void TIARunScene::processBackwardNodeChange(VisualGraph* graph, NetworkNodeChange* change)
{
    assert(change != NULL);
    assert(graph->getNode(change->Id) != NULL);
    if(graph->getNode(change->Id) == NULL)
        return;
    if(change->OldPresent == 0)
        graph->hideNode(change->Id);
    else
        graph->displayNode(change->Id);
    graph->getNode(change->Id)->setPotential(change->OldPotential);
}
void TIARunScene::showLayeredPotential()
{
    this->layered_->setNodeDisplayType(POTENTIAL);
}
void TIARunScene::showLayeredId()
{
    this->layered_->setNodeDisplayType(ID);
}
void TIARunScene::showResidual()
{
    original_->hideGraph();
    residual_->displayGraph();
    layered_->hideGraph();
}
void TIARunScene::showLayered()
{
    original_->hideGraph();
    residual_->hideGraph();
    layered_->displayGraph();
}
void TIARunScene::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key::Key_Forward)
        this->nextStep();
    if(event->key() == Qt::Key::Key_Back)
        this->prevStep();
}

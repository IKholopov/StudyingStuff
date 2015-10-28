#include "GraphEditScene.h"

#include <type_traits>
#include <assert.h>

GraphEditScene::GraphEditScene(EditGraphToolBar toolbar, GraphEditArea* parent):GraphScene((QObject*)parent)
{

    this->graph_ = new VisualGraph(this, (GraphArea*)parent);
    this->toolbar_ = toolbar;
    toolbar.setTool(EditGraphTools::None);
    view_ = parent;
}
GraphEditScene::~GraphEditScene()
{
    delete graph_;
}

void GraphEditScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    switch(toolbar_.getActiveTool()) {
        case EditGraphTools::AddNode:
            this->addNode(event->scenePos());
            break;
        default:
            this->QGraphicsScene::mousePressEvent(event);
            break;
    }
}

void GraphEditScene::addNode(QPointF position)
{
    graph_->addNode(position);
}
void GraphEditScene::addEdge(unsigned long long from, unsigned long long to, unsigned long long capacity)
{
    graph_->addEdge(from, to, capacity);
}
void GraphEditScene::loadGraph(std::string filename)
{
    graph_->removeGraph();
    delete graph_;
    graph_ = new VisualGraph(this, view_, filename);
}
void GraphEditScene::newGraph()
{
    graph_->removeGraph();
    delete graph_;
    graph_ = new VisualGraph(this, view_);
}
EditGraphTools GraphEditScene::getActiveTool()
{
    return toolbar_.getActiveTool();
}
VisualGraph* GraphEditScene::getGraph() const
{
    return graph_;
}

void GraphEditScene::mousePressedOnVertex(Vertex* v)
{
    if(this->getActiveTool() == EditGraphTools::AddEdge)
        this->view_->processAddEdge(this, v);
}
void GraphEditScene::setActiveTool(EditGraphTools tool)
{
    this->toolbar_.setTool(toolbar_.getActiveTool() != tool ? tool : EditGraphTools::None);
}



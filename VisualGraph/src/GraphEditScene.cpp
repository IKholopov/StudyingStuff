#include "GraphEditScene.h"

#include <type_traits>
#include <assert.h>

GraphEditScene::GraphEditScene(EditGraphToolBar toolbar, GraphEditArea* parent):GraphScene((QObject*)parent)
{

    this->graph = new VisualGraph(this, (GraphArea*)parent);
    this->toolbar = toolbar;
    toolbar.SetTool(EditGraphTools::None);
    view = parent;
}
GraphEditScene::~GraphEditScene()
{
    delete graph;
}

void GraphEditScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    switch(toolbar.GetActiveTool())
    {
        case EditGraphTools::AddNode:
            this->AddNode(event->scenePos());
            break;
        default:
            this->QGraphicsScene::mousePressEvent(event);
            break;
    }
}

void GraphEditScene::AddNode(QPointF position)
{
    graph->AddNode(position);
}
void GraphEditScene::AddEdge(unsigned long long from, unsigned long long to, unsigned long long capacity)
{
    graph->AddEdge(from, to, capacity);
}
void GraphEditScene::LoadGraph(std::string filename)
{
    graph->RemoveGraph();
    delete graph;
    graph = new VisualGraph(this, view, filename);
}
void GraphEditScene::NewGraph()
{
    graph->RemoveGraph();
    delete graph;
    graph = new VisualGraph(this, view);
}
EditGraphTools GraphEditScene::GetActiveTool()
{
    return toolbar.GetActiveTool();
}
VisualGraph* GraphEditScene::GetGraph() const
{
    return graph;
}

void GraphEditScene::mousePressedOnVertex(Vertex* v)
{
    if(this->GetActiveTool() == EditGraphTools::AddEdge)
        this->view->ProcessAddEdge(this, v);
}
void GraphEditScene::SetActiveTool(EditGraphTools tool)
{
    this->toolbar.SetTool(toolbar.GetActiveTool() != tool ? tool : EditGraphTools::None);
}



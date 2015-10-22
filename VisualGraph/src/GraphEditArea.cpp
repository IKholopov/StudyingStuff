#include "GraphEditArea.h"

#include <QMouseEvent>
#include <QInputDialog>

#include "GraphEditScene.h"


GraphEditArea::GraphEditArea(QWidget* parent):GraphArea(parent),timerId(0)
{
    QGraphicsScene* graphScene = new GraphEditScene(EditGraphToolBar(),this);
    graphScene->setSceneRect(QRectF(0, 0, 1250, 500));
    this->setMinimumSize(1250, 500);
    setCacheMode(CacheBackground);
    this->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
    setScene(graphScene);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
}
GraphEditArea::~GraphEditArea()
{
    delete this->scene();
}

void GraphEditArea::drawBackground(QPainter* painter, const QRectF& rect)
{
    painter->fillRect(rect.intersected(this->sceneRect()), QColor(200, 200, 200));
}

void GraphEditArea::SetActiveTool(EditGraphTools tool)
{
    static_cast<GraphEditScene*>(this->scene())->SetActiveTool(tool);
}
void GraphEditArea::SetTimerId(int id)
{
    this->timerId = id;
}
int GraphEditArea::GetTimerId()
{
    return timerId;
}
void GraphEditArea::SaveGraph()
{
    static_cast<GraphEditScene*>(this->scene())->GetGraph()->Save();
}
void GraphEditArea::LoadGraph()
{
    killTimer(timerId);
    static_cast<GraphEditScene*>(this->scene())->LoadGraph("graph.gr");
    startTimer(timerId);
}
void GraphEditArea::NewGraph()
{
    killTimer(timerId);
    static_cast<GraphEditScene*>(this->scene())->NewGraph();
    startTimer(timerId);
}

std::vector<std::vector<unsigned long long>> GraphEditArea::CloneGraph()
{
    return static_cast<GraphEditScene*>(this->scene())->GetGraph()->Clone();
}
void GraphEditArea::InitializeAddEdge()
{
    this->addEdgeTool.Initialize();
}
void GraphEditArea::ProcessAddEdge(GraphEditScene* scene, Vertex* v)
{
    this->addEdgeTool.Process(scene, v);
}

void GraphEditArea::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);
    VisualGraph* graph = static_cast<GraphEditScene*>(this->scene())->GetGraph();
    graph->Update();
    if(!graph->IsMoved())
    {
        killTimer(timerId);
        timerId = 0;
    }
}


Vertex* AddEdgeTool::GetFrom() const
{
    return from;
}
void AddEdgeTool::SetFrom(Vertex* value)
{
    from = value;
}
Vertex* AddEdgeTool::GetTo() const
{
    return to;
}
void AddEdgeTool::SetTo(Vertex* value)
{
    to = value;
}

void AddEdgeTool::Initialize()
{
    from = NULL;
    to = NULL;
}
void AddEdgeTool::Process(GraphEditScene* scene, Vertex* v)
{
    if(from == NULL)
    {
        from = v;
        return;
    }
    to = v;
    unsigned long long capacity = QInputDialog::getInt(NULL, "Capacity", "Capacity");
    scene->AddEdge(from->GetId(), to->GetId(), capacity);
    from = NULL;
    to = NULL;
}

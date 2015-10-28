#include "GraphEditArea.h"

#include <QMouseEvent>
#include <QInputDialog>
#include <QFileDialog>

#include "GraphEditScene.h"


GraphEditArea::GraphEditArea(QWidget* parent):GraphArea(parent),timerId_(0)
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

void GraphEditArea::setActiveTool(EditGraphTools tool)
{
    static_cast<GraphEditScene*>(this->scene())->setActiveTool(tool);
}
void GraphEditArea::setTimerId(int id)
{
    this->timerId_ = id;
}
int GraphEditArea::getTimerId()
{
    return timerId_;
}
void GraphEditArea::saveGraph()
{
    static_cast<GraphEditScene*>(this->scene())->getGraph()->save();
}
void GraphEditArea::loadGraph()
{
    killTimer(timerId_);
    QString filename = QFileDialog::getOpenFileName(this, "Open Graph", "~/", "All Files (*);;Graph Files (*.gr)");
    if(filename.isEmpty())
        return;
    static_cast<GraphEditScene*>(this->scene())->loadGraph(filename.toStdString());
    startTimer(timerId_);
}
void GraphEditArea::newGraph()
{
    killTimer(timerId_);
    static_cast<GraphEditScene*>(this->scene())->newGraph();
    startTimer(timerId_);
}

std::vector<std::vector<unsigned long long>> GraphEditArea::cloneGraph()
{
    return static_cast<GraphEditScene*>(this->scene())->getGraph()->clone();
}
void GraphEditArea::initializeAddEdge()
{
    this->addEdgeTool_.initialize();
}
void GraphEditArea::processAddEdge(GraphEditScene* scene, Vertex* v)
{
    this->addEdgeTool_.process(scene, v);
}

void GraphEditArea::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);
    VisualGraph* graph = static_cast<GraphEditScene*>(this->scene())->getGraph();
    graph->update();
    if(!graph->isMoved()) {
        killTimer(timerId_);
        timerId_ = 0;
    }
}

Vertex* AddEdgeTool::getFrom() const
{
    return from;
}
void AddEdgeTool::setFrom(Vertex* value)
{
    from = value;
}
Vertex* AddEdgeTool::getTo() const
{
    return to;
}
void AddEdgeTool::setTo(Vertex* value)
{
    to = value;
}

void AddEdgeTool::initialize()
{
    from = NULL;
    to = NULL;
}
void AddEdgeTool::process(GraphEditScene* scene, Vertex* v)
{
    if(from == NULL) {
        from = v;
        return;
    }
    to = v;
    unsigned long long capacity = QInputDialog::getInt(NULL, "Capacity", "Capacity");
    scene->addEdge(from->getId(), to->getId(), capacity);
    from = NULL;
    to = NULL;
}

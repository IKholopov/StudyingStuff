#include "AlgorithmRunView.h"
#include "TIARunScene.h"

AlgorithmRunView::AlgorithmRunView(QWidget* parent):GraphArea(parent), timerId(0)
{
    QGraphicsScene* graphScene = new TIARunScene(this);
    graphScene->setSceneRect(QRectF(0, 0, 1250, 500));
    this->setMinimumSize(1250, 500);
    setCacheMode(CacheBackground);
    this->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
    setScene(graphScene);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
}

void AlgorithmRunView::drawBackground(QPainter* painter, const QRectF& rect)
{
    painter->fillRect(rect.intersected(this->sceneRect()), QColor(200, 200, 200));
}
void AlgorithmRunView::SetTimerId(int id)
{
    this->timerId = id;
}
int AlgorithmRunView::GetTimerId()
{
    return timerId;
}
void AlgorithmRunView::Initialize(const std::vector<std::vector<unsigned long long> >& graphData)
{
    static_cast<TIARunScene*>(this->scene())->Initialize(graphData);
}
void AlgorithmRunView::NextStep()
{
    static_cast<TIARunScene*>(this->scene())->NextStep();
}
void AlgorithmRunView::PrevStep()
{
    static_cast<TIARunScene*>(this->scene())->PrevStep();
}
void AlgorithmRunView::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);
    auto graphs = static_cast<TIARunScene*>(this->scene())->GetGraphs();
    for(auto graph: graphs)
    {
        graph->Update();
        if(!graph->IsMoved() && !graph->IsActive())
        {
            killTimer(timerId);
            timerId = 0;
        }
    }
}


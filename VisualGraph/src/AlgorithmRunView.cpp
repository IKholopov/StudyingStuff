#include "AlgorithmRunView.h"

#include "TIARunScene.h"
#include <qtextedit.h>

AlgorithmRunView::AlgorithmRunView(QTextEdit* messageBox, LayeredResidualSwitcher* switcher, QWidget* parent):GraphArea(parent), timerId_(0), messageBox_(messageBox)
{
    QGraphicsScene* graphScene = new TIARunScene(messageBox, switcher, this);
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
void AlgorithmRunView::setTimerId(int id)
{
    this->timerId_ = id;
}
int AlgorithmRunView::getTimerId()
{
    return timerId_;
}
void AlgorithmRunView::initialize(const std::vector<std::vector<unsigned long long> >& graphData)
{
    static_cast<TIARunScene*>(this->scene())->initialize(graphData);
}
void AlgorithmRunView::nextStep()
{
    static_cast<TIARunScene*>(this->scene())->nextStep();
}
void AlgorithmRunView::prevStep()
{
    static_cast<TIARunScene*>(this->scene())->prevStep();
}
void AlgorithmRunView::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);
    auto graphs = static_cast<TIARunScene*>(this->scene())->getGraphs();
    for(auto graph: graphs) {
        graph->update();
        if(!graph->isMoved() && !graph->isActive()) {
            killTimer(timerId_);
            timerId_ = 0;
        }
    }
}


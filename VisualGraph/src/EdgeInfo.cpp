#include "EdgeInfo.h"

EdgeInfo::EdgeInfo(VisualEdge* edge):edge(edge)
{
    setZValue(0);
}

void EdgeInfo::Update()
{
    prepareGeometryChange();
}

QRectF EdgeInfo::boundingRect() const
{
//    if(edge->IsHovered())
//5        return QRectF(0, 0, 100, 100);
    return QRectF(qMin(edge->GetFrom()->scenePos().x(), edge->GetTo()->scenePos().x()) + edge->boundingRect().width() / 2,
                  qMin(edge->GetFrom()->scenePos().y(), edge->GetTo()->scenePos().y()) + edge->boundingRect().height() / 2,
                  20, 20);
}

void EdgeInfo::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QFont font("Times", 10);
    font.setStyleStrategy(QFont::ForceOutline);
    painter->setFont(font);
    painter->save();
    double scale = 1.0;
    painter->scale(scale, scale);
    painter->drawText(qMin(edge->GetFrom()->scenePos().x(), edge->GetTo()->scenePos().x()) + edge->boundingRect().width() / 2,
                      qMin(edge->GetFrom()->scenePos().y(), edge->GetTo()->scenePos().y()) + edge->boundingRect().height() / 2,
                      QString("%1").arg(this->edge->GetCapacity()));
    painter->restore();
}


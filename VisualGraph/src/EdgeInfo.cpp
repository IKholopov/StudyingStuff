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
    return QRectF(qMin(edge->GetFrom()->scenePos().x(), edge->GetTo()->scenePos().x()) + edge->boundingRect().width() / 2,
                  qMin(edge->GetFrom()->scenePos().y(), edge->GetTo()->scenePos().y()) + edge->boundingRect().height() / 2,
                  40, 40);
}

void EdgeInfo::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    const double pi = 3.14159265359;

    QFont font("Times", 10);
    font.setStyleStrategy(QFont::ForceOutline);
    painter->setFont(font);
    painter->save();
    double scale = 1.0;
    painter->scale(scale, scale);
    auto line = QLineF(mapFromItem(edge->GetFrom(), 0 , 0), mapFromItem(edge->GetTo(), 0, 0));
    double angle = acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = 2 * pi - angle;
    QString str;
    switch (edge->GetDisplayType()) {
        case 0:
            str = QString("%1").arg(this->edge->GetCapacity());
            break;
        case 1 :
            str = QString("[%1/%2]").arg(this->edge->GetFlow()).arg(edge->GetCapacity());
            break;
        default:
            break;
    }
    painter->drawText(qMin(edge->GetFrom()->scenePos().x(), edge->GetTo()->scenePos().x()) + edge->boundingRect().width() / 2 +
                       sin(angle- pi) * 7,
                      qMin(edge->GetFrom()->scenePos().y(), edge->GetTo()->scenePos().y()) + edge->boundingRect().height() / 2 +
                      cos(angle + pi) * 7,
                      str);
    painter->restore();
}


#include "EdgeInfo.h"

EdgeInfo::EdgeInfo(VisualEdge* edge):edge_(edge)
{
    setZValue(0);
}

void EdgeInfo::update()
{
    prepareGeometryChange();
}

QRectF EdgeInfo::boundingRect() const
{
    return QRectF(qMin(edge_->getFrom()->scenePos().x(), edge_->getTo()->scenePos().x()) + edge_->boundingRect().width() / 2,
                  qMin(edge_->getFrom()->scenePos().y(), edge_->getTo()->scenePos().y()) + edge_->boundingRect().height() / 2,
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
    auto line = QLineF(mapFromItem(edge_->getFrom(), 0 , 0), mapFromItem(edge_->getTo(), 0, 0));
    double angle = acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = 2 * pi - angle;
    QString str;
    switch (edge_->getDisplayType()) {
        case 0:
            str = QString("%1").arg(this->edge_->getCapacity());
            break;
        case 1 :
            str = QString("[%1/%2]").arg(this->edge_->getFlow()).arg(edge_->getCapacity());
            break;
        default:
            break;
    }
    painter->drawText(qMin(edge_->getFrom()->scenePos().x(), edge_->getTo()->scenePos().x()) + edge_->boundingRect().width() / 2 +
                       sin(angle- pi) * 7,
                      qMin(edge_->getFrom()->scenePos().y(), edge_->getTo()->scenePos().y()) + edge_->boundingRect().height() / 2 +
                      cos(angle + pi) * 7,
                      str);
    painter->restore();
}


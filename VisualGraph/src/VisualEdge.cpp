#include "VisualEdge.h"

VisualEdge::VisualEdge(QGraphicsScene* scene, unsigned long long id, Vertex* from, Vertex* to, unsigned long long capacity,
                       int displayType):id_(id), from_(from), to_(to),
    capacity_(capacity), displayType_(displayType)
{
    scene->addItem(this);
    info_ = new EdgeInfo(this);
    scene->addItem(info_);
    setFlag(ItemSendsGeometryChanges);
    setAcceptHoverEvents(1);
    setZValue(0);
}
VisualEdge::~VisualEdge()
{
    delete info_;
}

unsigned long long VisualEdge::getId() const
{
    return id_;
}
Vertex* VisualEdge::getTo() const
{
    return to_;
}
Vertex* VisualEdge::getFrom() const
{
    return from_;
}
EdgeInfo* VisualEdge::getInfo() const
{
    return info_;
}
unsigned long long VisualEdge::getCapacity() const
{
    return capacity_;
}
void VisualEdge::setCapacity(unsigned long long value)
{
    capacity_ = value;
}
int VisualEdge::getDisplayType()
{
    return displayType_;
}
void VisualEdge::setDisplayType(int displayType)
{
    this->displayType_ = displayType;
}
void VisualEdge::hideEdge()
{
    this->hide();
    this->setActive(false);
    info_->hide();
    prepareGeometryChange();
}
void VisualEdge::showEdge()
{
    this->show();
    this->setActive(true);
    info_->show();
    prepareGeometryChange();
}
void VisualEdge::update()
{
    info_->update();
    prepareGeometryChange();
}
bool VisualEdge::isHovered()
{
    return isHovered_;
}

QRectF VisualEdge::boundingRect() const
{
    qreal adjust = 1;
    return QRectF(from_->scenePos(), QSizeF(to_->scenePos().x() - from_->scenePos().x(),
                                           to_->scenePos().y() - from_->scenePos().y())).normalized().adjusted(-adjust, -adjust,adjust,adjust);
}
void VisualEdge::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    const double pi = 3.14159265359;

    Qt::PenStyle style = this->capacity_ == 0 ? Qt::DotLine : Qt::SolidLine;
    if(!highlighted_)
        painter->setPen(QPen(color_, 1, style, Qt::RoundCap, Qt::RoundJoin));
    else
        painter->setPen(QPen(QColor(239, 108, 0), 1, style, Qt::RoundCap, Qt::RoundJoin));
    auto lineFrom = mapFromItem(from_, 0, 0);
    auto lineTo = mapFromItem(to_, 0, 0);
    auto line = QLineF(lineFrom, lineTo);
    auto point2 = line.p2() - QPointF((line.dx() * 10) / line.length(), (line.dy() * 10) / line.length());
    double angle = acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = 2 * pi - angle;
    line.setP2(point2 + QPointF(sin(angle- pi) * 7,
                                cos(angle + pi) * 7));
    painter->drawLine(line);
    QPointF arrow1Source = line.p2();
    QPointF arrow1Dest = line.p2() + QPointF(sin(angle - pi / 1.5) * 7,
                         cos(angle - pi / 1.5) * 7) + QPointF(-sin(pi / 2 - angle) * 3, cos(pi /2 - angle) * 3);
    QPointF arrow2Source = line.p2();
    QPointF arrow2Dest = line.p2() + QPointF(sin(angle + pi / 1.5 - pi) * 7,
                         cos(angle + pi / 1.5 + pi) * 7) + QPointF(-sin(pi / 2 - angle) * 3, cos(pi /2 - angle) * 3);
    auto arrow1 = QLineF(arrow1Dest, arrow1Source);
    auto arrow2 = QLineF(arrow2Dest, arrow2Source);
    painter->drawLine(arrow1);
    painter->drawLine(arrow2);
}
void VisualEdge::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event);
    isHovered_ = true;
    this->color_ = Qt::red;
    prepareGeometryChange();
}
void VisualEdge::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event);
    isHovered_ = false;
    this->color_ = Qt::black;
    prepareGeometryChange();
}
bool VisualEdge::getHighlighted() const
{
    return highlighted_;
}
void VisualEdge::setHighlighted(bool value)
{
    highlighted_ = value;
}
bool VisualEdge::getActive() const
{
    return active_;
}
void VisualEdge::setActive(bool value)
{
    active_ = value;
}
unsigned long long VisualEdge::getFlow() const
{
    return flow_;
}
void VisualEdge::setFlow(unsigned long long value)
{
    flow_ = value;
}

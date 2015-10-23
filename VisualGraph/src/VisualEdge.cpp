#include "VisualEdge.h"

VisualEdge::VisualEdge(QGraphicsScene* scene, unsigned long long id, Vertex* from, Vertex* to, unsigned long long capacity,
                       int displayType):id(id), from(from), to(to),
    capacity(capacity), displayType(displayType)
{
    scene->addItem(this);
    info = new EdgeInfo(this);
    scene->addItem(info);
    setFlag(ItemSendsGeometryChanges);
    setAcceptHoverEvents(1);
    setZValue(0);
}
VisualEdge::~VisualEdge()
{
    delete info;
}

unsigned long long VisualEdge::GetId() const
{
    return id;
}
Vertex* VisualEdge::GetTo() const
{
    return to;
}
Vertex* VisualEdge::GetFrom() const
{
    return from;
}
EdgeInfo* VisualEdge::GetInfo() const
{
    return info;
}
unsigned long long VisualEdge::GetCapacity() const
{
    return capacity;
}
void VisualEdge::SetCapacity(unsigned long long value)
{
    capacity = value;
}
int VisualEdge::GetDisplayType()
{
    return displayType;
}
void VisualEdge::SetDisplayType(int displayType)
{
    this->displayType = displayType;
}
void VisualEdge::HideEdge()
{
    this->hide();
    this->SetActive(false);
    info->hide();
    prepareGeometryChange();
}
void VisualEdge::ShowEdge()
{
    this->show();
    this->SetActive(true);
    info->show();
    prepareGeometryChange();
}
void VisualEdge::Update()
{
    info->Update();
    prepareGeometryChange();
}
bool VisualEdge::IsHovered()
{
    return isHovered;
}

QRectF VisualEdge::boundingRect() const
{
    qreal adjust = 1;
    return QRectF(from->scenePos(), QSizeF(to->scenePos().x() - from->scenePos().x(),
                                           to->scenePos().y() - from->scenePos().y())).normalized().adjusted(-adjust, -adjust,adjust,adjust);
}
void VisualEdge::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    const double pi = 3.14159265359;

    painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    auto lineFrom = mapFromItem(from, 0, 0);
    auto lineTo = mapFromItem(to, 0, 0);
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
    isHovered = true;
    this->color = Qt::red;
    prepareGeometryChange();
}
void VisualEdge::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event);
    isHovered = false;
    this->color = Qt::black;
    prepareGeometryChange();
}
bool VisualEdge::GetActive() const
{
    return active;
}
void VisualEdge::SetActive(bool value)
{
    active = value;
}
unsigned long long VisualEdge::GetFlow() const
{
    return flow;
}
void VisualEdge::SetFlow(unsigned long long value)
{
    flow = value;
}

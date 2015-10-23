#include "Vertex.h"

#include <assert.h>
#include <QPainter>
#include <QGraphicsScene>

Vertex::Vertex(unsigned long long id, VisualGraph* graph, QPointF position):id(id), graph(graph), color(QColor(152, 255, 255))
{
    setFlag(ItemIsMovable);
        setFlag(ItemSendsGeometryChanges);
        setAcceptHoverEvents(1);
    nextPosition = position;
    setZValue(1);
}

void Vertex::AddEdge(VisualEdge* edge)
{
    edges.push_back(edge);
}
void Vertex::RemoveEdge(unsigned long long edgeId)
{
    for(auto e = edges.begin(); e != edges.end(); ++e)
        if((*e)->GetId() == edgeId)
        {
            edges.erase(e);
            break;
        }
}

QRectF Vertex::boundingRect() const
{
    return QRectF(-15, -15, 30, 30);
}
QPainterPath Vertex::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}
void Vertex::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(QBrush(color));
    painter->drawEllipse(-10, -10, 20, 20);
    QString str;
    switch(this->GetDisplayType())
    {
        case 0:
            str = QString("%1").arg(this->id);
            break;
        case 1:
            str = QString("%1").arg(this->potential);
            break;
        default:
            break;
    }
    QFont font("Times", 15);
    font.setStyleStrategy(QFont::ForceOutline);
    painter->setFont(font);
    painter->save();
    double scale = 1.0;
    if(this->id / 100)
        scale *=0.7;
    if(this->id / 10)
        scale *=0.7;
    painter->scale(scale, scale);
    painter->drawText(-4, 8, str);
    painter->restore();
}
void Vertex::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    this->graph->Scene()->mousePressedOnVertex(this);
    this->update();
    this->QGraphicsItem::mousePressEvent(event);
}
void Vertex::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    this->update();
    this->QGraphicsItem::mouseReleaseEvent(event);
}

QVariant Vertex::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if(change == GraphicsItemChange::ItemPositionHasChanged)
    {
        for(auto e: edges)
            e->Update();
        graph->MovedGraph();
    }
    return QGraphicsItem::itemChange(change, value);
}
unsigned long long Vertex::GetId()
{
    return this->id;
}
void Vertex::HideNode()
{
    this->hide();
    this->SetActive(false);
    prepareGeometryChange();
}
void Vertex::ShowNode()
{
    this->show();
    this->SetActive(true);
    prepareGeometryChange();
}
void Vertex::Update()
{
    if(scene()->mouseGrabberItem() == this || this->edges.size() == 0)
    {
        nextPosition = pos();
        return;
    }
    const double c1 = 40;
    const double c2 = 20.0;
    const double c3 = 0.3;
    double vx = 0;
    double vy = 0;
    double mass = c2 * (this->edges.size() + 1);
    for(auto vert: *(this->graph->Verticies()))
    {
        assert(vert != NULL);
        if(vert->Neighbors() == 0)
            continue;
        QPointF r = mapToItem(vert, 0, 0);
        if(r.x() * r.x() + r.y() * r.y() > 0)
        {
            vx += r.x() * c1 / (r.x() * r.x() + r.y() * r.y());
            vy += r.y() * c1 / (r.x() * r.x() + r.y() * r.y());
        }
    }
    for(auto e: edges)
    {
        Vertex* vert = NULL;
        if(e->GetFrom() == this)
            vert = e->GetTo();
        else if(e->GetTo() == this)
            vert = e->GetFrom();
        assert(vert != NULL);
        QPointF r = mapToItem(vert, 0, 0);
        vx -= r.x()/mass;
        vy -= r.y()/mass;
    }
    vx -= c3 * velocity.x();
    vy -= c3 * velocity.y();
    if(qAbs(vx) < 0.1 && qAbs(vy) < 0.1)
        this->velocity = QPointF(0, 0);
    else
        this->velocity += QPointF(vx, vy);
}
void Vertex::UpdatePosition()
{
    int offsetLimit = 30;
    this->nextPosition += velocity;
    this->nextPosition.setX(qMin(qMax(this->nextPosition.x(), scene()->sceneRect().left() + offsetLimit), scene()->sceneRect().right() - offsetLimit));
    if(nextPosition.x() == scene()->sceneRect().left() + offsetLimit || nextPosition.x() == scene()->sceneRect().right() - offsetLimit )
        velocity.setX(-velocity.x());
    this->nextPosition.setY(qMin(qMax(this->nextPosition.y(), scene()->sceneRect().top() + offsetLimit), scene()->sceneRect().bottom() - offsetLimit));
    if(nextPosition.y() == scene()->sceneRect().top() + offsetLimit || nextPosition.y() == scene()->sceneRect().bottom() - offsetLimit )
        velocity.setY(-velocity.y());
}

bool Vertex::advance()
{
    if(this->pos() == nextPosition)
        return false;
    setPos(nextPosition);
    return true;
}
unsigned long long Vertex::Neighbors()
{
    return this->edges.size();
}
void Vertex::SetColor(QColor color)
{
    this->color = color;
}
unsigned long long Vertex::GetPotential() const
{
    return potential;
}
void Vertex::SetPotential(unsigned long long value)
{
    potential = value;
}
bool Vertex::GetActive() const
{
    return active;
}
void Vertex::SetActive(bool value)
{
    active = value;
}
int Vertex::GetDisplayType()
{
    return displayType;
}
void Vertex::SetDisplayType(int displayType)
{
    this->displayType = displayType;
}

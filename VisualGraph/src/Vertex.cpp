#include "Vertex.h"

#include <assert.h>
#include <QPainter>
#include <QGraphicsScene>

Vertex::Vertex(unsigned long long id, VisualGraph* graph, QPointF position):id_(id), graph_(graph), color_(QColor(152, 255, 255))
{
    setFlag(ItemIsMovable);
        setFlag(ItemSendsGeometryChanges);
        setAcceptHoverEvents(1);
    nextPosition_ = position;
    setZValue(1);
}

void Vertex::addEdge(VisualEdge* edge)
{
    edges_.push_back(edge);
}
void Vertex::removeEdge(unsigned long long edgeId)
{
    for(auto e = edges_.begin(); e != edges_.end(); ++e)
        if((*e)->getId() == edgeId)
        {
            edges_.erase(e);
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
    if(!highlighted_)
        painter->setBrush(QBrush(color_));
    else
        painter->setBrush(QBrush(QColor(239, 108, 0)));
    painter->drawEllipse(-10, -10, 20, 20);
    QString str;
    switch(this->getDisplayType())
    {
        case ID:
            str = QString("%1").arg(this->id_ + 1);
            break;
        case POTENTIAL:
            str = QString("%1").arg(this->potential_);
            break;
        default:
            break;
    }
    QFont font("Times", 15);
    font.setStyleStrategy(QFont::ForceOutline);
    painter->setFont(font);
    painter->save();
    double scale = 1.0;
    if((this->id_ + 1) / 100)
        scale *=0.7;
    if((this->id_ + 1) / 10)
        scale *=0.7;
    painter->scale(scale, scale);
    painter->drawText(-4, 8, str);
    painter->restore();
}
void Vertex::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    this->graph_->scene()->mousePressedOnVertex(this);
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
        for(auto e: edges_)
            e->update();
        graph_->movedGraph();
    }
    return QGraphicsItem::itemChange(change, value);
}
unsigned long long Vertex::getId()
{
    return this->id_;
}
void Vertex::hideNode()
{
    this->hide();
    this->setActive(false);
    prepareGeometryChange();
}
void Vertex::showNode()
{
    this->show();
    this->setActive(true);
    prepareGeometryChange();
}
void Vertex::update()
{
    if(scene()->mouseGrabberItem() == this || this->edges_.size() == 0)
    {
        nextPosition_ = pos();
        return;
    }
    const double c1 = 100 * 10 / (double)(this->graph_->size());
    const double c2 = 20.0;
    const double c3 = 1;
    double vx = 0;
    double vy = 0;
    double mass = c2 * (this->edges_.size() + 1);
    for(auto vert: *(this->graph_->verticies()))
    {
        assert(vert != NULL);
        if(vert->neighbors() == 0)
            continue;
        QPointF r = mapToItem(vert, 0, 0);
        if(r.x() * r.x() + r.y() * r.y() > 0)
        {
            vx += r.x() * c1 / (r.x() * r.x() + r.y() * r.y());
            vy += r.y() * c1 / (r.x() * r.x() + r.y() * r.y());
        }
    }
    for(auto e: edges_)
    {
        if(e->getCapacity() == 0)
            continue;
        Vertex* vert = NULL;
        if(e->getFrom() == this)
            vert = e->getTo();
        else if(e->getTo() == this)
            vert = e->getFrom();
        assert(vert != NULL);
        QPointF r = mapToItem(vert, 0, 0);
        vx -= r.x()/mass;
        vy -= r.y()/mass;
    }
    vx -= c3 * velocity_.x();
    vy -= c3 * velocity_.y();
    if(qAbs(vx) < 0.13 && qAbs(vy) < 0.13)
        this->velocity_ = QPointF(0, 0);
    else
        this->velocity_ += QPointF(vx, vy);
}
void Vertex::updatePosition()
{
    int offsetLimit = 30;
    this->nextPosition_ += velocity_;
    this->nextPosition_.setX(qMin(qMax(this->nextPosition_.x(), scene()->sceneRect().left() + offsetLimit), scene()->sceneRect().right() - offsetLimit));
    if(nextPosition_.x() == scene()->sceneRect().left() + offsetLimit || nextPosition_.x() == scene()->sceneRect().right() - offsetLimit )
        velocity_.setX(-velocity_.x());
    this->nextPosition_.setY(qMin(qMax(this->nextPosition_.y(), scene()->sceneRect().top() + offsetLimit), scene()->sceneRect().bottom() - offsetLimit));
    if(nextPosition_.y() == scene()->sceneRect().top() + offsetLimit || nextPosition_.y() == scene()->sceneRect().bottom() - offsetLimit )
        velocity_.setY(-velocity_.y());
}

bool Vertex::advance()
{
    if(this->pos() == nextPosition_)
        return false;
    setPos(nextPosition_);
    return true;
}
unsigned long long Vertex::neighbors()
{
    return this->edges_.size();
}
void Vertex::setColor(QColor color)
{
    this->color_ = color;
}
unsigned long long Vertex::getPotential() const
{
    return potential_;
}
void Vertex::setPotential(unsigned long long value)
{
    potential_ = value;
}
bool Vertex::getActive() const
{
    return active_;
}
void Vertex::setActive(bool value)
{
    active_ = value;
}
LayeredOptions Vertex::getDisplayType()
{
    return displayType_;
}
void Vertex::setDisplayType(LayeredOptions displayType)
{
    this->displayType_ = displayType;
}
bool Vertex::getHighlighted() const
{
    return highlighted_;
}
void Vertex::setHighlighted(bool value)
{
    highlighted_ = value;
}

#ifndef VERTEX_H
#define VERTEX_H

#include "VisualEdge.h"
#include "VisualGraph.h"
#include "LayeredOptions.h"
#include <QGraphicsItem>
#include <vector>

class VisualEdge;
class VisualGraph;

class Vertex: public QGraphicsItem
{
    public:
        Vertex(unsigned long long id_, VisualGraph* graph_, QPointF position);
        void addEdge(VisualEdge* edge);
        void removeEdge(unsigned long long edgeId);

        QRectF boundingRect() const Q_DECL_OVERRIDE;
        QPainterPath shape() const Q_DECL_OVERRIDE;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) Q_DECL_OVERRIDE;

        void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

        unsigned long long getId();

        void hideNode();
        void showNode();
        void update();
        void updatePosition();
        bool advance();
        unsigned long long neighbors();
        void setColor(QColor color_);
        unsigned long long getPotential() const;
        void setPotential(unsigned long long value);
        bool getActive() const;
        void setActive(bool value);
        LayeredOptions getDisplayType();
        void setDisplayType(LayeredOptions displayType_);
        bool getHighlighted() const;
        void setHighlighted(bool value);

    signals:

    public slots:

    private:
        unsigned long long id_;
        QPointF velocity_ = QPointF(0, 0);
        std::vector<VisualEdge*> edges_;
        QPointF nextPosition_;
        VisualGraph* graph_;
        unsigned long long potential_ = 0;
        bool active_ = 1;
        QColor color_;
        LayeredOptions displayType_ = ID;
        bool highlighted_ = false;
};

#endif // VERTEX_H

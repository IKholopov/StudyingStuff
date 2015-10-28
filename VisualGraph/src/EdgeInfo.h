#ifndef EDGEINFO_H
#define EDGEINFO_H

#include "VisualEdge.h"
#include <QGraphicsItem>

class VisualEdge;

class EdgeInfo : public QGraphicsItem
{
    public:
        EdgeInfo(VisualEdge* edge_);

        void update();
    protected:
        QRectF boundingRect() const Q_DECL_OVERRIDE;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    private:
        VisualEdge* edge_;
};

#endif // EDGEINFO_H

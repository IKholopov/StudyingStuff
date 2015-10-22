#ifndef EDGEINFO_H
#define EDGEINFO_H

#include <QGraphicsItem>
#include "VisualEdge.h"

class VisualEdge;

class EdgeInfo : public QGraphicsItem
{
    public:
        EdgeInfo(VisualEdge* edge);

        void Update();
    protected:
        QRectF boundingRect() const Q_DECL_OVERRIDE;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    private:
        VisualEdge* edge;
};

#endif // EDGEINFO_H

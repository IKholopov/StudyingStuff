#ifndef VISUALEDGE_H
#define VISUALEDGE_H

#include "Vertex.h"
#include "EdgeInfo.h"
#include <QObject>


class Vertex;
class EdgeInfo;

class VisualEdge: public QGraphicsItem
{
    public:
        VisualEdge(QGraphicsScene* scene, unsigned long long id_, Vertex* from_, Vertex* to_, unsigned long long capacity_,
                   int displayType_ = 0);
        ~VisualEdge();
        unsigned long long getId() const;
        Vertex* getTo() const;
        Vertex* getFrom() const;
        EdgeInfo* getInfo() const;
        unsigned long long getCapacity() const;
        void setCapacity(unsigned long long value);
        int getDisplayType();
        void setDisplayType(int displayType_);
        unsigned long long getFlow() const;
        void setFlow(unsigned long long value);
        void hideEdge();
        void showEdge();
        void update();
        bool isHovered();

        QRectF boundingRect() const Q_DECL_OVERRIDE;

        bool getActive() const;
        void setActive(bool value);
        bool getHighlighted() const;
        void setHighlighted(bool value);

    signals:

    public slots:
    protected:
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
        void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    private:
        unsigned long long id_;
        Vertex* from_;
        Vertex* to_;
        unsigned long long capacity_;
        unsigned long long flow_ = 0;
        bool isHovered_;
        EdgeInfo* info_;
        QColor color_ = Qt::black;
        bool active_ = 1;
        int displayType_;
        bool highlighted_ = false;
};

#endif // EDGE_H

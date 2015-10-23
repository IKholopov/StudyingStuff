#ifndef VISUALEDGE_H
#define VISUALEDGE_H

#include <QObject>

#include "Vertex.h"
#include "EdgeInfo.h"

class Vertex;
class EdgeInfo;

class VisualEdge: public QGraphicsItem
{
    public:
        VisualEdge(QGraphicsScene* scene, unsigned long long id, Vertex* from, Vertex* to, unsigned long long capacity,
                   int displayType = 0);
        ~VisualEdge();
        unsigned long long GetId() const;
        Vertex* GetTo() const;
        Vertex* GetFrom() const;
        EdgeInfo* GetInfo() const;
        unsigned long long GetCapacity() const;
        void SetCapacity(unsigned long long value);
        int GetDisplayType();
        void SetDisplayType(int displayType);
        unsigned long long GetFlow() const;
        void SetFlow(unsigned long long value);
        void HideEdge();
        void ShowEdge();
        void Update();
        bool IsHovered();

        QRectF boundingRect() const Q_DECL_OVERRIDE;

        bool GetActive() const;
        void SetActive(bool value);
        bool GetHighlighted() const;
        void SetHighlighted(bool value);

    signals:

    public slots:
    protected:
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
        void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    private:
        unsigned long long id;
        Vertex* from;
        Vertex* to;
        unsigned long long capacity;
        unsigned long long flow = 0;
        bool isHovered;
        EdgeInfo* info;
        QColor color = Qt::black;
        bool active = 1;
        int displayType;
        bool highlighted = false;
};

#endif // EDGE_H

#ifndef VERTEX_H
#define VERTEX_H

#include <QGraphicsItem>
#include <vector>
#include "VisualEdge.h"
#include "VisualGraph.h"

class VisualEdge;
class VisualGraph;

class Vertex: public QGraphicsItem
{
    public:
        Vertex(unsigned long long id, VisualGraph* graph, QPointF position);
        void AddEdge(VisualEdge* edge);
        void RemoveEdge(unsigned long long edgeId);

        QRectF boundingRect() const Q_DECL_OVERRIDE;
        QPainterPath shape() const Q_DECL_OVERRIDE;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) Q_DECL_OVERRIDE;

        void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

        unsigned long long GetId();

        void HideNode();
        void ShowNode();
        void Update();
        void UpdatePosition();
        bool advance();
        unsigned long long Neighbors();
        void SetColor(QColor color);
        unsigned long long GetPotential() const;
        void SetPotential(unsigned long long value);
        bool GetActive() const;
        void SetActive(bool value);
        int GetDisplayType();
        void SetDisplayType(int displayType);
        bool GetHighlighted() const;
        void SetHighlighted(bool value);

    signals:

    public slots:

    private:
        unsigned long long id;
        QPointF velocity = QPointF(0, 0);
        std::vector<VisualEdge*> edges;
        QPointF nextPosition;
        VisualGraph* graph;
        unsigned long long potential = 0;
        bool active = 1;
        QColor color;
        int displayType = 0;
        bool highlighted = false;
};

#endif // VERTEX_H

#ifndef GRAPHAREA
#define GRAPHAREA

#include <QGraphicsView>

class GraphArea: public QGraphicsView
{
    public:
        GraphArea(QWidget* parent):QGraphicsView(parent) {};

        virtual void SetTimerId(int id) = 0;
        virtual int GetTimerId() = 0;
};

#endif // GRAPHAREA


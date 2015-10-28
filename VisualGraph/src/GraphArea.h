#ifndef GRAPHAREA
#define GRAPHAREA

#include <QGraphicsView>

class GraphArea: public QGraphicsView
{
    public:
        GraphArea(QWidget* parent):QGraphicsView(parent) {};

        virtual void setTimerId(int id) = 0;
        virtual int getTimerId() = 0;
};

#endif // GRAPHAREA


#ifndef GRAPHSCENE
#define GRAPHSCENE

#include "IGraphScene.h"
#include <QGraphicsScene>

class GraphScene: public IGraphScene, public QGraphicsScene
{
    public:
        GraphScene(QObject* parent):QGraphicsScene(parent) {};
};


#endif // GRAPHSCENE


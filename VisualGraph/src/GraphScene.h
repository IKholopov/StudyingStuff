#ifndef GRAPHSCENE
#define GRAPHSCENE

#include <QGraphicsScene>
#include "IGraphScene.h"

class GraphScene: public IGraphScene, public QGraphicsScene
{
    public:
        GraphScene(QObject* parent):QGraphicsScene(parent) {};
};


#endif // GRAPHSCENE


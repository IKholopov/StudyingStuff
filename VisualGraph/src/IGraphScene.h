#ifndef IGRAPHSCENE
#define IGRAPHSCENE

#include "Vertex.h"

class Vertex;

class IGraphScene
{
    public:
        virtual void mousePressedOnVertex(Vertex* v) = 0;
};

#endif // IGRAPHSCENE


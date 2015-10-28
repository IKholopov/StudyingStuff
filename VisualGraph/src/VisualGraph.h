#ifndef VISUALGRAPH_H
#define VISUALGRAPH_H

class Vertex;
class VisualEdge;
class GraphScene;

#include "GraphScene.h"
#include "Vertex.h"
#include "GraphArea.h"
#include "VisualEdge.h"
#include "LayeredOptions.h"

class VisualGraph
{
    public:
        VisualGraph(GraphScene* scene, GraphArea* view);
        VisualGraph(GraphScene* scene, GraphArea* view, const std::vector<std::vector<unsigned long long> >& graphData);
        VisualGraph(GraphScene* scene, GraphArea* view, std::string filename);
        ~VisualGraph();
        std::vector<std::vector<unsigned long long> > clone();

        void addNode(QPointF position);
        void addEdge(unsigned long long from, unsigned long long to, unsigned long long capacity);
        VisualEdge* getEdge(unsigned long long id);
        Vertex* getNode(unsigned long long id);
        unsigned long long getSize();
        void hideEdge(unsigned long long id);
        void displayEdge(unsigned long long id);
        void hideNode(unsigned long long id);
        void displayNode(unsigned long long id);
        void update();
        void movedGraph();
        void disableGraph();
        void displayGraph();
        void hideGraph();
        void setEdgeDisplayType(int dt);
        void setNodeDisplayType(LayeredOptions dt);
        void removeGraph();
        void save() const;
        bool isActive() const;
        bool isMoved() const;

        unsigned long long size() const;
        const std::vector<Vertex*>* verticies() const;
        GraphScene* scene();
        GraphArea* view();
    signals:

    public slots:

    private:
        unsigned long long idVertexCounter_;
        unsigned long long idEdgeCounter_;
        GraphScene* scene_;
        GraphArea* view_;
        std::vector<Vertex*> verticies_;
        std::vector<VisualEdge*> edges_;
        bool nodeMoved_;
        bool active_ = 1;
};

#endif // VISUALGRAPH_H

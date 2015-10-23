#ifndef VISUALGRAPH_H
#define VISUALGRAPH_H

class Vertex;
class VisualEdge;
class GraphScene;

#include "GraphScene.h"
#include "Vertex.h"
#include "GraphArea.h"
#include "VisualEdge.h"

class VisualGraph
{
    public:
        VisualGraph(GraphScene* scene, GraphArea* view);
        VisualGraph(GraphScene* scene, GraphArea* view, const std::vector<std::vector<unsigned long long> >& graphData);
        VisualGraph(GraphScene* scene, GraphArea* view, std::string filename);
        ~VisualGraph();
        std::vector<std::vector<unsigned long long> > Clone();

        void AddNode(QPointF position);
        void AddEdge(unsigned long long from, unsigned long long to, unsigned long long capacity);
        VisualEdge* GetEdge(unsigned long long id);
        Vertex* GetNode(unsigned long long id);
        unsigned long long GetSize();
        void HideEdge(unsigned long long id);
        void DisplayEdge(unsigned long long id);
        void HideNode(unsigned long long id);
        void DisplayNode(unsigned long long id);
        void Update();
        void MovedGraph();
        void DisableGraph();
        void DisplayGraph();
        void HideGraph();
        void SetEdgeDisplayType(int dt);
        void SetNodeDisplayType(int dt);
        void RemoveGraph();
        void Save() const;
        bool IsActive() const;
        bool IsMoved() const;

        unsigned long long Size() const;
        const std::vector<Vertex*>* Verticies() const;
        GraphScene* Scene();
        GraphArea* View();
    signals:

    public slots:

    private:
        unsigned long long idVertexCounter;
        unsigned long long idEdgeCounter;
        GraphScene* scene;
        GraphArea* view;
        std::vector<Vertex*> verticies;
        std::vector<VisualEdge*> edges;
        bool nodeMoved;
        bool active = 1;
};

#endif // VISUALGRAPH_H

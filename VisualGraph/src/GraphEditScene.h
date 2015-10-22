#ifndef GRAPHEDITSCENE_H
#define GRAPHEDITSCENE_H

#include <QGraphicsSceneMouseEvent>
#include "GraphScene.h"
#include "EditGraphToolBar.h"
#include "VisualGraph.h"
#include "GraphEditArea.h"

class VisualGraph;
class GraphEditArea;

class GraphEditScene : public GraphScene
{
    Q_OBJECT

    public:
        GraphEditScene(EditGraphToolBar toolbar, GraphEditArea* parent = 0);
        ~GraphEditScene();

        void AddNode(QPointF position);
        void AddEdge(unsigned long long from, unsigned long long to, unsigned long long capacity);
        void LoadGraph(std::string filename);
        void NewGraph();
        EditGraphTools GetActiveTool();
        VisualGraph* GetGraph() const;

        void mousePressedOnVertex(Vertex* v);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* event) Q_DECL_OVERRIDE;

    signals:

    public slots:
        void SetActiveTool(EditGraphTools tool);
    private:
        VisualGraph* graph;
        EditGraphToolBar toolbar;
        GraphEditArea* view;
};

#endif // GRAPHEDITSCENE_H

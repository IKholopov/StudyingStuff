#ifndef GRAPHEDITSCENE_H
#define GRAPHEDITSCENE_H

#include "GraphScene.h"
#include "EditGraphToolBar.h"
#include "VisualGraph.h"
#include "GraphEditArea.h"
#include <QGraphicsSceneMouseEvent>

class VisualGraph;
class GraphEditArea;

class GraphEditScene : public GraphScene
{
    Q_OBJECT

    public:
        GraphEditScene(EditGraphToolBar toolbar_, GraphEditArea* parent = 0);
        ~GraphEditScene();

        void addNode(QPointF position);
        void addEdge(unsigned long long from, unsigned long long to, unsigned long long capacity);
        void loadGraph(std::string filename);
        void newGraph();
        EditGraphTools getActiveTool();
        VisualGraph* getGraph() const;

        void mousePressedOnVertex(Vertex* v);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* event) Q_DECL_OVERRIDE;

    signals:

    public slots:
        void setActiveTool(EditGraphTools tool);
    private:
        VisualGraph* graph_;
        EditGraphToolBar toolbar_;
        GraphEditArea* view_;
};

#endif // GRAPHEDITSCENE_H

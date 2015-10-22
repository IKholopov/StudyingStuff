#ifndef GRAPHEDITAREA_H
#define GRAPHEDITAREA_H


#include "GraphArea.h"
#include "EditGraphToolBar.h"
#include "Vertex.h"

class GraphEditScene;
class Vertex;

class AddEdgeTool
{
    public:
        Vertex* GetFrom() const;
        void SetFrom(Vertex* value);
        Vertex* GetTo() const;
        void SetTo(Vertex* value);

        void Initialize();
        void Process(GraphEditScene* scene, Vertex* v);

    private:
        Vertex* from = NULL;
        Vertex* to = NULL;
};

class GraphEditArea : public GraphArea
{
    Q_OBJECT
    public:
        GraphEditArea( QWidget* parent = 0);
        ~GraphEditArea();

        void drawBackground(QPainter* painter, const QRectF& rect);

        void SetActiveTool(EditGraphTools tool);
        void SetTimerId(int id);
        int GetTimerId();
        void SaveGraph();
        void LoadGraph();
        void NewGraph();

        std::vector<std::vector<unsigned long long> > CloneGraph();
        void InitializeAddEdge();
        void ProcessAddEdge(GraphEditScene* scene, Vertex* v);
    protected:
        void timerEvent(QTimerEvent* event) Q_DECL_OVERRIDE;

    signals:
    public slots:
    private:
        int timerId;
        AddEdgeTool addEdgeTool;
};


#endif // GRAPHEDITAREA_H

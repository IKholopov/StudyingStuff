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
        Vertex* getFrom() const;
        void setFrom(Vertex* value);
        Vertex* getTo() const;
        void setTo(Vertex* value);

        void initialize();
        void process(GraphEditScene* scene, Vertex* v);

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

        void setActiveTool(EditGraphTools tool);
        void setTimerId(int id);
        int getTimerId();
        void saveGraph();
        void loadGraph();
        void newGraph();

        std::vector<std::vector<unsigned long long> > cloneGraph();
        void initializeAddEdge();
        void processAddEdge(GraphEditScene* scene, Vertex* v);
    protected:
        void timerEvent(QTimerEvent* event) Q_DECL_OVERRIDE;

    signals:
    public slots:
    private:
        int timerId_;
        AddEdgeTool addEdgeTool_;
};


#endif // GRAPHEDITAREA_H

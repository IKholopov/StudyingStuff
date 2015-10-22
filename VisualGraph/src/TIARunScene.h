#ifndef TIARUNSCENE_H
#define TIARUNSCENE_H

#include "AlgorithmRunView.h"
#include "GraphScene.h"
#include "NetworkDelta.h"
#include "TIAGraphDeltaIds.h"

class TIARunScene : public GraphScene
{
    Q_OBJECT
    public:
        TIARunScene(AlgorithmRunView* parent = 0);

        void mousePressedOnVertex(Vertex* v);

        void Initialize(const std::vector<std::vector<unsigned long long> >& graphData);
        void NextStep();
        void PrevStep();
        std::vector<VisualGraph*> GetGraphs();
        void ProcessEdgeChange(VisualGraph* graph, NetworkEdgeChange* change);
        void ProcessNodeChange(VisualGraph* graph, NetworkNodeChange* change);
        void ProcessBackwardEdgeChange(VisualGraph* graph, NetworkEdgeChange* change);
        void ProcessBackwardNodeChange(VisualGraph* graph, NetworkNodeChange* change);

    protected:
        void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;
    private:
        AlgorithmRunView* view;
        VisualGraph* original;
        std::vector<NetworkDelta>* deltas;
        VisualGraph* layered;
        VisualGraph* residual;
        long long currentStep;
        TIADeltas currentGraph;
};

#endif // TIARUNSCENE_H

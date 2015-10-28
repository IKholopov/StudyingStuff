#ifndef TIARUNSCENE_H
#define TIARUNSCENE_H

#include "AlgorithmRunView.h"
#include "GraphScene.h"
#include "NetworkDelta.h"
#include "TIAGraphDeltaIds.h"
#include "LayeredResidualSwitcher.h"

#include <QTextEdit>

class LayeredResidualSwitcher;
class AlgorithmRunView;

class TIARunScene : public GraphScene
{
    Q_OBJECT
    public:
        TIARunScene(QTextEdit* messageBox_, LayeredResidualSwitcher* switcher, AlgorithmRunView* parent = 0);
        ~TIARunScene();
        void mousePressedOnVertex(Vertex* v);

        void initialize(const std::vector<std::vector<unsigned long long> >& graphData);
        void nextStep();
        void prevStep();
        std::vector<VisualGraph*> getGraphs();
        void processEdgeChange(VisualGraph* graph, NetworkEdgeChange* change);
        void processNodeChange(VisualGraph* graph, NetworkNodeChange* change);
        void processBackwardEdgeChange(VisualGraph* graph, NetworkEdgeChange* change);
        void processBackwardNodeChange(VisualGraph* graph, NetworkNodeChange* change);
        void showLayeredPotential();
        void showLayeredId();
        void showLayered();
        void showResidual();
    protected:
        void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;
    private:
        AlgorithmRunView* view_;
        VisualGraph* original_;
        std::vector<NetworkDelta>* deltas_;
        VisualGraph* layered_;
        VisualGraph* residual_;
        unsigned long long currentStep_;
        TIADeltas currentGraph_;
        QTextEdit* messageBox_;
        LayeredResidualSwitcher* switcher_;
        std::vector<VisualEdge*> highlightedEdges_;
        std::vector<Vertex*> highlightedNodes_;
};

#endif // TIARUNSCENE_H

#ifndef ALGORITHMRUNVIEW_H
#define ALGORITHMRUNVIEW_H

#include "GraphArea.h"
#include "LayeredResidualSwitcher.h"

#include <QTextEdit>

class LayeredResidualSwitcher;

class AlgorithmRunView : public GraphArea
{
    Q_OBJECT
    public:
        AlgorithmRunView(QTextEdit* messageBox_, LayeredResidualSwitcher* switcher, QWidget* parent = 0);

        void drawBackground(QPainter* painter, const QRectF& rect);
        void setTimerId(int id);
        int getTimerId();

        void initialize(const std::vector<std::vector<unsigned long long> >& graphData);
        void nextStep();
        void prevStep();

        void timerEvent(QTimerEvent* event);

    private:
        int timerId_;
        QTextEdit* messageBox_;
};

#endif // ALGORITHMRUNVIEW_H

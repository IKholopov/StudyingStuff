#ifndef ALGORITHMRUNVIEW_H
#define ALGORITHMRUNVIEW_H

#include "GraphArea.h"

#include <QTextEdit>

class AlgorithmRunView : public GraphArea
{
    Q_OBJECT
    public:
        AlgorithmRunView(QTextEdit* messageBox, QWidget* parent = 0);

        void drawBackground(QPainter* painter, const QRectF& rect);
        void SetTimerId(int id);
        int GetTimerId();

        void Initialize(const std::vector<std::vector<unsigned long long> >& graphData);
        void NextStep();
        void PrevStep();

        void timerEvent(QTimerEvent* event);

    private:
        int timerId;
        QTextEdit* messageBox;

};

#endif // ALGORITHMRUNVIEW_H
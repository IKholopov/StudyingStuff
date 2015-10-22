#ifndef ALGORYTHMRUN_H
#define ALGORYTHMRUN_H

#include <QMainWindow>
#include "src/AlgorithmRunView.h"

namespace Ui {
class AlgorythmRun;
}

class AlgorythmRun : public QMainWindow
{
        Q_OBJECT

    public:
        explicit AlgorythmRun(QWidget *parent = 0);
        ~AlgorythmRun();

        void Initialize(std::vector<std::vector<unsigned long long>> graphData);
    private:
        AlgorithmRunView* graphArea;
        Ui::AlgorythmRun *ui;
};

#endif // ALGORYTHMRUN_H

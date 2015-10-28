#ifndef ALGORYTHMRUN_H
#define ALGORYTHMRUN_H

#include "src/AlgorithmRunView.h"
#include <QMainWindow>

namespace Ui {
class AlgorythmRun;
}

class AlgorythmRun : public QMainWindow
{
        Q_OBJECT

    public:
        explicit AlgorythmRun(QWidget *parent = 0);
        ~AlgorythmRun();

        void initialize(std::vector<std::vector<unsigned long long>> graphData);
    private:
        AlgorithmRunView* graphArea_;
        LayeredResidualSwitcher* switcher_;
        Ui::AlgorythmRun *ui_;
};

#endif // ALGORYTHMRUN_H

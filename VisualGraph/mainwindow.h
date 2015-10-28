#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/GraphEditArea.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        GraphEditArea* graphArea_;
        Ui::MainWindow* ui_;
};

#endif // MAINWINDOW_H

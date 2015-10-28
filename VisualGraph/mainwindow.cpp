#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSignalMapper>
#include "src/EditGraphToolBar.h"
#include "algorythmrun.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    graphArea_ = new GraphEditArea(ui_->GraphField);
    QObject::connect(ui_->AddEdgeButton, &QToolButton::pressed,
        [=](){
            this->graphArea_->setActiveTool(EditGraphTools::AddEdge);
            ui_->AddNodeButton->setChecked(0);
        });
    QObject::connect(ui_->AddNodeButton, &QToolButton::pressed,
        [=](){
            this->graphArea_->setActiveTool(EditGraphTools::AddNode);
            this->graphArea_->initializeAddEdge();
            ui_->AddEdgeButton->setChecked(0);
        });
    QObject::connect(ui_->SaveButton, &QToolButton::clicked,
        [=](){
            graphArea_->saveGraph();
        });
    QObject::connect(ui_->OpenButton, &QToolButton::clicked,
        [=](){
            graphArea_->loadGraph();
        });
    QObject::connect(ui_->NewButton, &QToolButton::clicked,
        [=](){
            graphArea_->newGraph();
        });
    QObject::connect(ui_->StartAlgorythmButton, &QToolButton::clicked,
        [=](){
            static AlgorythmRun w;
            w.initialize(this->graphArea_->cloneGraph());
            w.show();
        });
}

MainWindow::~MainWindow()
{
    delete ui_;
}

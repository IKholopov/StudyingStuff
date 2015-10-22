#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSignalMapper>
#include "src/EditGraphToolBar.h"
#include "algorythmrun.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    graphArea = new GraphEditArea(ui->GraphField);
    QObject::connect(ui->AddEdgeButton, &QToolButton::pressed,
        [=](){
            this->graphArea->SetActiveTool(EditGraphTools::AddEdge);
            ui->AddNodeButton->setChecked(0);
        });
    QObject::connect(ui->AddNodeButton, &QToolButton::pressed,
        [=](){
            this->graphArea->SetActiveTool(EditGraphTools::AddNode);
            this->graphArea->InitializeAddEdge();
            ui->AddEdgeButton->setChecked(0);
        });
    QObject::connect(ui->SaveButton, &QToolButton::clicked,
        [=](){
            graphArea->SaveGraph();
        });
    QObject::connect(ui->OpenButton, &QToolButton::clicked,
        [=](){
            graphArea->LoadGraph();
        });
    QObject::connect(ui->NewButton, &QToolButton::clicked,
        [=](){
            graphArea->NewGraph();
        });
    QObject::connect(ui->StartAlgorythmButton, &QToolButton::clicked,
        [=](){
            static AlgorythmRun w;
            w.Initialize(this->graphArea->CloneGraph());
            w.show();
        });
}

MainWindow::~MainWindow()
{
    delete ui;
}

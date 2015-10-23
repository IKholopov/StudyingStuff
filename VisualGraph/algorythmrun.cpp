#include "algorythmrun.h"
#include "ui_algorythmrun.h"
//#include "src/GraphParser.h"

AlgorythmRun::AlgorythmRun(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AlgorythmRun)
{
    ui->setupUi(this);
    graphArea = new AlgorithmRunView(this->ui->TextMessage, this->ui->GraphField);
    QObject::connect(this->ui->NextButton, &QToolButton::clicked,
        [=](){
            graphArea->NextStep();
        });
    QObject::connect(this->ui->PrevButton, &QToolButton::clicked,
        [=](){
            graphArea->PrevStep();
        });
}
AlgorythmRun::~AlgorythmRun()
{
    delete ui;
}

void AlgorythmRun::Initialize(std::vector<std::vector<unsigned long long> > graphData)
{
    graphArea->Initialize(graphData);
}

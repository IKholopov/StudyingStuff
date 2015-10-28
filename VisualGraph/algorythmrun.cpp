#include "algorythmrun.h"
#include "ui_algorythmrun.h"

AlgorythmRun::AlgorythmRun(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::AlgorythmRun)
{
    ui_->setupUi(this);
    this->switcher_ = new LayeredResidualSwitcher(ui_->layeredButton, ui_->residualButton, ui_->PotentialButton, ui_->idButton);
    graphArea_ = new AlgorithmRunView(this->ui_->TextMessage, switcher_, this->ui_->GraphField);
    QObject::connect(this->ui_->NextButton, &QToolButton::clicked,
        [=](){
            graphArea_->nextStep();
        });
    QObject::connect(this->ui_->PrevButton, &QToolButton::clicked,
        [=](){
            graphArea_->prevStep();
        });
    QObject::connect(this->ui_->idButton, &QRadioButton::clicked,
        [=](){
            switcher_->checkLayeredOption(ID);
        });
    QObject::connect(this->ui_->PotentialButton, &QRadioButton::clicked,
        [=](){
            switcher_->checkLayeredOption(POTENTIAL);
        });
    QObject::connect(this->ui_->layeredButton, &QRadioButton::clicked,
        [=](){
            switcher_->check(LAYERED);
        });
    QObject::connect(this->ui_->residualButton, &QRadioButton::clicked,
        [=](){
            switcher_->check(RESIDUAL);
        });
}
AlgorythmRun::~AlgorythmRun()
{
    delete ui_;
}

void AlgorythmRun::initialize(std::vector<std::vector<unsigned long long> > graphData)
{
    graphArea_->initialize(graphData);
}

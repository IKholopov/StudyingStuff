#include "LayeredResidualSwitcher.h"
#include <assert.h>

LayeredResidualSwitcher::LayeredResidualSwitcher(QRadioButton* layeredButton, QRadioButton* residualButton,
                                                 QRadioButton* potentialButton, QRadioButton* idButton): layeredButton_(layeredButton),
                                                 residualButton_(residualButton), potentialButton_(potentialButton), idButton_(idButton)
{
    scene_ = NULL;
}

void LayeredResidualSwitcher::enable(TIADeltas delta)
{
    this->layeredButton_->setEnabled(true);
    this->residualButton_->setEnabled(true);
    assert(delta == RESIDUAL || delta == LAYERED);
    this->setChecked(delta);
}
void LayeredResidualSwitcher::disable()
{
    this->layeredButton_->setEnabled(false);
    this->residualButton_->setEnabled(false);
    this->potentialButton_->setEnabled(false);
    this->idButton_->setEnabled(false);
}
void LayeredResidualSwitcher::setScene(TIARunScene* scene)
{
    this->scene_ = scene;
}
void LayeredResidualSwitcher::check(TIADeltas delta)
{
    assert(delta == RESIDUAL || delta == LAYERED);
    assert(scene_ != NULL);
    this->setChecked(delta);
    if(delta == RESIDUAL)
        this->scene_->showResidual();
    if(delta == LAYERED)
        this->scene_->showLayered();
}
void LayeredResidualSwitcher::checkLayeredOption(LayeredOptions option)
{
    assert(scene_ != NULL);
    if(option == ID) {
        this->idButton_->setChecked(true);
        this->scene_->showLayeredId();
    }
    if(option == POTENTIAL) {
        this->potentialButton_->setChecked(true);
        this->scene_->showLayeredPotential();
    }
}
void LayeredResidualSwitcher::setChecked(TIADeltas delta)
{
    assert(delta == RESIDUAL || delta == LAYERED);
    if(delta == RESIDUAL) {
        this->residualButton_->setChecked(true);
        this->layeredButton_->setChecked(false);
        this->potentialButton_->setEnabled(false);
        this->idButton_->setEnabled(false);
    }
    if(delta == LAYERED) {
        this->residualButton_->setChecked(false);
        this->layeredButton_->setChecked(true);
        this->potentialButton_->setEnabled(true);
        this->idButton_->setEnabled(true);
    }
}

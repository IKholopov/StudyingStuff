#ifndef LAYEREDRESIDUALSWITCHER_H
#define LAYEREDRESIDUALSWITCHER_H

#include "TIAGraphDeltaIds.h"
#include "TIARunScene.h"
#include "LayeredOptions.h"
#include <QRadioButton>

class TIARunScene;

class LayeredResidualSwitcher
{
    public:
        LayeredResidualSwitcher(QRadioButton* layeredButton, QRadioButton* residualButton,
                                QRadioButton* potentialButton, QRadioButton* idButton);
        void enable(TIADeltas delta);
        void disable();
        void setChecked(TIADeltas delta);
        void setScene(TIARunScene* scene);
        void check(TIADeltas delta);
        void checkLayeredOption(LayeredOptions option);
    private:
        QRadioButton* layeredButton_;
        QRadioButton* residualButton_;
        QRadioButton* potentialButton_;
        QRadioButton* idButton_;
        TIARunScene* scene_;
};

#endif // LAYEREDRESIDUALSWITCHER_H

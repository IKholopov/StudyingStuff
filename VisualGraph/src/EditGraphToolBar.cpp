#include "EditGraphToolBar.h"

EditGraphToolBar::EditGraphToolBar(): activeTool_(None)
{
}

EditGraphTools EditGraphToolBar::getActiveTool()
{
    return activeTool_;
}
void EditGraphToolBar::setTool(EditGraphTools tool)
{
    this->activeTool_ = tool;
}


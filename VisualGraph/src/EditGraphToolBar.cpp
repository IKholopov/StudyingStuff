#include "EditGraphToolBar.h"

EditGraphToolBar::EditGraphToolBar(): activeTool(None)
{
}

EditGraphTools EditGraphToolBar::GetActiveTool()
{
    return activeTool;
}
void EditGraphToolBar::SetTool(EditGraphTools tool)
{
    this->activeTool = tool;
}


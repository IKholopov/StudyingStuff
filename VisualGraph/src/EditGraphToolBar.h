#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>

enum EditGraphTools { None, AddNode, AddEdge };

class EditGraphToolBar
{
    public:
        EditGraphToolBar();
        EditGraphTools GetActiveTool();
        void SetTool(EditGraphTools tool);
    signals:

    public slots:
    private:
        EditGraphTools activeTool;
};

#endif // TOOLBAR_H

#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>

enum EditGraphTools { None, AddNode, AddEdge };

class EditGraphToolBar
{
    public:
        EditGraphToolBar();
        EditGraphTools getActiveTool();
        void setTool(EditGraphTools tool);
    signals:

    public slots:
    private:
        EditGraphTools activeTool_;
};

#endif // TOOLBAR_H

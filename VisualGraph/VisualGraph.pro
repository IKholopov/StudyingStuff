#-------------------------------------------------
#
# Project created by QtCreator 2015-10-06T19:51:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisualGraph
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    src/GraphEditArea.cpp \
    src/EditGraphToolBar.cpp \
    src/VisualGraph.cpp \
    src/Vertex.cpp \
    src/GraphEditScene.cpp \
    algorythmrun.cpp \
    src/EdgeInfo.cpp \
    src/GraphParser.cpp \
    src/VisualEdge.cpp \
    src/AlgorithmRunView.cpp \
    src/TIARunScene.cpp

HEADERS  += mainwindow.h \
    src/GraphEditArea.h \
    src/EditGraphToolBar.h \
    src/VisualGraph.h \
    src/Vertex.h \
    src/GraphEditScene.h \
    src/IGraphScene.h \
    src/GraphScene.h \
    src/GraphArea.h \
    algorythmrun.h \
    src/EdgeInfo.h \
    src/GraphParser.h \
    src/VisualEdge.h \
    src/AlgorithmRunView.h \
    src/TIARunScene.h

FORMS    += mainwindow.ui \
    algorythmrun.ui

#HEADERS += /home/igor/Study/Programming/ADV/Graph/include/ParentChildListOriented.h \
#            /home/igor/Study/Programming/ADV/Flow/include/NetworkGraph.h \
#            /home/igor/Study/Programming/ADV/Flow/include/NetworkEdge.h


#TARGETDEPS += /home/igor/Study/Programming/ADV-build/Flow/libFlow.a \
#              /home/igor/Study/Programming/ADV-build/Graph/libGraph.a

RESOURCES += \
    icons.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../ADV-build/Graph/release/ -lGraph
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../ADV-build/Graph/debug/ -lGraph
else:unix: LIBS += -L$$PWD/../../ADV-build/Graph/ -lGraph

INCLUDEPATH += $$PWD/../Graph/include
DEPENDPATH += $$PWD/../Graph/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../ADV-build/Graph/release/libGraph.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../ADV-build/Graph/debug/libGraph.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../ADV-build/Graph/release/Graph.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../ADV-build/Graph/debug/Graph.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../ADV-build/Graph/libGraph.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../ADV-build/Flow/release/ -lFlow
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../ADV-build/Flow/debug/ -lFlow
else:unix: LIBS += -L$$PWD/../../ADV-build/Flow/ -lFlow

INCLUDEPATH += $$PWD/../Flow/include
DEPENDPATH += $$PWD/../Flow/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../ADV-build/Flow/release/libFlow.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../ADV-build/Flow/debug/libFlow.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../ADV-build/Flow/release/Flow.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../ADV-build/Flow/debug/Flow.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../ADV-build/Flow/libFlow.a

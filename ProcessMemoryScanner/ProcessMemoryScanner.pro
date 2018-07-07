#-------------------------------------------------
#
# Project created by QtCreator 2018-06-02T22:09:19
#
#-------------------------------------------------

QT       += core gui
CONFIG += static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProcessMemoryScanner
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    taskselectiondialog.cpp \
    memoryscannerengine.cpp \
    memoryinteractionstratege.cpp \
    linuxmemoryinteraction.cpp \
    memoryscannerengineexception.cpp \
    TaskWidget-master/TaskWidget/processdescriptor.cpp \
    TaskWidget-master/TaskWidget/processfilterwidget.cpp \
    TaskWidget-master/TaskWidget/processmodel.cpp \
    TaskWidget-master/TaskWidget/processproxymodel.cpp \
    TaskWidget-master/TaskWidget/readlinuxprocessesstrategy.cpp \
    TaskWidget-master/TaskWidget/readprocessstrategy.cpp \
    TaskWidget-master/TaskWidget/taskwidget.cpp


HEADERS += \
        mainwindow.h \
    taskselectiondialog.h \
    memoryscannerengine.h \
    memoryinteractionstratege.h \
    linuxmemoryinteraction.h \
    memoryscannerengineexception.h \
    TaskWidget-master/TaskWidget/processdescriptor.h \
    TaskWidget-master/TaskWidget/processfilterwidget.h \
    TaskWidget-master/TaskWidget/processmodel.h \
    TaskWidget-master/TaskWidget/processproxymodel.h \
    TaskWidget-master/TaskWidget/readlinuxprocessesstrategy.h \
    TaskWidget-master/TaskWidget/readprocessstrategy.h \
    TaskWidget-master/TaskWidget/taskwidget.h


RESOURCES += \
    images.qrc \
    TaskWidget-master/TaskWidget/taskwidgetimages.qrc

DISTFILES += \
    TaskWidget-master/TaskWidget/images/find.png \
    TaskWidget-master/screenshot.png \
    TaskWidget-master/README.md \
    TaskWidget-master/LICENSE

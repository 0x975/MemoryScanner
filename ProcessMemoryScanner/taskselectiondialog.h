#ifndef TASKSELECTIONDIALOG_H
#define TASKSELECTIONDIALOG_H

#include <QApplication>
#include <QtWidgets>

//#include <TaskWidget/taskwidget.h>
#include <TaskWidget-master/TaskWidget/taskwidget.h>

class TaskSelectionDialog: public QDialog
{
    Q_OBJECT

public:
    TaskSelectionDialog(QWidget *parent = 0);
    ProcessDescriptor getSelectedProcess();

protected slots:
    void reciveProcess();

private:
    ProcessDescriptor selectedProcess;
    TaskWidget *taskWidget;

    QDialogButtonBox *btnBox;
};

#endif // TASKSELECTIONDIALOG_H

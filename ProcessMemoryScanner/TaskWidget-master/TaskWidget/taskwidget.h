#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QApplication>
#include <QtCore>
#include <QtGui>

#include <QWidget>
#include <QItemSelectionModel>
#include <QModelIndexList>
#include <QModelIndex>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QBoxLayout>
#include <QHeaderView>
#include <QTableView>
#include <QPushButton>
#include <QMessageBox>
#include <QGroupBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QRegExp>
#include <QTimer>
#include <QLabel>
#include <QDebug>

#include <iostream>
#include <vector>
#include <string>

#include "processfilterwidget.h"
#include "processmodel.h"
#include "processproxymodel.h"
#include "processdescriptor.h"

#include "readlinuxprocessesstrategy.h"
#include "readprocessstrategy.h"

class TaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TaskWidget(QWidget *parent = nullptr);

    void setReadStrategy(ReadProcessStrategy *strategy);
    ReadProcessStrategy* getReadStrategy();
    void setFilterVisable(bool condition);
    uint getSelectedProcessPID();
    ProcessDescriptor getSelectedProcessDescriptor();


private:
    void setupUpdateTimer();
    void setupFilterField();

signals:
    void selectionChanged();

private slots:
    void selectBtnHandler();
    void filterTextChanged();
    void update();

private:
    ProcessFilterWidget *processTextField;
    ReadProcessStrategy *readStrategy;

    QTableView *view;
    ProcessModel *model;
    ProcessProxyModel *pModel;
    QTimer *updateTimer;

    QPushButton *selectBtn;
    QGroupBox *filterBox;

    uint selectedProcessPID;
    QVector<ProcessDescriptor> processList;
};

#endif // TASKWIDGET_H

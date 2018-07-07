#include "taskwidget.h"

TaskWidget::TaskWidget(QWidget *parent) : QWidget(parent)
{
    readStrategy = new ReadLinuxProcessesStrategy();
    processList = QVector<ProcessDescriptor>::fromStdVector(readStrategy->readAllRunningProcesses());

    model = new ProcessModel(processList, NULL);
    pModel = new ProcessProxyModel();
    view = new QTableView;
    pModel->setSourceModel(model);

    setMinimumWidth(600);
    setMinimumHeight(400);

    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->horizontalHeader()->setStretchLastSection(true);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setSortingEnabled(true);
    view->sortByColumn(0, Qt::AscendingOrder);
    view->setModel(pModel);

    QVBoxLayout *widgetLayout = new QVBoxLayout;
    QHBoxLayout *btnLayout = new QHBoxLayout();

    selectBtn = new QPushButton("select process");
    connect(selectBtn, &QPushButton::pressed, this, &TaskWidget::selectBtnHandler);

    btnLayout->addWidget(selectBtn);
    btnLayout->addStretch();

    filterBox = new QGroupBox(tr("filter"));
    filterBox->setVisible(false);
    QGridLayout *filterBoxLayout = new QGridLayout();
    processTextField = new ProcessFilterWidget(pModel->header(), 2);

    connect(processTextField, &ProcessFilterWidget::filterChanged, this, &TaskWidget::filterTextChanged);

    filterBox->setLayout(filterBoxLayout);
    filterBoxLayout->addWidget(processTextField, 0, 0);

    widgetLayout->addWidget(filterBox);
    widgetLayout->addWidget(view);
    //widgetLayout->addLayout(btnLayout);

    //setupUpdateTimer();
    setLayout(widgetLayout);
}

void TaskWidget::setupUpdateTimer()
{
    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    updateTimer->start(1000);
}

void TaskWidget::setupFilterField()
{

}

void TaskWidget::setReadStrategy(ReadProcessStrategy *strategy)
{
    readStrategy = strategy;
}

ReadProcessStrategy* TaskWidget::getReadStrategy()
{
    return readStrategy;
}

void TaskWidget::setFilterVisable(bool condition)
{
    filterBox->setVisible(condition);
}

uint TaskWidget::getSelectedProcessPID()
{
    return selectedProcessPID;
}

ProcessDescriptor TaskWidget::getSelectedProcessDescriptor()
{
    QModelIndexList select_0 = view->selectionModel()->selectedRows(0);
    QModelIndexList select_1 = view->selectionModel()->selectedRows(1);
    QModelIndexList select_2 = view->selectionModel()->selectedRows(2);

    unsigned int pid;
    std::string p_name;
    std::string p_uname;

    QModelIndex index;
    for(int i=0; i< select_0.count(); i++)
    {
        index = select_0.at(i);
        pid = index.data().toInt();
        index = select_1.at(i);
        p_uname = index.data().toString().toStdString();
        index = select_2.at(i);
        p_name = index.data().toString().toStdString();

        return ProcessDescriptor(pid, p_name, p_uname);
    }

    return ProcessDescriptor();
}

void TaskWidget::selectBtnHandler()
{
    QModelIndexList select = view->selectionModel()->selectedRows();
    for(int i=0; i< select.count(); i++)
    {
        QModelIndex index = select.at(i);
        selectedProcessPID = index.data().toInt();
        //std::cout << "selected: " << selectedProcessPID << std::endl;
    }
}

void TaskWidget::filterTextChanged()
{
    //std::cout << processTextField->text().toStdString() << std::endl;
    //std::cout << "header: " << processTextField->headerSection() << std::endl;
    //pModel->setFilterRegExp(QRegExp(processTextField->text(), Qt::CaseInsensitive, QRegExp::RegExp));
    pModel->clearRegExps();
    pModel->attachRegExp(processTextField->headerSection(),
                         QRegExp(processTextField->text(), Qt::CaseInsensitive, QRegExp::RegExp));
}

void TaskWidget::update()
{
    processList = QVector<ProcessDescriptor>::fromStdVector(readStrategy->readAllRunningProcesses());
    model->setProcessList(processList);
    pModel->setSourceModel(model);

    //std::cout << "update" << std::endl;
}








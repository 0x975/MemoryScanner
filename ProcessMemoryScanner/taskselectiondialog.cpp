#include "taskselectiondialog.h"

TaskSelectionDialog::TaskSelectionDialog(QWidget *parent)
    : QDialog(parent)
{
    taskWidget = new TaskWidget();
    taskWidget->setFilterVisable(true);

    btnBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(btnBox, &QDialogButtonBox::accepted, this, &TaskSelectionDialog::reciveProcess);
    connect(btnBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *dialogLayout = new QVBoxLayout;
    dialogLayout->addWidget(taskWidget);
    dialogLayout->addWidget(btnBox);

    setWindowTitle("Task Widget");
    setLayout(dialogLayout);
}

ProcessDescriptor TaskSelectionDialog::getSelectedProcess()
{
    return selectedProcess;
}

void TaskSelectionDialog::reciveProcess()
{
    selectedProcess = taskWidget->getSelectedProcessDescriptor();
    QDialog::accept();
}

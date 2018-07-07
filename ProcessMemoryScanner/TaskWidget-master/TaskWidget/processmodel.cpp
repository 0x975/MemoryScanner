#include "processmodel.h"

ProcessModel::ProcessModel(QObject *parent)
    :QAbstractTableModel(parent)
{

}

ProcessModel::ProcessModel(QVector<ProcessDescriptor> &processVector, QObject *parent)
    :QAbstractTableModel(parent)
{
    setProcessList(processVector);
}

void ProcessModel::setProcessList(QVector<ProcessDescriptor> &processList)
{
    this->processList = processList;
    resetInternalData();

    //QModelIndex topLeft = createIndex(0, 0);
    //QModelIndex bottomRight = createIndex(processList.size(), 3);
    //emit dataChanged(topLeft, bottomRight);
}

int ProcessModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return (int)processList.size();
}

int ProcessModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant ProcessModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    if(role == Qt::DisplayRole) {
        int column = index.column();
        int row = index.row();

        ProcessDescriptor pd = processList[row];
        if(column == 0)
        {
            return QString(QString::number(pd.pid()));
        }
        else if(column == 1)
        {
            return QString(QString::fromStdString(pd.user()));
        }
        else if(column == 2)
        {
            return QString(QString::fromStdString(pd.name()));
        }
    }

    return QVariant();
}

QVariant ProcessModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if(orientation == Qt::Horizontal)
    {
        if(section == 0) {
            return "PID";
        }
        else if(section == 1) {
            return "USER";
        }
        else if(section == 2) {
            return "PROCESS";
        }
        else {
            return QVariant();
        }
    }

    return QVariant();
}

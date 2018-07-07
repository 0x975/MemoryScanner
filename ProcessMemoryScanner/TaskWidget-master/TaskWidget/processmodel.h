#ifndef PROCESSMODEL_H
#define PROCESSMODEL_H

#include <QAbstractTableModel>
#include "processdescriptor.h"


class ProcessModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ProcessModel(QObject *parent);
    ProcessModel(QVector<ProcessDescriptor> &processVector, QObject *parent);
    void setProcessList(QVector<ProcessDescriptor> &processList);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

public slots:

private:
    QVector<ProcessDescriptor> processList;
};

#endif // PROCESSMODEL_H

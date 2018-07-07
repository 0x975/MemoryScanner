#ifndef PROCESSPROXYMODEL_H
#define PROCESSPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QList>

class ProcessProxyModel : public QSortFilterProxyModel
{
     Q_OBJECT

public:
    ProcessProxyModel(QObject* parent = 0);
    void setSourceModel(QAbstractItemModel *sourceModel) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

    void attachRegExp(int section, const QRegExp &regxp);
    void clearRegExps();
    QList<QString> header();

public slots:

private:
    void setFilterRegExp(const QRegExp &regExp);
    QList<QRegExp> regExpFilters;
};

#endif // PROCESSPROXYMODEL_H

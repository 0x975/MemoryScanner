#include "processproxymodel.h"

ProcessProxyModel::ProcessProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{

}

void ProcessProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    QSortFilterProxyModel::setSourceModel(sourceModel);
    for(int i = 0; i < this->sourceModel()->columnCount(); i++) {
        regExpFilters.push_back(QRegExp("", Qt::CaseInsensitive, QRegExp::RegExp));
    }
}

QVariant ProcessProxyModel::headerData(int section, Qt::Orientation orientation, int role)  const
{
    return sourceModel()->headerData(section, orientation, role);
}

 bool ProcessProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
 {
    QVariant leftData = this->sourceModel()->data(source_left);
    QVariant rightData = this->sourceModel()->data(source_right);

    if((source_left.column() == 0) && (source_right.column() == 0)) {
        return leftData.toInt() < rightData.toInt();
    }
    else {
        return leftData.toString().toLower() < rightData.toString().toLower();
    }
 }

 bool ProcessProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
 {
     QModelIndex index0 = sourceModel()->index(source_row, 0, source_parent);
     QModelIndex index1 = sourceModel()->index(source_row, 1, source_parent);
     QModelIndex index2 = sourceModel()->index(source_row, 2, source_parent);

     return (sourceModel()->data(index0).toString().contains(regExpFilters.at(0))
             && sourceModel()->data(index1).toString().contains(regExpFilters.at(1))
             && sourceModel()->data(index2).toString().contains(regExpFilters.at(2)));

     //return sourceModel()->data(index2).toString().contains(regExpFilters.at(2));
 }

 QList<QString> ProcessProxyModel::header()
 {
     QList<QString> headerList;
     for(int i = 0; i < sourceModel()->columnCount(); i++) {
         headerList.push_back(headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
     }
     return headerList;
 }

 void ProcessProxyModel::attachRegExp(int section, const QRegExp &regxp)
 {
     regExpFilters[section] = regxp;
     invalidateFilter();
 }

 void ProcessProxyModel::clearRegExps()
 {
     for(int i = 0; i < regExpFilters.size(); i++) {
         regExpFilters[i] = QRegExp("", Qt::CaseInsensitive, QRegExp::RegExp);
     }
     invalidateFilter();
 }


 void ProcessProxyModel::setFilterRegExp(const QRegExp &regExp)
 {
     Q_UNUSED(regExp);
     /*make setFilterRegExp function private,
      * because it's now unused
     */
 }

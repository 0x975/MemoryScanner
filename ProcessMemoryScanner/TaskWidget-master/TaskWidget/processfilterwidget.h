#ifndef QFILTERWIDGET_H
#define QFILTERWIDGET_H

#include <QWidgetAction>
#include <QToolButton>
#include <QLineEdit>
#include <QWidget>
#include <QAction>
#include <QImage>
#include <QIcon>
#include <QMenu>

class ProcessFilterWidget : public QLineEdit
{
    Q_OBJECT
public:
    ProcessFilterWidget(QList<QString> tableHeader, int defaultSection, QWidget *parent = 0);
    int headerSection();

private:
    int headerSectionFromAction(const QAction *action);

signals:
    void filterChanged();

private:
    QActionGroup *patternGroup;
};

#endif // QFILTERWIDGET_H

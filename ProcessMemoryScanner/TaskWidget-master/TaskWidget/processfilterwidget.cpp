#include "processfilterwidget.h"


ProcessFilterWidget::ProcessFilterWidget(QList<QString> tableHeader, int defaultSection, QWidget *parent)
    : QLineEdit(parent)
{
    setClearButtonEnabled(true);
    connect(this, &QLineEdit::textChanged, this, &ProcessFilterWidget::filterChanged);

    QMenu *menu = new QMenu(this);
    patternGroup = new QActionGroup(this);
    patternGroup->setExclusive(true);

    for(int i = 0; i < tableHeader.size(); i++) {
        QAction *patternAction = menu->addAction(tableHeader.at(i));
        patternAction->setCheckable(true);
        if(i == defaultSection) patternAction->setChecked(true);
        patternAction->setData(QVariant(i));
        patternGroup->addAction(patternAction);
    }
    connect(patternGroup, &QActionGroup::triggered, this, &ProcessFilterWidget::filterChanged);

    const QIcon icon = QIcon(QPixmap(":/images/find.png"));
    QToolButton *optionsBtn = new QToolButton();

    optionsBtn->setFocusPolicy(Qt::NoFocus);
    optionsBtn->setStyleSheet("* { border: none; }");
    optionsBtn->setIcon(icon);
    optionsBtn->setMenu(menu);
    optionsBtn->setPopupMode(QToolButton::InstantPopup);
#ifndef QT_NO_CURSOR
    optionsBtn->setCursor(Qt::ArrowCursor);
#endif

    QWidgetAction *optionsAction = new QWidgetAction(this);
    optionsAction->setDefaultWidget(optionsBtn);
    addAction(optionsAction, QLineEdit::LeadingPosition);
}

int ProcessFilterWidget::headerSectionFromAction(const QAction *action)
{
    return action->data().toInt();
}

int ProcessFilterWidget::headerSection()
{
    return headerSectionFromAction(patternGroup->checkedAction());
}

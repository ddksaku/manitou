#include "TabWidget.h"
#include <QtGui/QTabBar>

TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    setDocumentMode(true);
    setElideMode(Qt::ElideRight);
    setMovable(true);
    setTabsClosable(true);
    setTabShape(QTabWidget::Rounded);
    setTabPosition(QTabWidget::North);
    setUsesScrollButtons(true);
}

void TabWidget::showTabBar(bool show)
{
    if (show)
        tabBar()->show();
    else
        tabBar()->hide();
}

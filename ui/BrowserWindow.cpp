#include "BrowserWindow.h"
#include "ui_BrowserWindow.h"
#include "../model/history/HistoryWidget.h"
#include "../Manitou.h"
#include <QtGui/QMessageBox>

#include <QDebug>

BrowserWindow::BrowserWindow(unsigned long id, QWidget *parent) :
    QMainWindow(parent), id(id), ui(new Ui::BrowserWindow), lastTab(0)
{
    ui->setupUi(this);
    tabWidget = new TabWidget(this);
    tabWidget->showTabBar(false);
    ui->centralWidget->layout()->addWidget(tabWidget);

    HistoryWidget *historyWidget = new HistoryWidget(this);
    ui->toolBar->addWidget(historyWidget);

    connect(tabWidget, SIGNAL(currentChanged(int)), SLOT(onCurrentTabChanged(int)));

//    progressBar = new QProgressBar(this);
//    progressBar->setMaximumWidth(QApplication::desktop()->screenGeometry().width() / 7);
//    progressBar->setMaximumHeight(12);
//    progressBar->setMinimum(0);
//    progressBar->setMaximum(100);
//    progressBar->setEnabled(false);
//    progressBar->setShown(false);
//    statusBar()->addPermanentWidget(progressBar, 0);

//    connect(ui->actionInspector, SIGNAL(triggered()), SLOT(showInspector()));
//
//    connect(ui->actionLinks, SIGNAL(triggered()), SLOT(highlightLinks()));
//    connect(ui->actionParagraphs, SIGNAL(triggered()), SLOT(highlightParagraphs()));
//
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    initializeActions();
}

void BrowserWindow::initializeActions()
{
    ui->menuFile->insertAction(ui->actionLocation, Manitou::instance()->getAction(Manitou::ActionNewWindow));
    ui->menuFile->insertAction(ui->actionLocation, Manitou::instance()->getAction(Manitou::ActionNewTab));
    ui->menuFile->addSeparator();
    ui->menuFile->addAction(Manitou::instance()->getAction(Manitou::ActionCloseWindow));
    ui->menuFile->addAction(Manitou::instance()->getAction(Manitou::ActionCloseTab));
}

BrowserWindow::~BrowserWindow()
{
    delete ui;
}

QTabWidget* BrowserWindow::getTabWidget()
{
    return tabWidget;
}

QStatusBar* BrowserWindow::getStatusBar()
{
    return ui->statusBar;
}

void BrowserWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void BrowserWindow::closeEvent(QCloseEvent *e)
{
    if (tabsMap.size() > 1) {
        QMessageBox messageBox(QMessageBox::Question, windowTitle(), tr("Are you sure you want to close this windows."), QMessageBox::Cancel | QMessageBox::Close, this);
        messageBox.setInformativeText(QString::number(tabsMap.size()) + tr(" tabs are open in this window. Do you want to close the window anyway?"));
        messageBox.setDefaultButton(QMessageBox::Close);
        messageBox.setWindowModality(Qt::WindowModal);
        switch(messageBox.exec()) {
            case QMessageBox::Cancel:
                e->ignore();
                return;
        }
    }

    QMainWindow::closeEvent(e);
    emit windowClosed(id);
}

void BrowserWindow::addTab(BrowserTab *tab)
{
    tabsMap.insert(tab->getId(), tab);
    tabWidget->addTab(tab, QString::number(tab->getId()));
    tab->setParentWindow(this);
    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(onTabCloseRequest(int)));

    if (tabsMap.size() > 1)
        tabWidget->showTabBar(true);
}

void BrowserWindow::setCurrentTab(BrowserTab *tab)
{
    QList<unsigned long> list = tabsMap.keys(tab);
    if (!list.empty()) {
        tabWidget->setCurrentWidget(tab);

    }
}

BrowserTab* BrowserWindow::currentTab()
{
    return (BrowserTab*) tabWidget->currentWidget();
}

void BrowserWindow::onCurrentTabChanged(int index)
{
    Q_UNUSED(index);

    if (lastTab) {
        disconnect(ui->actionLocation, SIGNAL(triggered()), lastTab, SLOT(openLocation()));
        disconnect(ui->actionSearch, SIGNAL(triggered()), lastTab, SLOT(search()));
        disconnect(ui->actionReload, SIGNAL(triggered()), lastTab, SLOT(reload()));
        disconnect(ui->actionStop, SIGNAL(triggered()), lastTab, SLOT(stop()));
        disconnect(ui->actionToolbar, SIGNAL(triggered()), lastTab, SLOT(toolbar()));
        disconnect(ui->actionSource, SIGNAL(triggered()), lastTab, SLOT(viewSource()));
    }

    BrowserTab *tab = (BrowserTab*) tabWidget->currentWidget();
    connect(ui->actionLocation, SIGNAL(triggered()), tab, SLOT(openLocation()));
    connect(ui->actionSearch, SIGNAL(triggered()), tab, SLOT(search()));
    connect(ui->actionReload, SIGNAL(triggered()), tab, SLOT(reload()));
    connect(ui->actionStop, SIGNAL(triggered()), tab, SLOT(stop()));
    connect(ui->actionToolbar, SIGNAL(triggered()), tab, SLOT(toolbar()));
    connect(ui->actionSource, SIGNAL(triggered()), tab, SLOT(viewSource()));

    lastTab = tab;
}

void BrowserWindow::closeCurrentTab()
{
    onTabCloseRequest(tabWidget->currentIndex());
}

void BrowserWindow::onTabCloseRequest(int index)
{
    if (tabWidget->count() > 1) {
        BrowserTab *tab = (BrowserTab*) tabWidget->widget(index);
        tabsMap.remove(tab->getId());
        tab->close();

        if (lastTab == tab)
            lastTab = 0;

        if (tabsMap.size() <= 1)
            tabWidget->showTabBar(false);
    }
}

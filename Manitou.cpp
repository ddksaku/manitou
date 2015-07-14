#include "Manitou.h"
#include "ui/BrowserWindow.h"
#include "ui/BrowserTab.h"
#include <QtCore/QDir>
#include <QtCore/QSettings>
#include <QtCore/QTimer>
#include <QtGui/QAction>
#include <QtGui/QDesktopServices>
#include <QtWebKit/QWebSettings>


#ifdef Q_WS_MAC
    void qt_mac_set_dock_menu(QMenu *menu);
#endif

Manitou::Manitou(int &argc, char **argv)
    : QApplication(argc, argv), windowsSequence(1), tabsSequence(1), dockMenu(0)
{
    initialize();

#ifdef Q_WS_MAC
    setQuitOnLastWindowClosed(false);
#endif

    connect(this, SIGNAL(aboutToQuit()), SLOT(destroy()));

    QTimer::singleShot(0, this, SLOT(postInitialize()));
}

Manitou::~Manitou()
{
    if (dockMenu)
        delete dockMenu;
}

void Manitou::initialize()
{
    QCoreApplication::setApplicationName("Manitou");
    QCoreApplication::setApplicationVersion("0.1.0");
    QCoreApplication::setOrganizationName("Internet3D");
    QCoreApplication::setOrganizationDomain("internet3d.rdc.cz");

    // init database
    database.initialize();
    history = new History(this);
    searchHistory = new SearchHistory(this);

    // actions initialization
    createActions();

    // initialize Web icon ("favicon") cache database
    QString directory = QDesktopServices::storageLocation(QDesktopServices::CacheLocation);
    QDir dir;
    if (!directory.isEmpty()) {
        if (!dir.exists(directory)) {
            if (!dir.mkpath(directory)) {
                directory = "";
            }
        }
    }
    else {
        directory = dir.homePath() + "/." + QCoreApplication::applicationName();
        if (!dir.exists(directory)) {
            if (!dir.mkpath(directory)) {
                directory = "";
            }
        }
    }

    if (!directory.isEmpty()) {
        QWebSettings::setIconDatabasePath(directory);
    }

#ifdef Linux
    wiiRemote = new WiiRemote();
#endif

}

void Manitou::createActions()
{
    QAction *action = new QAction(tr("New Window"), this);
    action->setShortcut(QKeySequence::New);
    actionsMap.insert(Manitou::ActionNewWindow, action);
    connect(action, SIGNAL(triggered()), SLOT(onOpenWindow()));

    action = new QAction(tr("New Tab"), this);
    action->setShortcut(QKeySequence::AddTab/*(Qt::CTRL + Qt::Key_T)*/);
    actionsMap.insert(Manitou::ActionNewTab, action);
    connect(action, SIGNAL(triggered()), SLOT(onOpenTab()));

    action = new QAction(tr("Close Window"), this);
    action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));
    actionsMap.insert(Manitou::ActionCloseWindow, action);
    connect(action, SIGNAL(triggered()), SLOT(closeWindow()));

    action = new QAction(tr("Close Tab"), this);
    actionsMap.insert(Manitou::ActionCloseTab, action);
    connect(action, SIGNAL(triggered()), SLOT(closeTab()));

#ifdef Q_WS_MAC
    // initialize dock menu (specific for Mac OS X)
    dockMenu = new QMenu();
    dockMenu->addAction(getAction(Manitou::ActionNewWindow));
    qt_mac_set_dock_menu(dockMenu);
#endif
}

void Manitou::postInitialize()
{
    // load WebKit settings
    QSettings settings;
    QWebSettings *globalSettings = QWebSettings::globalSettings();
    settings.beginGroup("WebKit");
        globalSettings->setAttribute(QWebSettings::AutoLoadImages, settings.value("AutoLoadImages", true).toBool());
        globalSettings->setAttribute(QWebSettings::DeveloperExtrasEnabled, settings.value("DevelopersExtras", true).toBool());
        globalSettings->setAttribute(QWebSettings::PluginsEnabled, settings.value("Plugins", true).toBool());
        globalSettings->setAttribute(QWebSettings::LocalStorageEnabled, settings.value("LocalStorage", true).toBool());
        globalSettings->setAttribute(QWebSettings::LocalStorageDatabaseEnabled, settings.value("LocalDatabase", true).toBool());
    settings.endGroup();
}

void Manitou::destroy()
{
    QSettings settings;
    QWebSettings *globalSettings = QWebSettings::globalSettings();
    settings.beginGroup("WebKit");
        settings.setValue("AutoLoadImages", globalSettings->testAttribute(QWebSettings::AutoLoadImages));
        settings.setValue("DevelopersExtras", globalSettings->testAttribute(QWebSettings::DeveloperExtrasEnabled));
        settings.setValue("Plugins", globalSettings->testAttribute(QWebSettings::PluginsEnabled));
        settings.setValue("LocalStorage", globalSettings->testAttribute(QWebSettings::LocalStorageEnabled));
        settings.setValue("LocalDatabase", globalSettings->testAttribute(QWebSettings::LocalStorageDatabaseEnabled));
    settings.endGroup();

    delete searchHistory;
    database.destroy();
    
    delete wiiRemote;
}

bool Manitou::event(QEvent *event)
{
#ifdef Q_WS_MAC
    // TODO: nejspise se bude resit pomoci odchytavani eventu primo od Cocoa frameworku...
    // ostatnich platforem se to netyka.
//    if (event->type() == QEvent::ApplicationActivate) {
//        if (windowsMap.empty()) {
//            BrowserWindow *window = createNewWindow();
//            window->showMaximized();
//        }
//    }
#endif

    return QApplication::event(event);
}

BrowserWindow* Manitou::createNewWindow(const QUrl &url)
{
    BrowserWindow *window = new BrowserWindow(windowsSequence);
    windowsMap.insert(windowsSequence++, window);
    connect(window, SIGNAL(windowClosed(unsigned long)), SLOT(onWindowClosed(unsigned long)));

    BrowserTab *tab = createNewTab(url);
    window->addTab(tab);

    BrowserWindow *activeWindow = (BrowserWindow*) Manitou::activeWindow();
    if (activeWindow) {
        window->setWindowState(activeWindow->windowState());
    }

    return window;
}

BrowserTab* Manitou::createNewTab(const QUrl &url)
{
    BrowserTab *tab = new BrowserTab(tabsSequence);
    tabsMap.insert(tabsSequence++, tab);

    connect(tab, SIGNAL(tabClosed(unsigned long)), SLOT(onTabClosed(unsigned long)));
    if (!url.isEmpty()) {
        tab->openUrl(url);
    }
    else {
        tab->openUrl(QUrl("qrc:/html/index.html", QUrl::TolerantMode));
    }

    return tab;
}

void Manitou::onOpenWindow()
{
    BrowserWindow *window = createNewWindow();
    window->show();
}

void Manitou::onOpenTab()
{
    BrowserTab *tab = createNewTab();
    BrowserWindow *window = (BrowserWindow*) activeWindow();
    window->addTab(tab);
    window->setCurrentTab(tab);
}

void Manitou::onWindowClosed(unsigned long id)
{
    BrowserWindow *window = windowsMap.value(id, 0);
    if (window) {
        windowsMap.remove(id);
        window->deleteLater();
    }
}

void Manitou::onTabClosed(unsigned long id)
{
    BrowserTab *tab = tabsMap.value(id, 0);
    if (tab) {
        tabsMap.remove(id);
        tab->deleteLater();
    }
}

void Manitou::closeWindow()
{
    BrowserWindow *window = (BrowserWindow*) Manitou::activeWindow();
    if (window)
        window->close();
}

void Manitou::closeTab()
{
    BrowserWindow *window = (BrowserWindow*) Manitou::activeWindow();
    if (window)
        window->closeCurrentTab();
}

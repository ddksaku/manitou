#ifndef __Manitou__
#define __Manitou__

#include <QtCore/QHash>
#include <QtCore/QUrl>
#include <QtGui/QApplication>
#include <QtGui/QMenu>
#include "model/Database.h"
#include "model/history/History.h"
#include "model/search/SearchHistory.h"

#include "WiiRemote.h"

// forward declarations
class BrowserWindow;
class BrowserTab;
class QAction;


/**
 * Manitou's application object.
 */
class Manitou : public QApplication {

        Q_OBJECT

    public:
        /** Application actions enumeration. */
        enum ApplicationAction {
            ActionNewWindow,
            ActionNewTab,
            ActionCloseWindow,
            ActionCloseTab
        };

    private:
        Database database;
        History *history;
        SearchHistory *searchHistory;

        QHash<unsigned int, BrowserWindow*> windowsMap;
        QHash<unsigned int, BrowserTab*> tabsMap;
        unsigned long windowsSequence;
        unsigned long tabsSequence;

        QHash<ApplicationAction, QAction*> actionsMap;

        QMenu *dockMenu; /**< The menu for Dock icon on Mac OS X. */

        WiiRemote *wiiRemote;

    public:
        /** Constructor. */
        Manitou(int &argc, char **argv);

        /** Destructor. */
        ~Manitou();

        /** Returns the only instance of Manitou application object. */
        static Manitou* instance() { return static_cast<Manitou*>(QCoreApplication::instance()); }

        History* getHistory() { return history; }
        SearchHistory* getSearchHistory() { return searchHistory; }

        /** Event handler. */
        bool event(QEvent *event);

        /** Creates new browser window. */
        BrowserWindow* createNewWindow(const QUrl &url = QUrl());

        /** Creates new browser tab. */
        BrowserTab* createNewTab(const QUrl &url = QUrl());

        /** Returns one of common application's action. */
        QAction *getAction(const ApplicationAction action) { return actionsMap.value(action); }

        WiiRemote *getWiiRemote() { return wiiRemote; }

    signals:

    public slots:
        void onWindowClosed(unsigned long id);

        void onTabClosed(unsigned long id);

    protected:
        /** Initializes application. */
        void initialize();

        /** Creates application's common actions. */
        void createActions();

    protected slots:
        /** Initializes parts, which could be initialized after the main window has shown. */
        void postInitialize();

        /** Destroys application. */
        void destroy();

        void onOpenWindow();

        void onOpenTab();

        void closeWindow();

        void closeTab();

};

#endif /* __Manitou__ */

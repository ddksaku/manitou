#ifndef __BrowserWindow__
#define __BrowserWindow__

#include <QtCore/QHash>
#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include "BrowserTab.h"
#include "TabWidget.h"


namespace Ui {
    class BrowserWindow;
}


class BrowserWindow : public QMainWindow {

        Q_OBJECT

    private:
        unsigned long id;
        Ui::BrowserWindow *ui;

        QProgressBar *progressBar;

        TabWidget *tabWidget;
        QHash<unsigned long, BrowserTab*> tabsMap;
        BrowserTab *lastTab;

    public:
        BrowserWindow(unsigned long id, QWidget *parent = 0);
        ~BrowserWindow();

        unsigned long getId() const { return id; }

        void addTab(BrowserTab *tab);

        void setCurrentTab(BrowserTab *tab);

        BrowserTab* currentTab();

        QTabWidget* getTabWidget();
        QStatusBar* getStatusBar();

    signals:
        void windowClosed(unsigned long id);

    public slots:
        void closeCurrentTab();

    protected:
        void initializeActions();
        void changeEvent(QEvent *e);
        void closeEvent(QCloseEvent *e);

    private slots:
        void onCurrentTabChanged(int index);
        void onTabCloseRequest(int index);

};

#endif /* __BrowserWindow__ */

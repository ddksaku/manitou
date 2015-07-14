#ifndef __BrowserTab__
#define __BrowserTab__

#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include "GraphicsView.h"
#include "GraphicsWebView.h"
#include "NavigationToolBar.h"

// forward declarations
class BrowserWindow;


class BrowserTab : public QWidget {

        Q_OBJECT

    private:
        unsigned int id;

        NavigationToolBar *navigationToolBar;
        QGraphicsView *graphicsView;
        QGraphicsScene *graphicsScene;
        GraphicsWebView *webView;

        BrowserWindow *parentWindow;

    public:
        explicit BrowserTab(unsigned int id, QWidget *parent = 0);
        virtual ~BrowserTab();

        unsigned int getId() const { return id; }

        QGraphicsWebView* getWebView() { return webView; }

        void setParentWindow(BrowserWindow *parentWindow);

    signals:
        void tabClosed(unsigned long id);

    public slots:
        void openUrl(const QUrl &url);
        void close();

    private slots:
        void onTitleChanged(QString title);

        void onLoadStarted();
        void onLoadProgress(int progress);
        void onLoadFinished();

        void showInspector();
        void toolbar();

        void openLocation();
        void search();

        void reload();
        void stop();

        void viewSource();
        void highlightLinks();
        void highlightParagraphs();

    protected:
        void resizeEvent(QResizeEvent *e);

};

#endif /* __BrowserTab__ */

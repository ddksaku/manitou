#ifndef __NavigationToolBar__
#define __NavigationToolBar__

#include <QtGui/QToolBar>
#include <QtWebKit/QGraphicsWebView>
#include "AddressBar.h"
#include "SearchBar.h"


class NavigationToolBar : public QToolBar {

        Q_OBJECT

    private:
        AddressBar *addressBar;
        SearchBar *searchBar;
        QGraphicsWebView *webView;

    public:
        NavigationToolBar(QGraphicsWebView *webView, QWidget *parent = 0);

    public slots:
        void location();
        void search();

        void onUrlChanged(const QUrl &url);
        void onIconChanged();
        void onAddressChanged();
        void onOpenUrl(const QUrl &url);

};

#endif /* __NavigationToolBar__ */

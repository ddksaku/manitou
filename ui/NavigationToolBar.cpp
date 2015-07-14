#include "NavigationToolBar.h"
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QLayout>


NavigationToolBar::NavigationToolBar(QGraphicsWebView *webView, QWidget *parent) :
    QToolBar(parent), webView(webView)
{
    setIconSize(QSize(24, 24));
    layout()->setSpacing(0);
    layout()->setContentsMargins(0,0,0,0);

#ifdef Q_WS_MAC
    setStyleSheet("QToolBar { background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,"
                      "stop:0 rgba(217, 217, 217, 255), stop:0.45 rgba(177, 177, 177, 255),"
                      "stop:0.46 rgba(140, 140, 140, 255), stop:1 rgba(125, 125, 125, 255));"
                  "}"
                  "QToolBar:active { background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,"
                      "stop:0 rgba(168, 168, 168, 255), stop:0.45 rgba(130, 130, 130, 255),"
                      "stop:0.46 rgba(113, 113, 113, 255), stop:1 rgba(95, 95, 95, 255));"
                  "}");
#endif Q_WS_MAC

    QAction *action = webView->pageAction(QWebPage::Back);
    action->setIcon(QIcon(":/icons/previous.png"));
    this->addAction(action);

    action = webView->pageAction(QWebPage::Forward);
    action->setIcon(QIcon(":/icons/next.png"));
    this->addAction(action);

    action = webView->pageAction(QWebPage::Reload);
    action->setIcon(QIcon(":/icons/refresh.png"));
    this->addAction(action);

    action = webView->pageAction(QWebPage::Stop);
    action->setIcon(QIcon(":/icons/stop.png"));
    this->addAction(action);

    addressBar = new AddressBar(this);
    addressBar->setWebIcon(webView->icon());
    this->addWidget(addressBar);

    searchBar = new SearchBar(this);
    searchBar->setMaximumWidth(QApplication::desktop()->screenGeometry().width() / 3);
    this->addWidget(searchBar);


    connect(webView, SIGNAL(urlChanged(QUrl)), SLOT(onUrlChanged(QUrl)));
    connect(webView, SIGNAL(iconChanged()), SLOT(onIconChanged()));
    connect(addressBar, SIGNAL(returnPressed()), SLOT(onAddressChanged()));
    connect(searchBar, SIGNAL(openUrl(QUrl)), SLOT(onOpenUrl(QUrl)));
}

void NavigationToolBar::location()
{
    addressBar->setFocus(Qt::ShortcutFocusReason);
    addressBar->selectAll();
}

void NavigationToolBar::search()
{
    searchBar->setFocus(Qt::TabFocusReason);
}

void NavigationToolBar::onUrlChanged(const QUrl &url)
{
    addressBar->setText(url.toString());
    addressBar->setCursorPosition(0);
}

void NavigationToolBar::onIconChanged()
{
    QIcon icon = webView->icon();
    if (!icon.isNull()) {
        addressBar->setWebIcon(icon);
    }
    else {
        addressBar->setWebIcon(QWebSettings::webGraphic(QWebSettings::DefaultFrameIconGraphic));
    }
}

void NavigationToolBar::onAddressChanged()
{
    QUrl url = QUrl::fromUserInput(addressBar->text());
    if (url.isValid())
        webView->load(url);
}

void NavigationToolBar::onOpenUrl(const QUrl &url)
{
    if (url.isValid())
        webView->load(url);
}

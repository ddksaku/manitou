#ifndef __WebPage__
#define __WebPage__

#include <QtWebKit/QWebPage>

class WebPage : public QWebPage {

        Q_OBJECT

    public:
        explicit WebPage(QObject *parent = 0);

        QList<QString> getLinks();

    signals:

    public slots:

    private:
        QWebPage* createWindow(WebWindowType type);

    private slots:
        void addJavaScriptObject();

        void onWiimoteButtonDown();
        void onWiimoteButtonUp();
        void onWiimoteAcceleration();
};

#endif /* __WebPage__ */

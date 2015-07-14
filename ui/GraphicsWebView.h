#ifndef __GraphicsWebView__
#define __GraphicsWebView__

#include <QtWebKit/QGraphicsWebView>
#include <QtWebKit/QWebHitTestResult>

class GraphicsWebView : public QGraphicsWebView {

        Q_OBJECT

    private:
        QWebHitTestResult lastHitTestResult;
        bool scrolling;
        bool scrolled;
        QPoint delta;

    public:
        explicit GraphicsWebView(QGraphicsItem *parent = 0);

        QWebHitTestResult getLastHitTestResult() { return lastHitTestResult; }

    private:
        void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
//        void mousePressEvent(QGraphicsSceneMouseEvent *event);
//        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    signals:

    public slots:

};

#endif /* __GraphicsWebView__ */

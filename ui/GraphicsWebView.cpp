#include "GraphicsWebView.h"
#include "WebPage.h"
#include <QtGui/QGraphicsSceneContextMenuEvent>

GraphicsWebView::GraphicsWebView(QGraphicsItem *parent) :
    QGraphicsWebView(parent), scrolling(false), scrolled(false)
{
    setPage(new WebPage(this));
}

void GraphicsWebView::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    lastHitTestResult = page()->mainFrame()->hitTestContent(event->pos().toPoint());
    //lastHitTestResult.frame()
    QGraphicsWebView::contextMenuEvent(event);
}

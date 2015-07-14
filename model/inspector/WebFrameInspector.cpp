#include "WebFrameInspector.h"
#include <QtWebKit/QWebElement>
#include <QtWebKit/QWebElementCollection>


WebFrameInspector::WebFrameInspector(QObject *parent) :
    QObject(parent), webFrame(0)
{
}

QList<QString> WebFrameInspector::getContents()
{
    return QList<QString>();
}

QList<QString> WebFrameInspector::getImages()
{
    QList<QString> images;

    QWebElementCollection collection = webFrame->findAllElements("img");
    foreach (QWebElement element, collection) {
        images.append(element.attribute("alt") + " - " + element.attribute("src"));
    }
    return images;
}

QList<QString> WebFrameInspector::getLinks()
{
    QList<QString> links;

    QWebElementCollection collection = webFrame->findAllElements("a");
    foreach (QWebElement element, collection) {
        links.append(element.toPlainText() + " - " + element.attribute("href"));
    }
    return links;
}

QList<QString> WebFrameInspector::getParagraphs()
{
    return QList<QString>();
}

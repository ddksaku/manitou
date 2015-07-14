#include "WebPage.h"
#include "BrowserWindow.h"
#include "../JavaScriptObject.h"
#include "../AudioPlayer.h"
#include "../capture/Capture.h"
#include "../WiiRemote.h"
#include "../Manitou.h"

#include <QWebElement>

WebPage::WebPage(QObject *parent) :
    QWebPage(parent)
{
    connect(this->currentFrame(), SIGNAL(javaScriptWindowObjectCleared()), SLOT(addJavaScriptObject()));
}

QWebPage* WebPage::createWindow(WebWindowType type) {
    Q_UNUSED(type)

    BrowserWindow *window = Manitou::instance()->createNewWindow();
    window->show();
    return window->currentTab()->getWebView()->page();
}

void WebPage::addJavaScriptObject()
{
    JavaScriptObject *jsObject = new JavaScriptObject(this);
    this->mainFrame()->addToJavaScriptWindowObject("jsObject", jsObject);

    // AudioPlayer *audioPlayer = new AudioPlayer(this);
    // this->mainFrame()->addToJavaScriptWindowObject("audioPlayer",audioPlayer);

    Capture *capture = new Capture(this);
    this->mainFrame()->addToJavaScriptWindowObject("capture",capture);

#ifdef Linux
    WiiRemote *wiiRemote = Manitou::instance()->getWiiRemote();
    this->mainFrame()->addToJavaScriptWindowObject("wiiRemote",wiiRemote);
    connect(wiiRemote, SIGNAL(buttonDown()), SLOT(onWiimoteButtonDown()));
    connect(wiiRemote, SIGNAL(buttonUp()), SLOT(onWiimoteButtonUp()));
    connect(wiiRemote, SIGNAL(acceleration()), SLOT(onWiimoteAcceleration()));
#endif

}

void WebPage::onWiimoteButtonDown()
{
    QString javascript =
        this->mainFrame()->findFirstElement("body").attribute("onWiimoteButtonDown");
    this->mainFrame()->evaluateJavaScript(javascript);
}

void WebPage::onWiimoteButtonUp()
{
    QString javascript =
        this->mainFrame()->findFirstElement("body").attribute("onWiimoteButtonUp");
    this->mainFrame()->evaluateJavaScript(javascript);
}

void WebPage::onWiimoteAcceleration()
{
    QString javascript =
        this->mainFrame()->findFirstElement("body").attribute("onWiimoteAcceleration");
    this->mainFrame()->evaluateJavaScript(javascript);
}

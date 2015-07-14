#ifndef __model_inspector_WebFrameInspector__
#define __model_inspector_WebFrameInspector__

#include <QtCore/QObject>
#include <QtWebKit/QWebFrame>

class WebFrameInspector : public QObject {

        Q_OBJECT

    private:
        QWebFrame *webFrame;

    public:
        explicit WebFrameInspector(QObject *parent = 0);

        void setWebFrame(QWebFrame *webFrame) { this->webFrame = webFrame; }

        QList<QString> getContents();
        QList<QString> getImages();
        QList<QString> getLinks();
        QList<QString> getParagraphs();
};

#endif /* __model_inspector_WebFrameInspector__ */

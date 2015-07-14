#ifndef __JavaScriptObject__
#define __JavaScriptObject__

#include <QObject>

class JavaScriptObject : public QObject {

        Q_OBJECT

    public:
        explicit JavaScriptObject(QObject *parent = 0);

    signals:

    public slots:
        QString toUpper(const QString &string) { return string.toUpper(); }
        int sqr(int x) { return x * x; }

};

#endif /* __JavaScriptObject__ */

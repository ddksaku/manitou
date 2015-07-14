#ifndef __AddressBar__
#define __AddressBar__

#include <QtGui/QAction>
#include <QtGui/QCompleter>
#include <QtGui/QIcon>
#include <QtGui/QLineEdit>


class AddressBar : public QLineEdit {

        Q_OBJECT

    private:
        QIcon webIcon;
        int iconSize;
        QCompleter *completer;

    public:
        explicit AddressBar(QWidget *parent = 0);

        QIcon getWebIcon() const { return webIcon; }

        void setWebIcon(QIcon webIcon) { this->webIcon = webIcon; }

    signals:

    public slots:

    protected:
        void paintEvent(QPaintEvent *event);
        void resizeEvent(QResizeEvent *event);

        void resize(const QSize &size);

};

#endif /* __AddressBar__ */

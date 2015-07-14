#ifndef __ui_TabWidget__
#define __ui_TabWidget__

#include <QtGui/QTabWidget>

class TabWidget : public QTabWidget {

        Q_OBJECT

    public:
        explicit TabWidget(QWidget *parent = 0);

    signals:

    public slots:
        void showTabBar(bool show);

};

#endif /* __ui_TabWidget__ */

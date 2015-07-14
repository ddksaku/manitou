#ifndef __ui_IconLineEdit__
#define __ui_IconLineEdit__

#include <QtGui/QLineEdit>
#include <QtGui/QToolButton>

class IconLineEdit : public QWidget {

        Q_OBJECT

    private:
        QToolButton *button;
        QLineEdit *lineEdit;

    public:
        explicit IconLineEdit(QWidget *parent = 0);

        QLineEdit* getLineEdit() const { return lineEdit; }

        QToolButton* getButton() const { return button; }

};

#endif /* __ui_IconLineEdit__ */

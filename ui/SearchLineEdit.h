#ifndef __SearchLineEdit__
#define __SearchLineEdit__

#include <QtGui/QLineEdit>

/**
 * Search line edit.
 */
class SearchLineEdit : public QLineEdit {

        Q_OBJECT

    private:
        enum State {
            StateEmpty,
            StateEdited
        };

        State state;
        QString engineName;

    public:
        explicit SearchLineEdit(const QString &engineName, QWidget *parent = 0);

        void setEngineName(const QString &engineName) { this->engineName = engineName; }

    signals:
        void clearHistory();

    private slots:
        void onClearHistory();

    protected:
        void contextMenuEvent(QContextMenuEvent *event);
        void focusInEvent(QFocusEvent *event);
        void focusOutEvent(QFocusEvent *event);


};

#endif /* __SearchLineEdit__ */

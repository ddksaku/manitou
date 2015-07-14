#ifndef __SearchBar__
#define __SearchBar__

#include <QtGui/QWidget>
#include <QtCore/QUrl>
#include "SearchLineEdit.h"

/**
 * Search bar.
 */
class SearchBar : public QWidget {

        Q_OBJECT

    private:
        SearchLineEdit *searchEdit; /**< Line edit for editing search query. */
        QCompleter *completer; /**< Search line edit completer. */

    public:
        /** Constructor. */
        explicit SearchBar(QWidget *parent = 0);
        ~SearchBar();

    signals:
        /** This signal is emmited when the search query has been confirmed by user. */
        void openUrl(const QUrl &url);

    private slots:
        void onSearchReturnPressed();
        void onClearHistory();

    protected:
        void focusInEvent(QFocusEvent *event);


};

#endif /* __SearchBar__ */

#include "SearchLineEdit.h"
#include <QtGui/QContextMenuEvent>
#include <QtGui/QMenu>

SearchLineEdit::SearchLineEdit(const QString &engineName, QWidget *parent) :
    QLineEdit(parent), state(StateEmpty), engineName(engineName)
{
    this->setStyleSheet("color:gray;");

    this->setText(engineName);
}

void SearchLineEdit::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = createStandardContextMenu();

    menu->addSeparator();
    QAction *action = menu->addAction(tr("Clear Search History"));
    connect(action, SIGNAL(triggered()), this, SLOT(onClearHistory()));

    menu->exec(event->globalPos());
    delete menu;
}

void SearchLineEdit::focusInEvent(QFocusEvent *inEvent)
{
    if (state == StateEmpty) {
        state = StateEdited;
        setText("");
        this->setStyleSheet("color:black;");
    }

    QLineEdit::focusInEvent(inEvent);
}

void SearchLineEdit::focusOutEvent(QFocusEvent *outEvent)
{
    if (text().isEmpty()) {
        state = StateEmpty;
        setText(engineName);
        this->setStyleSheet("color:gray;");
    }

    QLineEdit::focusOutEvent(outEvent);
}

void SearchLineEdit::onClearHistory()
{
    emit clearHistory();
}

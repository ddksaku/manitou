#include "SearchBar.h"

#include <QtCore/QDateTime>
#include <QtCore/QModelIndexList>
#include <QtGui/QCompleter>
#include <QtGui/QHBoxLayout>
#include <QtGui/QFocusEvent>
#include "../Manitou.h"

#include <QtDebug>

SearchBar::SearchBar(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    setLayout(layout);

    SearchHistory *searchHistory = Manitou::instance()->getSearchHistory();
    completer = new QCompleter(searchHistory->getItemModel(), this);
    completer->setCompletionColumn(1);
    completer->setCaseSensitivity(Qt::CaseInsensitive);

    searchEdit = new SearchLineEdit("Google", this);
    //TODO: in Qt 4.7
    //searchEdit->setPlaceholderText("Google");
    searchEdit->setCompleter(completer);

    layout->addWidget(searchEdit);

    connect(searchEdit, SIGNAL(returnPressed()), SLOT(onSearchReturnPressed()));
    connect(searchEdit, SIGNAL(clearHistory()), SLOT(onClearHistory()));
}

SearchBar::~SearchBar()
{
    delete completer;
}

void SearchBar::onSearchReturnPressed()
{
    if (!searchEdit->text().isEmpty()) {
        QString trimmed = searchEdit->text().trimmed();
        QString query = trimmed;
        query.replace(QRegExp("[\\s]+"), "+");
        QUrl url("http://www.google.com/search?client=webkit&q=" + query);
        if (url.isValid())
            emit openUrl(url);

        QAbstractItemModel *model = completer->model();
        if (model) {
            trimmed = trimmed.toLower();
            QList<QModelIndex> list = model->match(model->index(0, 1), Qt::EditRole, trimmed, 1, Qt::MatchFlags(Qt::MatchFixedString | Qt::MatchWrap));
            if (list.isEmpty()) {
                model->insertRow(0);
                model->setData(model->index(0, 1), trimmed);
                model->setData(model->index(0, 2), QDateTime::currentDateTime().toUTC().toString(Qt::ISODate));
                model->submit();
            }
        }

        searchEdit->setCursorPosition(0);
    }
}

void SearchBar::onClearHistory()
{
    QAbstractItemModel *model = completer->model();
    if (model) {
        model->removeRows(0, model->rowCount());
        model->submit();
    }
}


void SearchBar::focusInEvent(QFocusEvent *event)
{
    searchEdit->setFocus(event->reason());
}

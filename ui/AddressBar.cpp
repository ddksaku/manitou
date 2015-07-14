#include "AddressBar.h"
#include "../Manitou.h"
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

AddressBar::AddressBar(QWidget *parent) :
    QLineEdit(parent)
{
    resize(size());
    setBackgroundRole(QPalette::NoRole);

    History *history = Manitou::instance()->getHistory();
    completer = new QCompleter(history->getItemModel(), this);
    completer->setCompletionColumn(1);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
}

void AddressBar::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!webIcon.isNull()) {
        QPixmap pixmap = webIcon.pixmap(iconSize, iconSize);
        QPoint point;
        point.setX((iconSize - pixmap.size().width()) / 2);
        point.setY((geometry().height() - pixmap.size().height()) / 2);
        painter.drawPixmap(point, pixmap);
    }

    painter.end();
}

void AddressBar::resizeEvent(QResizeEvent *event)
{
    QLineEdit::resizeEvent(event);
    resize(event->size());
}

void AddressBar::resize(const QSize &size)
{
    iconSize = size.height();
    QMargins margins = textMargins();
    margins.setLeft(iconSize);
    setTextMargins(margins);
}

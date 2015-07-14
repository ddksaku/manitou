#include "IconLineEdit.h"

#include <QtGui/QHBoxLayout>

#include <QtDebug>


IconLineEdit::IconLineEdit(QWidget *parent) :
        QWidget(parent)
{
    lineEdit = new QLineEdit(this);

    button = new QToolButton(this);
    button->setPopupMode(QToolButton::InstantPopup);
    button->setToolButtonStyle(Qt::ToolButtonIconOnly);
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    button->setMaximumSize(lineEdit->size().height() - 8, lineEdit->size().height() - 8);

    //qDebug() << "lineEdit: size=" << lineEdit->size() << ", contentsRect=" << lineEdit->contentsRect() << ", frameSize=" << lineEdit->frameSize();


    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(button);
    layout->addWidget(lineEdit);
    layout->setSpacing(0);

    setLayout(layout);
}

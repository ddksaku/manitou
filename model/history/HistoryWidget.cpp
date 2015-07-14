/*
 * Copyright (c) 2010 Roman Hak
 * Contact: roman.hak@gmail.com
 *
 * This file is part of Manitou Web Browser.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "HistoryWidget.h"
#include "../../Manitou.h"
#include <QtGui/QStackedLayout>
#include <QtGui/QTableView>

HistoryWidget::HistoryWidget(QWidget *parent) :
    QWidget(parent)
{
    historyItemView = new QTableView(this);
    historyItemView->setModel(Manitou::instance()->getHistory()->getItemModel());
    QStackedLayout *layout = new QStackedLayout(this);
    layout->addWidget(historyItemView);
    this->setLayout(layout);
}

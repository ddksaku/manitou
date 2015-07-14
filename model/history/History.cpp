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

#include "History.h"

const QString History::tableName = "History";
const QString History::createTableSqlScript =
        "create table History ("
            "id integer primary key, "
            "url text, "
            "title text, "
            "date text"
        ")";

History::History(QObject *parent) :
    DatabaseModel(tableName, createTableSqlScript, parent)
{
}

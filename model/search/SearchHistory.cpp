#include "SearchHistory.h"

const QString SearchHistory::tableName = "SearchHistory";
const QString SearchHistory::createTableSqlScript =
        "create table SearchHistory ("
            "id integer primary key, "
            "sentence text, "
            "date text"
        ")";

SearchHistory::SearchHistory(QObject *parent) :
    DatabaseModel(tableName, createTableSqlScript, parent)
{
}

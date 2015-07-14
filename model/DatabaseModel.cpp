#include "DatabaseModel.h"
#include <QtCore/QStringList>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

#include <QtDebug>

DatabaseModel::DatabaseModel(const QString &tableName, const QString &createTableSqlScript, QObject *parent)  :
    QObject(parent)
{
    tableModel = new QSqlTableModel(this);

    QStringList tableList = tableModel->database().tables(QSql::Tables);
    if (!tableList.contains(tableName)) {
        createTable(createTableSqlScript);
    }

    tableModel->setTable(tableName);
    tableModel->setEditStrategy(QSqlTableModel::OnRowChange);
    tableModel->select();
}

void DatabaseModel::createTable(const QString &createTableSqlScript)
{
    QSqlQuery query;
    if (!query.exec(createTableSqlScript)) {
        qDebug() << "error: " << query.lastError().text();
    }
}

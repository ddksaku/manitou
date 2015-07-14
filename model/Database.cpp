#include "Database.h"
#include <QtCore/QStringList>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

#include <QDebug>

Database::Database(QObject *parent) :
    QObject(parent)
{
}

bool Database::initialize()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // TODO: nejakou rozumnou k souboru (asi stejnou, jako nastaveni...)
    db.setDatabaseName("/Users/roman/tmp/Manitou");
    if (!db.open()) {
        qDebug() << "Openning database failed: " << db.lastError().text();
        return false;
    }

    return true;
}

void Database::destroy()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen())
        db.close();
}

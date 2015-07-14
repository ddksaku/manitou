#ifndef __model_DatabaseModel__
#define __model_DatabaseModel__

#include "Model.h"
#include <QtCore/QObject>
#include <QtSql/QSqlTableModel>

class DatabaseModel : public QObject, public Model {

        Q_OBJECT

    private:
        QSqlTableModel *tableModel;

    public:
        explicit DatabaseModel(const QString &tableName, const QString &createTableSqlScript, QObject *parent = 0);

        QSqlTableModel* getItemModel() { return tableModel; }

    private:
        void createTable(const QString &createTableSqlScript);
};

#endif /* __model_DatabaseModel__ */

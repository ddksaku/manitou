#ifndef __model_Database__
#define __model_Database__

#include <QtCore/QObject>
#include <QtSql/QSqlDatabase>

class Database : public QObject {

        Q_OBJECT

    public:
        explicit Database(QObject *parent = 0);

        bool initialize();
        void destroy();

};

#endif /* __model_Database__ */

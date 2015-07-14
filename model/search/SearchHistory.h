#ifndef __model_search_SearchHistory__
#define __model_search_SearchHistory__

#include "../DatabaseModel.h"

class SearchHistory : public DatabaseModel {

        Q_OBJECT

    private:
        static const QString tableName;
        static const QString createTableSqlScript;

    public:
        explicit SearchHistory(QObject *parent = 0);

};

#endif /* __model_search_SearchHistory__ */

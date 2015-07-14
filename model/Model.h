#ifndef __model_Model__
#define __model_Model__

#include <QtCore/QAbstractItemModel>

class Model {

    public:
        virtual QAbstractItemModel* getItemModel() = 0;
};

#endif /* __model_Model__ */

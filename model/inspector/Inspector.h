#ifndef __model_inspector_Inspector__
#define __model_inspector_Inspector__

#include <QtCore/QList>
#include <QtCore/QString>

class Inspector {

    public:
        virtual QList<QString> getContents() = 0;
        virtual QList<QString> getImages() = 0;
        virtual QList<QString> getLinks() = 0;
        virtual QList<QString> getParagraphs() = 0;
};

#endif /* __model_inspector_Inspector__ */

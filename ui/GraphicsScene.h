#ifndef __GraphicsScene__
#define __GraphicsScene__

#include <QGraphicsScene>

class GraphicsScene : public QGraphicsScene {

        Q_OBJECT

    public:
        explicit GraphicsScene(QObject *parent = 0);

    signals:

    public slots:

};

#endif /* __GraphicsScene__ */

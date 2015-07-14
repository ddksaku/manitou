#include "GraphicsScene.h"

GraphicsScene::GraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    setBackgroundBrush(Qt::black);
}

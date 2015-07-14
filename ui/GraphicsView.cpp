#include "GraphicsView.h"

#include <QtDebug>

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    grabGesture(Qt::SwipeGesture);
    grabGesture(Qt::PanGesture);
    grabGesture(Qt::PinchGesture);
}

bool GraphicsView::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture) {
        return gestureEvent(static_cast<QGestureEvent*>(event));
    }
    else {
        return QGraphicsView::event(event);
    }
}

bool GraphicsView::gestureEvent(QGestureEvent *event)
{
    foreach (QGesture *gesture, event->gestures()) {
        qDebug() << "type: " << gesture->gestureType();
    }

    if (QGesture *pinchGesture = event->gesture(Qt::PinchGesture)) {
        triggerPinchGesture(static_cast<QPinchGesture*>(pinchGesture));
        return true;
    }

    if (QGesture *swipeGesture = event->gesture(Qt::SwipeGesture)) {
        triggerSwipeGesture(static_cast<QSwipeGesture*>(swipeGesture));
        return true;
    }

    if (QGesture *tapGesture = event->gesture(Qt::TapGesture)) {
        triggerTapGesture(static_cast<QTapGesture*>(tapGesture));
        return true;
    }

    return false;
}

void GraphicsView::triggerPinchGesture(QPinchGesture *gesture)
{
    qDebug() << "Pinch gesture";
    if (gesture->changeFlags().testFlag(QPinchGesture::ScaleFactorChanged)) {
        qDebug() << "Scale factor changed to: " << gesture->scaleFactor();
    }
}

void GraphicsView::triggerSwipeGesture(QSwipeGesture *gesture)
{
    qDebug() << "Swipe gesture";
    if (gesture->horizontalDirection() == QSwipeGesture::Left)
        qDebug() << "Horizontal: left";
    else if (gesture->horizontalDirection() == QSwipeGesture::Right)
        qDebug() << "Horizontal: right";

    if (gesture->verticalDirection() == QSwipeGesture::Up)
        qDebug() << "Horizontal: up";
    else if (gesture->verticalDirection() == QSwipeGesture::Down)
        qDebug() << "Horizontal: down";

    qDebug() << "angle: " << gesture->swipeAngle();

}

void GraphicsView::triggerTapGesture(QTapGesture *gesture)
{
    qDebug() << "Tap gesture";
    qDebug() << "position: " << gesture->position();
}

void GraphicsView::triggerTapAndHoldGesture(QTapAndHoldGesture *gesture)
{
    qDebug() << "Tap and hold gesture";
    qDebug() << "position: " << gesture->position();
}

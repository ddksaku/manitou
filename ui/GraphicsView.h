#ifndef __GraphicsView__
#define __GraphicsView__

#include <QtGui/QGesture>
#include <QtGui/QGestureEvent>
#include <QtGui/QGraphicsView>
#include <QtGui/QPinchGesture>
#include <QtGui/QSwipeGesture>
#include <QtGui/QTapAndHoldGesture>
#include <QtGui/QTapGesture>


class GraphicsView : public QGraphicsView {

        Q_OBJECT

    public:
        explicit GraphicsView(QWidget *parent = 0);

    private:
        bool event(QEvent *event);
        bool gestureEvent(QGestureEvent *event);

        void triggerPinchGesture(QPinchGesture *gesture);
        void triggerSwipeGesture(QSwipeGesture *gesture);
        void triggerTapGesture(QTapGesture *gesture);
        void triggerTapAndHoldGesture(QTapAndHoldGesture *gesture);

    signals:

    public slots:

};

#endif /* __GraphicsView__ */

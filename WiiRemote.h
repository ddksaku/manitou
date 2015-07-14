#ifndef __WiiRemote__
#define __WiiRemote__

#include <QObject>

#include <wii/WiiDiscovery.h>
#include <wii/WiiRemote.h>

/**
 * Part of JS api for the WII remote.
 * Connects to a first available wii remote and provides simplified
 * interface to it.
 */
class WiiRemote : public QObject {

        Q_OBJECT

    public:
        explicit WiiRemote(QObject *parent = 0);

        void findRemote();

    signals:
        void acceleration();
        void buttonDown();
        void buttonUp();

    public slots:
        bool isActive();

        void setVibrations(bool vibrate);
        void setLeds(int mask);

        int buttonState();
        qreal accelerationX();
        qreal accelerationY();
        qreal accelerationZ();

        void enableAccelerometer();
        void disableAccelerometer();

    private slots:
        void onDeviceDiscovered(wii::WiiDevice *device);
        void onDisconnected();
        void onButtonStateChanged(wii::WiiRemote::Button button,
            bool pressed);

    private:
        wii::WiiDiscovery *discovery;
        wii::WiiRemote *remote;
};

#endif /* __WiiRemote__ */

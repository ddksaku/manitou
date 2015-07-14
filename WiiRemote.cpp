#include "WiiRemote.h"

WiiRemote::WiiRemote(QObject *parent) :
    QObject(parent), remote(NULL)
{
    discovery = wii::WiiDiscovery::instance();

    connect(discovery, SIGNAL(deviceDiscovered(wii::WiiDevice *)),
        SLOT(onDeviceDiscovered(wii::WiiDevice *)));

    findRemote();
}

void WiiRemote::findRemote()
{
    discovery->startDiscovery();
}


void WiiRemote::onDeviceDiscovered(wii::WiiDevice *device)
{
    if (device->deviceType() != wii::WiiDevice::WiiRemote) {
        return;
    }

    if (remote) {
        return;
    }

    discovery->stopDiscovery();

    remote = static_cast<wii::WiiRemote *>(device);

    connect(remote, SIGNAL(deviceDisconnected()), SLOT(onDisconnected()));

    connect(remote, SIGNAL(buttonStateChanged(wii::WiiRemote::Button, bool)),
        SLOT(onButtonStateChanged(wii::WiiRemote::Button, bool)));
    connect(remote, SIGNAL(accelerationChanged(const QVector3D &)),
        SIGNAL(acceleration()));

    remote->connectDevice();

}

void WiiRemote::onDisconnected()
{
    disconnect(remote, 0, this, 0);
    remote = NULL;
}

void WiiRemote::onButtonStateChanged(
    wii::WiiRemote::Button button, bool pressed)
{
    Q_UNUSED(button);

    if (pressed) {
        emit buttonDown();
    } else {
        emit buttonUp();
    }
}

bool WiiRemote::isActive()
{
    return remote && remote->isConnected();
}

void WiiRemote::setVibrations(bool vibrate)
{
    if (!isActive()) {
        return;
    }

    remote->setVibrations(vibrate);
}

void WiiRemote::setLeds(int mask){
    if (!isActive()) {
        return;
    }

    wii::WiiRemote::Leds flags = wii::WiiRemote::LedNone;

    if (mask & 1) { flags |= wii::WiiRemote::Led1; }
    if (mask & 2) { flags |= wii::WiiRemote::Led2; }
    if (mask & 4) { flags |= wii::WiiRemote::Led3; }
    if (mask & 8) { flags |= wii::WiiRemote::Led4; }

    remote->setLeds(flags);
}

int WiiRemote::buttonState(){
    if (!isActive()) {
        return 0;
    }
    
    return static_cast<int>(remote->buttons());
}

qreal WiiRemote::accelerationX()
{
    if (!isActive()) {
        return 0;
    }
    
    return remote->acceleration().x();
}

qreal WiiRemote::accelerationY()
{
    if (!isActive()) {
        return 0;
    }
    
    return remote->acceleration().y();
}

qreal WiiRemote::accelerationZ()
{
    if (!isActive()) {
        return 0;
    }
    
    return remote->acceleration().z();
}

void WiiRemote::enableAccelerometer(){
    if (!isActive()) {
        return;
    }

    wii::WiiRemote::Features features = remote->features();
    features |= wii::WiiRemote::FeatureAccelerometer;

    remote->setFeatures(features);
}

void WiiRemote::disableAccelerometer(){
    if (!isActive()) {
        return;
    }

    wii::WiiRemote::Features features = remote->features();
    features &= ~wii::WiiRemote::FeatureAccelerometer;

    remote->setFeatures(features);
}


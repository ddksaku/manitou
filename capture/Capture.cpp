#include <QAudioDeviceInfo>
#include <QDebug>
#include "Capture.h"

Capture::Capture(QObject *parent)
    : QObject(parent)
{
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
    QStringList supportedCodecs = info.supportedCodecs();
    for(QStringList::iterator it = supportedCodecs.begin(); it != supportedCodecs.end(); it++)
    {
        FormatData fd;
        fd.setType(*it);
    }

    audioCapture = new AudioCapture();
    imageCapture = new ImageCapture();
}

Capture::~Capture()
{
    if(audioCapture)
        delete audioCapture;
    if(imageCapture)
        delete imageCapture;
}

void Capture::startCaptureAudio(QString filename)
{
    audioCapture->startCapture(filename);
}

void Capture::stopCaptureAudio()
{
    audioCapture->stopCapture();
}

void Capture::captureImage()
{
    imageCapture->captureImage();
}

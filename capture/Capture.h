#ifndef CAPTURE_H
#define CAPTURE_H

#include <QList>
#include <QFile>
#include <QAudioInput>

#include "AudioCapture.h"
#include "ImageCapture.h"
#include "FormatData.h"
#include "CaptureCB.h"

class Capture : public QObject {

    Q_OBJECT
private:
    AudioCapture *audioCapture;
    ImageCapture *imageCapture;
public:
    explicit Capture(QObject *parent);
    ~Capture();

    QList<FormatData> supportedAudioFormats;
public slots:

    void startCaptureAudio(QString filename /* CaptureCB successCB */); // just test, change later
    void stopCaptureAudio();

    void captureImage();

};

#endif // CAPTURE_H

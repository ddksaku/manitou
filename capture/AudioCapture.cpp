#include <stdlib.h>
#include <math.h>
#include "AudioCapture.h"
#include <QFile>
#include "../AudioPlayer.h"

#define BUFFER_SIZE 4096

AudioInfo::AudioInfo(QObject *parent, QAudioInput *device)
    :QIODevice(parent)
{
    m_maxValue = 0;

}

AudioInfo::~AudioInfo()
{
}

void AudioInfo::start()
{
    open(QIODevice::WriteOnly);

}

void AudioInfo::stop()
{
    close();
}

qint64 AudioInfo::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data)
    Q_UNUSED(maxlen)

    return 0;
}


qint64 AudioInfo::writeData(const char *data, qint64 len)
{
    int samples = len/2; // 2 bytes per sample
    int maxAmp = 32768; // max for S16 samples
    bool clipping = false;

    m_maxValue = 0;
    qint16 *s = (qint16*)data;

    // sample format is S16LE, only!
    for (int i = 0; i < samples; ++i) {
        qint16 sample = *s;
        s++;
        if (abs(sample) > m_maxValue) m_maxValue = abs(sample);
    }
    // check for clipping
    if (m_maxValue >= (maxAmp - 1))
        clipping = true;

    float value = ((float)m_maxValue/(float)maxAmp);
    if (clipping)
        m_maxValue = 100;
    else
        m_maxValue = (int)(value*100);

    // emit update();

    return len;
}

int AudioInfo::LinearMax()
{
    return m_maxValue;
}

AudioCapture::AudioCapture()
{
    format.setFrequency(11150);
    format.setChannels(1);
    format.setSampleSize(8);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    format.setCodec("audio/pcm");

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
    if (!info.isFormatSupported(format)) {
        format = info.nearestFormat(format);
    }

    audioInput = new QAudioInput(format,this);

    // information about inputed audio
    audioInfo = new AudioInfo(this, audioInput);
    
}

AudioCapture::~AudioCapture()
{

}

void AudioCapture::startCapture(QString filename)
{
    // audioInfo->start();
    // audioInput->start(audioInfo);

    outputFile.setFileName(filename);
    outputFile.open(QIODevice::WriteOnly);

    audioInput->start(&outputFile);

}

void AudioCapture::stopCapture()
{
    // audioInfo->stop();
    // audioInput->stop();

    audioInput->stop();
    outputFile.close();

    AudioPlayer *audioPlayer = new AudioPlayer(this);
    audioPlayer->play("D:/test.raw");

}


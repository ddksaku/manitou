#ifndef AUDIOCAPTURE_H
#define AUDIOCAPTURE_H

#include <QAudioInput>
#include <QFile>

class AudioInfo : public QIODevice
{
    Q_OBJECT
public:
    AudioInfo(QObject *parent, QAudioInput *device);
    ~AudioInfo();

    void start();
    void stop();

    int LinearMax();

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

private:
    int m_maxValue;

};


class AudioCapture : public QObject
{
    Q_OBJECT
public:
    AudioCapture();
    ~AudioCapture();

    void startCapture(QString filename);
    void stopCapture();

private:
    AudioInfo *audioInfo;
    QAudioFormat format;
    QAudioInput *audioInput;

    QFile outputFile;

    char *buffer;

};

#endif // AUDIOCAPTURE_H

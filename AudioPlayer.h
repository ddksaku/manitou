#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <phonon>
#include <QUrl>

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent);

public slots:
    void play(QString filename);
    void pause();
    void stop();

private:
    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;
    // Phonon::MediaSource *mediaSource;

};

#endif // AUDIOPLAYER_H

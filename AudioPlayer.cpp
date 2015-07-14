#include "AudioPlayer.h"


AudioPlayer::AudioPlayer(QObject *parent)
    : QObject(parent)
{
    // initializing device and player
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, parent);
    mediaObject = new Phonon::MediaObject(parent);
    // mediaObject->setTickInterval(1000); // for tick() signal
    Phonon::createPath(mediaObject, audioOutput);

}

void AudioPlayer::play(QString url)
{
    QUrl qurl(url);
    Phonon::MediaSource mediaSrc(qurl);
    mediaObject->setCurrentSource(mediaSrc);
    mediaObject->play();
}

void AudioPlayer::pause()
{
    mediaObject->pause();
}

void AudioPlayer::stop()
{
    mediaObject->stop();
}

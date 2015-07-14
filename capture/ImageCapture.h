#ifndef IMAGECAPTURE_H
#define IMAGECAPTURE_H

#include <QObject>
#include "cv.h"
#include "highgui.h"

class ImageCapture : public QObject
{
    Q_OBJECT
public:
    ImageCapture();
    ~ImageCapture();

    void captureImage();

private:
    CvCapture *camera;
};

#endif // IMAGECAPTURE_H

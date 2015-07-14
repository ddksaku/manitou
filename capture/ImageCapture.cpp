#include "ImageCapture.h"
#include "cv.h"
#include "highgui.h"

ImageCapture::ImageCapture()
{
    camera = cvCreateCameraCapture(0);
    cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_WIDTH,640);
    cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_HEIGHT,480);
}

ImageCapture::~ImageCapture()
{
    cvReleaseCapture(&camera);
}

void ImageCapture::captureImage()
{
    cvNamedWindow("Captured Image",CV_WINDOW_AUTOSIZE);

    IplImage *frame;
    if(camera)
    {
        frame = cvQueryFrame(camera);
        cvShowImage("Captured Image", frame);
    }
}

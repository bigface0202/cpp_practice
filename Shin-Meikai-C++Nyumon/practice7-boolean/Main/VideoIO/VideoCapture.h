/**
 * @file VideoCapture.h
 *
 * @author y-ksst / created on 2021/06/30
 * 
 */
#ifndef VIDEO_CAPTURE_H
#define VIDEO_CAPTURE_H

#include <opencv2/videoio.hpp>

#define CAMERA_DEVICE_ID 0

namespace gwrt {

class VideoCapture {

private:

    /* VideoCapture (opnecv) */
    cv::VideoCapture *cap;

public:

    /** Constructor */
    VideoCapture();

    /** Destructor */
    ~VideoCapture();

    /** Show with highgui */
    bool show();

};

}

#endif
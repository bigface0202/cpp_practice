/**
 * @file VideoCapture.cpp
 *
 * @author y-ksst / created on 2021/06/30
 * 
 */
#include <stdio.h>
#include <time.h>
#include <opencv2/highgui.hpp>

#include "Main/VideoIO/VideoCapture.h"
#include "Main/VideoIO/VideoWriter.h"

using namespace gwrt;
using namespace std;

VideoCapture::VideoCapture()
{
    printf( "[VideoCapture]: Constructor\n" );
    printf( "\t* DeviceID:%d open.\n", CAMERA_DEVICE_ID );
    this->cap = new cv::VideoCapture( CAMERA_DEVICE_ID );
}

VideoCapture::~VideoCapture()
{
    printf( "[VideoCapture]: Destructor\n" );
    if ( this->cap->isOpened() ) {
        printf( "\t* cap release.\n" );
        this->cap->release();
    }
    delete this->cap;
}

bool VideoCapture::show()
{
    cv::Mat frame;
    string fileName;
    int fourcc, width, height;
    float fps;
    VideoWriter w;

    fileName = "test.avi";
    fourcc = cv::VideoWriter::fourcc('X', 'V', 'I', 'D');
    width = 640;
    height = 480;
    fps = 30.0;

    w.openVideoWriter(fileName, fourcc, fps, width, height);

    printf( "[VideoCapture::show]:\n" );
    if ( ! this->cap->isOpened() ) {
        return false;
    }
    
    printf( "\t* DeviceID:%d can open.\n", CAMERA_DEVICE_ID );
    
    // Pythonとは違い、capをreadすると提供されたArrayに代入する
    while( this->cap->read( frame ) ) {

        cv::imshow( "sample", frame );
        w.writeVideoWriter(frame);

        const int key = cv::waitKey( 1 );

        if ( key == 'q' ) {
            break;
        }
    }
    cv::destroyAllWindows();
    return true;
}

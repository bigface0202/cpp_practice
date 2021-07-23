/**
 * @file VideoWriter.h
 *
 * @author kishishita / created on 2021/07/02
 * 
 */
#ifndef VIDEO_WRITER_H
#define VIDEO_WRITER_H

#include <stdio.h>
#include <opencv2/videoio.hpp>

using namespace std;

namespace gwrt {

class VideoWriter {

private:

    /* VideoWriter (opencv) */
    cv::VideoWriter *writer;

public:

    /* Constructor */
    VideoWriter();

    /* Destructor */
    ~VideoWriter();

    /* Set the variables into the writer */
    void openVideoWriter(string fileName, int fourcc, float fps, int width, int height);

    /* Write the frame in the opend file */
    void writeVideoWriter(cv::Mat frame);

};

}

#endif
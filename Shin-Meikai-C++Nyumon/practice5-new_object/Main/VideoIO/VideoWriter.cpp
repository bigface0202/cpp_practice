/**
 * @file VideoWriter.cpp
 *
 * @author ssugino / created on 2021/06/30
 * 
 */
#include <stdio.h>

#include "Main/VideoIO/VideoWriter.h"

using namespace gwrt;

VideoWriter::VideoWriter()
{
    printf("[VideoWriter]: Constructor\n");
    this->writer = new cv::VideoWriter();
}

VideoWriter::~VideoWriter()
{
    printf("[VideoCapture]: Destructor\n");
    this->writer->release();

    delete this->writer;
}

void VideoWriter::openVideoWriter(string fileName, int fourcc, float fps, int width, int height)
{
    this->writer->open(fileName, fourcc, fps, cv::Size(width, height));
}

void VideoWriter::writeVideoWriter(cv::Mat frame)
{
    this->writer->write(frame);
}
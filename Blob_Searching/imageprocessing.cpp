#include "imageprocessing.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ballstats.h"
#include <math.h>
#include "stdio.h"
#include <stdlib.h>
#include <iostream>
#include <QDebug>

static const float FRAME_OF_VIEW = 53.5f;

ImageProcessing::ImageProcessing()
{

}
void ImageProcessing::initialize(cv::Mat image)
{
    current_image_ = image;

    //set detector params (it's passed into detector later on)
    cv::SimpleBlobDetector::Params par;
    //circularity
    par.filterByCircularity = true;
    par.minCircularity = 0.5;
    //area
    par.filterByArea = true;
    par.minArea = 250;
    par.maxArea = 1920 * 1080;
    //color
    par.filterByColor = true; //filter by black and white
    par.blobColor = 255;
    par.filterByConvexity = false;
    par.filterByInertia = false;
    //threshold
    par.minThreshold = 225;
    par.maxThreshold = 255;
    par.thresholdStep = 20;

    //create images for later use
    red_ = cv::Mat( image.rows, image.cols, CV_8UC3 );
    green_ = cv::Mat( image.rows, image.cols, CV_8UC3 );
    hsv_ = cv::Mat( image.rows, image.cols, CV_8UC3 );

    //create detector
    cv::SimpleBlobDetector detector(par);
    detector_ = detector;
}

cv::vector<BallStats> ImageProcessing::find_red(cv::Mat input_image)
{
    input_image.copyTo(current_image_);
    cv::cvtColor(current_image_, hsv_, CV_BGR2HSV);
    cv::inRange(hsv_, cv::Scalar(168, 145, 169), cv::Scalar(180, 255, 255), red_);
    detector_.detect(red_, keypoints_red_);
    for (int i = 0; i< keypoints_red_.size(); i++)
    {
        BallStats current_ball(keypoints_red_[i], 1, find_angle(keypoints_red_[i]));
        balls.push_back(current_ball);
        //current_ball.print_stats();
    }
//    cv::drawKeypoints(current_image_, keypoints_red_, output_, cv::Scalar(0,0,255)); //Draws the center of the blobs onto the image
    return balls;
}

cv::vector<BallStats> ImageProcessing::find_green(cv::Mat input_image)
{
    input_image.copyTo(current_image_);
    cv::cvtColor(current_image_, hsv_, CV_BGR2HSV);
    cv::inRange(hsv_, cv::Scalar(49, 114, 106 ), cv::Scalar(77, 255, 255), green_);
    detector_.detect(green_, keypoints_green_);
    for (int i = 0; i< keypoints_green_.size(); i++)
    {
        BallStats current_ball(keypoints_green_[i], 2, find_angle(keypoints_green_[i]));
        balls.push_back(current_ball);
        //current_ball.print_stats();
    }
    //cv::drawKeypoints(current_image_, keypoints_green_, output_, cv::Scalar(0,255,0)); //Draws the center of the blobs onto the image
    return balls;
}

//NOTE: finding balls w/o color is faster
cv::vector<BallStats> ImageProcessing::find_ball(cv::Mat input_image, bool color)
{
    input_image.copyTo(current_image_);

    if (!color)
    {
        cv::cvtColor(current_image_, hsv_, CV_BGR2HSV);
        cv::inRange(hsv_, cv::Scalar(168, 145, 169), cv::Scalar(180, 255, 255), red_);
        cv::inRange(hsv_, cv::Scalar(49, 114, 106 ), cv::Scalar(77, 255, 255), green_);
        cv::bitwise_or(red_, green_, red_);
        detector_.detect(red_, keypoints_red_);
        for (int i = 0; i< keypoints_red_.size(); i++)
        {
            BallStats current_ball(keypoints_red_[i], 0, find_angle(keypoints_red_[i]));
            balls.push_back(current_ball);
            //current_ball.print_stats();
        }
//        cv::drawKeypoints(current_image_, keypoints_red_, output_, cv::Scalar(255,0,0)); //Draws the center of the blobs onto the image
    }
    else
    {
        cv::cvtColor(current_image_, hsv_, CV_BGR2HSV);
        cv::inRange(hsv_, cv::Scalar(168, 145, 169), cv::Scalar(180, 255, 255), red_);
        cv::inRange(hsv_, cv::Scalar(49, 114, 106 ), cv::Scalar(77, 255, 255), green_);
        detector_.detect(green_, keypoints_green_);
        detector_.detect(red_, keypoints_red_);
        for (int i = 0; i< keypoints_red_.size(); i++)
        {
            BallStats current_ball(keypoints_red_[i], 1, find_angle(keypoints_red_[i]));
            balls.push_back(current_ball);
            //current_ball.print_stats();
        }
        for (int i = 0; i< keypoints_green_.size(); i++)
        {
            BallStats current_ball(keypoints_green_[i], 2, find_angle(keypoints_green_[i]));
            balls.push_back(current_ball);
            //current_ball.print_stats();
        }
//        cv::drawKeypoints(current_image_, keypoints_red_, output_, cv::Scalar(255,0,0)); //Draws the center of the red blobs onto the image
//        cv::drawKeypoints(output_, keypoints_green_, output_, cv::Scalar(0,255,0)); //Draws the center of the green blobs onto the image
    }
    return balls;
}

float ImageProcessing::find_angle(cv::KeyPoint coord)
{
    int center_of_frame = current_image_.cols/2;
    float offset = coord.pt.x - center_of_frame;
    return (offset/center_of_frame) * FRAME_OF_VIEW/2 * -1; //times -1 because the camera is upside down
}


ImageProcessing::~ImageProcessing()
{

}


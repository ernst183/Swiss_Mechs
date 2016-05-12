/// \file [FileName]
/// \brief [enter brief description for file]
///
/// [Enter detailed description of the file here]
///

// +----------------------------------------------------------+
// |                                                          |
// |        Copyright (C) 2006 - 2012 IMS - ZHW               |
// |          Institute For Mechatronic Systems               |
// |        Applied science University of Zuerich             |
// |                                                          |
// | SEDE: Seatovic Dejan     (7090)                          |
// |                 ALL RIGHTS RESERVED!                     |
// |                                                          |
// +----------------------------------------------------------+
//

#include "imageprocessing.h"
#include "circle.h"

ImageProcessing::ImageProcessing()
{
    this->time_stamp = 0;
    this->number_circles = 0;
}

void ImageProcessing::find_circles()
{
    cv::Mat current_gray, current_hsv;
    /// Convert it to gray
    cv::cvtColor( this->current_frame, current_gray, CV_BGR2GRAY );

    /// Blur image to reduce noise
    cv::GaussianBlur(current_gray, current_gray, cv::Size(9,9), 2, 2);

    /// Convert it to HSV
    cv::cvtColor( this->current_frame, current_hsv, CV_BGR2HSV );

    /// Reduce the noise so we avoid false circle detection
    cv::GaussianBlur( current_gray, current_gray, cv::Size(3,3), 1, 1 );

    cv::vector < cv::Vec3f > circles;

    /// Apply the Hough Transform to find the circles
    cv::HoughCircles( current_gray, circles, CV_HOUGH_GRADIENT, 1, current_gray.rows / 8, 45, 24, current_gray.rows / 10, 0 );

    for( size_t i = 0; i < circles.size( ); i++ )
    {
        bool red_ball = false;
        bool green_ball = false;
        //std::cout << circles[i][2] << std::endl;
        // circle center
        cv::Point center( cvRound( circles[ i ][ 0 ] ), cvRound( circles[ i ][ 1 ] ) );
        int radius = cvRound( circles[ i ][ 2 ] );
        int red = 0;
        int green = 0;
        int other = 0;
        float step = radius / 2;
        float hue_array[5];

        //center point
        float x = circles[ i ][ 0 ];// - radius;
        float y = circles[ i ][ 1 ];// - radius;
        cv::Vec3b pixel_sample = current_hsv.at < cv::Vec3b > ( y, x ); //vec = [r,g,b]
        float hue = pixel_sample[ 0 ];
        //add to array
        hue_array[0] = hue;
        //std::cout << hue_array[0] << std::endl;

        //north
        y = circles[ i ][ 1 ] + step;
        pixel_sample = current_hsv.at < cv::Vec3b > ( y, x ); //vec = [r,g,b]
        hue = pixel_sample[ 0 ];
        //add to array
        hue_array[1] = hue;
        //std::cout << hue_array[1] << std::endl;

        //south
        y = circles[ i ][ 1 ] - step;
        pixel_sample = current_hsv.at < cv::Vec3b > ( y, x ); //vec = [r,g,b]
        hue = pixel_sample[ 0 ];
        //add to array
        hue_array[2] = hue;
        //std::cout << hue_array[2] << std::endl;

        //east
        x = circles[ i ][ 1 ] + step;
        pixel_sample = current_hsv.at < cv::Vec3b > ( y, x ); //vec = [r,g,b]
        hue = pixel_sample[ 0 ];
        //add to array
        hue_array[3] = hue;
        //std::cout << hue_array[3] << std::endl;

        //west
        x = circles[ i ][ 1 ] - step;
        pixel_sample = current_hsv.at < cv::Vec3b > ( y, x ); //vec = [r,g,b]
        hue = pixel_sample[ 0 ];
        //add to array
        hue_array[4] = hue;
        //std::cout << hue_array[4] << std::endl;


        //NOTE: this is hardcoded to the size of hue_array
        for (int i = 0; i < 5; i++)
        {
            if( /*(hue_array[i] >= 0 && hue_array[i] < 10) ||*/ hue_array[i] > 170 )
            {
                red++;
            }
            else if( hue_array[i] > 50 && hue_array[i] < 70 )
            {
                green++;
            }
            else
            {
                other++;
            }
        }

        //sample from within radius


        if( red >= 3)
        {
            red_ball = true;
            Circle new_circle ( circles[i], true, false, this->time_stamp );
            this->circles[number_circles] = new_circle;
            number_circles++;


        }
        else if( green >= 3 )
        {
            green_ball = true;
            Circle new_circle ( circles[i], false, true, this->time_stamp );
            this->circles[number_circles] = new_circle;
            number_circles++;
        }



        if( red_ball == true )
        {
            circle( this->current_frame, center, 3, cv::Scalar( 0, 0, 255 ), -1, 8, 0 );

            // circle outline
            circle( this->current_frame, center, radius, cv::Scalar( 0, 0, 255 ), 3, 8, 0 );
        }
        else if( green_ball == true )
        {
            circle( this->current_frame, center, 3, cv::Scalar( 0, 255, 0 ), -1, 8, 0 );

            // circle outline
            circle( this->current_frame, center, radius, cv::Scalar( 0, 255, 0 ), 3, 8, 0 );
        }
    }
    this->time_stamp++;
}

void denoise_circles()
{

}

double ImageProcessing::find_distance(Circle &circle)
{
    if(circle.distance == 0)
    {
        circle.distance = 823.32 * pow(circle.circle_vector[2], -.851);
    }
    return circle.distance;
}


//LEFT IS POSITIVE...RIGHT IS NEGATIVE
double ImageProcessing::find_angle(Circle &circle)
{
    if(circle.angle == 180)
    {
        //convert offset (in px) to cm
        //HACK: we hardcode 540. if the width isn't 1080, we're screwed.
        double offset = ((circle.circle_vector[0] - 320) * 2.5) / circle.circle_vector[2];
        //solve for angle
        if (circle.distance != 0)
        {
            circle.angle = (atan2(offset, circle.distance) * 180) / M_PI;
        }
    }
    return circle.angle;
}


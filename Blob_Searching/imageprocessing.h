#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H
#include "imageprocessing.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/opencv.hpp"
#include <math.h>
#include "stdio.h"
#include "ballstats.h"

class ImageProcessing
{
public:    
    enum channels_values
    {
        hue = 0,
        saturation,
        value
    };
    ///
    /// \brief current_image_
    /// Holds the image to be processed.
    /// \brief hsv_
    /// Holds the image converted to Hue/Saturation/Value form.
    /// \brief red_
    /// Holds the binary image showing the red ball.
    /// \brief green_
    /// Holds the binary image showing the green ball.
    /// \brief output_
    /// Used to hold the output image with keypoints drawn on in case it's needed by imshow.
    cv::Mat current_image_, hsv_, red_, green_, output_;

    /// \brief detector_
    /// A SimpleBlobDetector used to find the red and green balls shown in the binary images red_ and green_.
    cv::SimpleBlobDetector detector_;
    /// \brief keypoints_red_
    /// An array of all found keypoints for red balls.
    /// \brief keypoints_green_
    /// An array of all found keypoints fo green balls.
    std::vector<cv::KeyPoint> keypoints_red_, keypoints_green_;
    /// \brief balls
    /// An array of BallStats objects representing each ball found in the frame.
    cv::vector<BallStats> balls;

    ImageProcessing();
    void initialize(cv::Mat image);
    float find_angle(cv::KeyPoint coord);
    ~ImageProcessing();
    ///
    /// \brief find_red
    /// Finds all red balls in the input_image.
    /// \param input_image The image to be processed.
    /// \return An array of Ballstats representing all found red balls.
    ///
    cv::vector<BallStats> find_red(cv::Mat input_image);
    ///
    /// \brief find_green
    /// Finds all green balls in the input_image.
    /// \param input_image The image to be processed.
    /// \return An array of Ballstats representing all found green balls.
    ///
    cv::vector<BallStats> find_green(cv::Mat input_image);
    ///
    /// \brief find_ball
    /// Finds all balls in the input_image.
    /// \param input_image The image to be processed.
    /// \param color If true, will find the color of each ball. If false, find_ball will not differentiate by color. Color = false runs faster.
    /// \return An array of Ballstats representing all found balls.
    ///
    cv::vector<BallStats>  find_ball(cv::Mat input_image, bool color);
};

#endif // IMAGEPROCESSING_H

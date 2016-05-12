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

#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include "imageprocessing_global.h"

class IMAGEPROCESSINGSHARED_EXPORT ImageProcessing {
public:
    int time_stamp;
    int number_circles;
    cv::Mat current_frame;
    Circle circles[100];


    ImageProcessing();

    void find_circles();
    void denoise_circles();
    double find_distance(Circle &circle);
    double find_angle(Circle &circle);
};

#endif // IMAGEPROCESSING_H

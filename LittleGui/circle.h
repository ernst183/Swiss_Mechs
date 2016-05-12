#ifndef CIRCLE_H
#define CIRCLE_H
#include "opencv2/opencv.hpp"
#include <math.h>

class Circle
{
public:
    double distance;
    double angle;
    bool red_ball;
    bool green_ball;
    cv::Vec<float, 3> circle_vector;
    int time_stamp;


    Circle(cv::Vec<float, 3> circle_vector, bool red_ball, bool green_ball, int time_stamp);
    void print_circle();

    Circle();
    ~Circle();
};

#endif // CIRCLE_H

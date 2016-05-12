#include "circle.h"

Circle::Circle(cv::Vec3f circle_vector, bool red_ball, bool green_ball, int time_stamp)
{
    this->circle_vector = circle_vector;
    this->red_ball = red_ball;
    this->green_ball = green_ball;
    this->time_stamp = time_stamp;
    this->angle = 180;
    this->distance = 0;
}

Circle::Circle()
{
    this->angle = 180;
    this->distance = 0;
}

Circle::~Circle()
{

}

void Circle::print_circle()
{
    std::cout << "Radius: " << this->circle_vector[2] << std::endl;
    std::cout << "Distance: " << this->distance << std::endl;
    std::cout << "Angle: " << this->angle << std::endl << std::endl;
}


#include "littlegui.h"
#include "ui_littlegui.h"
#include "QMessageBox"
#include "imageprocessing_global.h"
#include "imageprocessing.h"
#include "circle.h"
#include <math.h>
#include <stdio.h>
#include "opencv2/opencv.hpp"
#include "QBitmap"


LittleGui::LittleGui( QWidget *parent ) : QDialog( parent ),
	ui( new Ui::LittleGui )
{
	ui->setupUi( this );
	cv::Mat mat;
}

LittleGui::~LittleGui( )
{
	delete ui;
}

void LittleGui::on_liveImage_clicked( )
{
    ImageProcessing immy;
    cv::VideoCapture cap( 0 );

    // Create mat with alpha channel
    if( !cap.isOpened( ) ) // check if we succeeded
        return;

    cv::namedWindow( "edges", 1 );
    for ( ; ; )
    {
        cap >> immy.current_frame;
        immy.find_circles();
        for(int i = 0; i < immy.number_circles; i++)
        {
            immy.find_distance(immy.circles[i]);
            immy.find_angle(immy.circles[i]);
            immy.circles[i].print_circle();
        }
        cv::imshow("edges", immy.current_frame);
        cv::waitKey(30);
    }

} // on_liveImage_clicked

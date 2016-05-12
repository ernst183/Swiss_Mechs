#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageprocessing.h"
#include "opencv2/opencv.hpp"
#include "opencv2/features2d/features2d.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    cv::Mat im;
    cv::VideoCapture cap( 0 );
    ImageProcessing immypro;
    immypro.initialize(im);
    for( ; ; )
    {
        // Read image
        // Create mat with alpha channel
        if( !cap.isOpened( ) ) // check if we succeeded
            return;

        cap >> im;
        immypro.find_red(im);
        // Show blobs
        //std::cout << "Finished frame" << std:: endl;
        cv::imshow("keypoints", immypro.current_image_ );
        cv::waitKey(30);
    }
}

#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <vector>
#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <vector>

#include   <stdlib.h>
#include   <time.h>


#include <opencv2/opencv.hpp>

//---------------------------------------qt-------------------------------------------
#include  "QPixmap"
#include  "QLabel"
#include  "QPainter"
#include  "QLabel"
#include  "QTextCodec"

class CommonFunc
{
public:
    CommonFunc();
};


void print_cvMat_info(cv::Mat img) ;
void cvMat_16bit_to_8bit(cv::Mat &src, cv::Mat &out) ;
void cvMat_32bit_to_8bit(cv::Mat &src, cv::Mat &out) ;
int getMatProper(cv::Mat &imageProper);
void showMatOnLabel(cv::Mat img, QLabel *label);

void displayResult(cv::Mat matt, QLabel *label_2);

std::string  getDatetimeStr();
void  _declspec(dllexport) print_To_Glog(std::string words,int degree);

#endif // COMMONFUNC_H

#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <opencv2/opencv.hpp>
//#include <opencv2/stitching.hpp>
//#include <windows.h>  

using namespace std;
using namespace cv;

const double PI = 3.1415926;
// 一些超参， 可以通过调节这些参数来优化匹配拼接的效果
const double Cny1 = 5, Cny2 = 7;  // 原图滤波 canny 函数的第二和第三个参数， 
const int Ksize = 23;  // 原图预处理，形态学闭运算的 ksize 参数，影响轮廓的有效提取
const int  MinLen = 100;  // 判断外轮廓的最小阈值
const double ThresholdLen = 0.36;  // 匹配每条边长度的相对比例阈值
const double ThresholdDir = 12;   // 匹配内角角度的阈值
const double ThresholdAveDir = 4;  // 匹配所有边平均角度的阈值
const double ThresholdTolLen = 0.15;  // 匹配所有边长度的相对比例阈值
const vector<double> Epsilon_Vec{ 2, 3, 4, 6, 8};   // 多边形拟合的可选参数 epsilon， 使其自适应

// ApproxPoly.cpp 
Mat preSolveImg(Mat srcImg, double c1 = Cny1, double c2 = Cny2, int ksize = Ksize);
void extractContours(Mat srcImg, vector<vector<Point>> & contours);
void approxPoly(vector<vector<Point>> & curves, vector<vector<Point>> & contours, double epsilon, int minlen = MinLen);

// TransformImg.cpp
void rotatePoint(Mat rot_mat, Point & pot);
Mat moveImg(Mat srcImg, double x, double y);
Mat rotateImg(Mat srcImg, double angle, Point & pot1, Point & pot2);

// LineFunctions.cpp
double lineLength(const Point & a, const Point & b);
double lineDirection(const Point & a, const Point & b);

// MatchImg.cpp
vector<pair<Point, Point>> matchTwo(int & matchNum, double & matchLen, double & matchTheta, const vector<Point> & contour1,
							const vector<Point> & contour2, double thresholdLen = ThresholdLen, 
							double thresholdDir = ThresholdDir, double thresholdAveDir = ThresholdAveDir);
bool matchImg(vector<pair<Point, Point>> & pot_vec, Mat srcImg1, Mat srcImg2, 
							const vector<double> & epsilon_vec = Epsilon_Vec, double thresholdTolLen = ThresholdTolLen);
//double matchShape(Mat srcImg1, Mat srcImg2);

// JointImg.cpp
Mat jointTwo(Mat srcImg1, Mat srcImg2);
Mat jointImg(vector<Mat> img_vec);

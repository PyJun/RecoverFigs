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
// һЩ���Σ� ����ͨ��������Щ�������Ż�ƥ��ƴ�ӵ�Ч��
const double Cny1 = 5, Cny2 = 7;  // ԭͼ�˲� canny �����ĵڶ��͵����������� 
const int Ksize = 23;  // ԭͼԤ������̬ѧ������� ksize ������Ӱ����������Ч��ȡ
const int  MinLen = 100;  // �ж�����������С��ֵ
const double ThresholdLen = 0.36;  // ƥ��ÿ���߳��ȵ���Ա�����ֵ
const double ThresholdDir = 12;   // ƥ���ڽǽǶȵ���ֵ
const double ThresholdAveDir = 4;  // ƥ�����б�ƽ���Ƕȵ���ֵ
const double ThresholdTolLen = 0.15;  // ƥ�����б߳��ȵ���Ա�����ֵ
const vector<double> Epsilon_Vec{ 2, 3, 4, 6, 8};   // �������ϵĿ�ѡ���� epsilon�� ʹ������Ӧ

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

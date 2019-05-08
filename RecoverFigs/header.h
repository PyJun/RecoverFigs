#pragma once

#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <opencv2/opencv.hpp>
//#include <windows.h>

using namespace std;
using namespace cv;

const string DIR = "D:/codespace/python/�˹�����/���ѧϰ/��Ƭƥ��/data/";
//const string DIR = "./data/";
const double PI = 3.1415926;

// һЩ���Σ� ����ͨ��������Щ�������Ż�ƥ��ƴ�ӵ�Ч��
const double Cny1 = 5, Cny2 = 7;  // ԭͼ�˲� canny �����ĵڶ��͵����������� 
const int Ksize = 23;  // ԭͼԤ������̬ѧ������� ksize ������Ӱ����������Ч��ȡ
const int  MinLen = 100;  // �ж�����������С��ֵ
const double ThresholdLen = 0.4;  // ƥ��ÿ���߳��ȵ���Ա�����ֵ
const double ThresholdDir = 12;   // ƥ���ڽǽǶȵ���ֵ
const double ThresholdAveDir = 4;  // ƥ�����б�ƽ���Ƕȵ���ֵ
const double ThresholdTolLen = 0.14;  // ƥ�����б߳��ȵ���Ա�����ֵ
const double ThresholdAvePixDiff = 32;  // ƥ���֮���ƽ�����ز�
const int Rang = 3;					// ����ƥ��ľ����С
const vector<double> Epsilon_Vec{3, 4, 6, 8};   // �������ϵĿ�ѡ���� epsilon�� ʹ������Ӧ

// ����һ��ƥ���Ľṹ�壬 ����ƥ����ƥ��ϵ��
struct Matcher {
	Point first_p, last_p;
	double match = 0;
	Matcher() = default;
	Matcher(const Point & fp, const Point & lp, double m = 0) : first_p(fp), last_p(lp), match(m) {}
};
const int SIZE = 100;
// matchers[i][j] ��ʾ i ƥ�� j ʱ��ƥ����ƥ��ϵ��
extern Matcher matchers[SIZE][SIZE];
// ��������ͼ�������
extern vector<Mat> imgs_vec;

// ApproxPoly.cpp 
Mat preSolveImg(Mat srcImg, double c1 = Cny1, double c2 = Cny2, int ksize = Ksize);
void extractContours(Mat srcImg, vector<vector<Point>> & contours);
void approxPoly(vector<vector<Point>> & curves, vector<vector<Point>> & contours, double epsilon, int minlen = MinLen);

// TransformImg.cpp
void rotatePoint(Mat rot_mat, Point & pot);
void movePoint(double x, double y, Point & pot);
Mat moveImg(Mat srcImg, double x, double y);
Mat moveImg(Mat srcImg, double x, double y, Point & pot1, Point & pot2, const set<int> & jointedIds, int size);
Mat rotateImg(Mat srcImg, double angle, Point & pot1, Point & pot2);
Mat rotateImg(Mat srcImg, double angle, Point & pot1, Point & pot2, const set<int> & jointedIds, int size);

// LineFunctions.cpp
double lineLength(const Point & a, const Point & b);
double lineDirection(const Point & a, const Point & b);
int minMatElemnet(Mat srcImg, Point pot, int range);

// DetectTarget.cpp
vector<Rect> detectTarget(Mat srcImg);
Mat normalizeImg(Mat srcImg, Rect rect);
Mat normalizeImg(Mat srcImg, Rect rect, const set<int> & jointedIds, int size);

// MatchImg.cpp
vector<pair<Point, Point>> matchTwo(int & matchNum, double & matchLen, double & matchTheta, double & matchPixDiff,
				Mat srcImg1, Mat srcImg2, const vector<Point> & contour1,const vector<Point> & contour2, 
				double thresholdLen = ThresholdLen, double thresholdDir = ThresholdDir, 
				double thresholdAveDir = ThresholdAveDir, double thresholdAvePixDiff = ThresholdAvePixDiff, int range = Rang);
double matchImg(vector<pair<Point, Point>> & pot_vec, Mat srcImg1, Mat srcImg2, 
							const vector<double> & epsilon_vec = Epsilon_Vec, double thresholdTolLen = ThresholdTolLen);
//double matchShape(Mat srcImg1, Mat srcImg2);

// JointImg.cpp
double isJoint(vector<pair<Point, Point>> & pot_vec, Mat srcImg1, Mat srcImg2);
Mat jointTwo(const vector<pair<Point, Point>> & pot_vec, Mat & lastImg, Mat srcImg1, Mat srcImg2);
Mat jointTwo(Mat srcImg1, Mat srcImg2, pair<int,int> pair_id , set<int> & jointedIds, int size);
Mat jointImg(vector<Mat> img_vec);
Mat jointImg(const vector<Mat> & img_vec, const vector<pair<int,int>> & imgNums);

// ImgPrime.cpp
double imgPrime(vector<pair<int,int>> & nums, int size, int start = 0);
bool recoverImg(Mat & dstImg, const vector<Mat> img_vec);

// InitImg.cpp
inline string getImgPath(int i);
vector<Mat> getImgVec(const vector<int> nums);
void initMatchers(const vector<Mat> & img_vec);
vector<int> getNums(int n);


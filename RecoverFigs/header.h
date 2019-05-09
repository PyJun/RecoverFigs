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

using namespace std;
using namespace cv;

//const string DIR = "D:/codespace/python/�˹�����/���ѧϰ/��Ƭƥ��/data";
const string DIR = "./data";
const double PI = 3.1415926;

// һЩ���Σ� ����ͨ��������Щ�������Ż�ƥ��ƴ�ӵ�Ч��
const double Cny1 = 3, Cny2 = 5;  // ԭͼ�˲� canny �����ĵڶ��͵����������� 
const int Ksize = 23;  // ԭͼԤ������̬ѧ������� ksize ������Ӱ����������Ч��ȡ
const int  MinLen = 100;  // �ж�����������С��ֵ
const double ThresholdLen = 0.4;  // ƥ��ÿ���߳��ȵ���Ա�����ֵ
const double ThresholdDir = 12;   // ƥ���ڽǽǶȵ���ֵ
const double ThresholdAveDir = 4;  // ƥ�����б�ƽ���Ƕȵ���ֵ
const double ThresholdTolLen = 0.1;  // ƥ�����б߳��ȵ���Ա�����ֵ
const double ThresholdAvePixDiff = 25;  // ƥ���֮���ƽ�����ز�
const int Rang = 3;					// ����ƥ��ľ����С
const vector<double> Epsilon_Vec{3, 5, 7};   // �������ϵĿ�ѡ���� epsilon�� ʹ������Ӧ

// ����һ��ƥ���Ľṹ�壬 ����ƥ����ƥ��ϵ��
struct Matcher {
	Point first_p, last_p;
	double match;
	Matcher() : match(-1) {}
	Matcher(const Point & fp, const Point & lp, double m = -1) : first_p(fp), last_p(lp), match(m) {}
};
const int SIZE = 100;
// matchers[i][j] ��ʾ i ƥ�� j ʱ��ƥ����ƥ��ϵ��
extern Matcher matchers[SIZE][SIZE];
extern vector<vector<vector<Point>>> contours_vec;

// ApproxPoly.cpp 
Mat preSolveImg(const Mat & srcImg, double c1 = Cny1, double c2 = Cny2, int ksize = Ksize);
void extractContours(const Mat & srcImg, vector<vector<Point>> & contours);
void approxPoly(vector<vector<Point>> & curves, vector<vector<Point>> & contours, double epsilon, int minlen = MinLen);

// TransformImg.cpp
void rotatePoint(const Mat & rot_mat, Point & pot);
void movePoint(double x, double y, Point & pot);
Mat moveImg(const Mat & srcImg, double x, double y, Point & pot1, Point & pot2, const set<int> & jointedIds, int size);
Mat rotateImg(const Mat & srcImg, double angle, Point & pot1, Point & pot2, const set<int> & jointedIds, int size);

// LineFunctions.cpp
double lineLength(const Point & a, const Point & b);
double lineDirection(const Point & a, const Point & b);
int minMatElemnet(const Mat & srcImg, Point pot, int range);

// DetectTarget.cpp
vector<Rect> detectTarget(Mat srcImg);
Mat normalizeImg(Mat srcImg, double rate = 1.128);
Mat normalizeImg(Mat srcImg, Rect rect, const set<int> & jointedIds, int size);

// MatchImg.cpp
vector<pair<Point, Point>> matchTwo(int & matchNum, double & matchLen, double & matchTheta, double & matchPixDiff,
				const Mat & srcImg1, const Mat & srcImg2, const vector<Point> & contour1,const vector<Point> & contour2, 
				double thresholdLen = ThresholdLen, double thresholdDir = ThresholdDir, double thresholdAveDir = ThresholdAveDir, 
				double thresholdAvePixDiff = ThresholdAvePixDiff, int range = Rang);
double matchImg(vector<pair<Point, Point>> & pot_vec, vector<vector<Point>> & contours1, vector<vector<Point>> & contours2, 
				const Mat & srcImg1, const Mat & srcImg2, const vector<double> & epsilon_vec = Epsilon_Vec, 
				double thresholdTolLen = ThresholdTolLen);

// JointImg.cpp
Mat jointTwo(Mat srcImg1, Mat srcImg2, pair<int,int> pair_id , set<int> & jointedIds, int size);
Mat jointImg(const vector<Mat> & img_vec, const vector<pair<int,int>> & imgNums);

// ImgPrime.cpp
double imgPrime(vector<pair<int,int>> & nums, int size, int start = 0);
bool recoverImg(Mat & dstImg, const vector<Mat> & img_vec);

// InitImg.cpp
inline string getImgPath(int i, const string dir = DIR+"/");
vector<Mat> getImgVec(const vector<int> & nums, const string dir = DIR+"/");
void initMatchers(const vector<Mat> & img_vec);
vector<int> getNums(int n);


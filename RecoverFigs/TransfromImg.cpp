#include "header.h"

// ��һ�������� pot ������ת
void rotatePoint(Mat rot_mat, Point & pot) {
	Mat p(3, 1, CV_64FC1);
	p.at<double>(0, 0) = pot.x;
	p.at<double>(1, 0) = pot.y;
	p.at<double>(2, 0) = 1;
	Mat rot_pot = rot_mat * p;
	pot.x = rot_pot.at<double>(0, 0);
	pot.y = rot_pot.at<double>(1, 0);
}

// ��һ��ͼ�������ת��ͬʱ������ת��ԭͼ����� pot1, pot2 ����ͼ���е�λ��
Mat rotateImg(Mat srcImg, double angle, Point & pot1, Point & pot2) {
	Mat dstImg(srcImg.size(), srcImg.type(), Scalar::all(255));
	Point2f center(dstImg.cols / 2, dstImg.rows / 2);
	Mat rot_mat = getRotationMatrix2D(center, angle, 1);
	warpAffine(srcImg, dstImg, rot_mat, Size(dstImg.cols, dstImg.rows), INTER_LINEAR, BORDER_CONSTANT, Scalar::all(255));
	rotatePoint(rot_mat, pot1);
	rotatePoint(rot_mat, pot2);
	return dstImg;
}

// ��һ��ͼ�����ƽ��
Mat moveImg(Mat srcImg, double x, double y) {
	Mat dstImg;
	Mat mv_mat = Mat::zeros(2, 3, CV_64FC1);
	mv_mat.at<double>(0, 0) = 1;
	mv_mat.at<double>(0, 2) = x; //ˮƽƽ����
	mv_mat.at<double>(1, 1) = 1;
	mv_mat.at<double>(1, 2) = y; //��ֱƽ����
	warpAffine(srcImg, dstImg, mv_mat, srcImg.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar::all(255));
	return dstImg;
}

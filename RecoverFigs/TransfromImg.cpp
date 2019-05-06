#include "header.h"

// 对一个点坐标 pot 进行旋转
void rotatePoint(Mat rot_mat, Point & pot) {
	Mat p(3, 1, CV_64FC1);
	p.at<double>(0, 0) = pot.x;
	p.at<double>(1, 0) = pot.y;
	p.at<double>(2, 0) = 1;
	Mat rot_pot = rot_mat * p;
	pot.x = rot_pot.at<double>(0, 0);
	pot.y = rot_pot.at<double>(1, 0);
}

// 对一个图像进行旋转，同时更新旋转后原图像二点 pot1, pot2 在新图像中的位置
Mat rotateImg(Mat srcImg, double angle, Point & pot1, Point & pot2) {
	Mat dstImg(srcImg.size(), srcImg.type(), Scalar::all(255));
	Point2f center(dstImg.cols / 2, dstImg.rows / 2);
	Mat rot_mat = getRotationMatrix2D(center, angle, 1);
	warpAffine(srcImg, dstImg, rot_mat, Size(dstImg.cols, dstImg.rows), INTER_LINEAR, BORDER_CONSTANT, Scalar::all(255));
	rotatePoint(rot_mat, pot1);
	rotatePoint(rot_mat, pot2);
	return dstImg;
}

// 对一个图像进行平移
Mat moveImg(Mat srcImg, double x, double y) {
	Mat dstImg;
	Mat mv_mat = Mat::zeros(2, 3, CV_64FC1);
	mv_mat.at<double>(0, 0) = 1;
	mv_mat.at<double>(0, 2) = x; //水平平移量
	mv_mat.at<double>(1, 1) = 1;
	mv_mat.at<double>(1, 2) = y; //竖直平移量
	warpAffine(srcImg, dstImg, mv_mat, srcImg.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar::all(255));
	return dstImg;
}

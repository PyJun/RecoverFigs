#include "header.h"

// ����ԭͼ�񷵻�һ��Ŀ������ľ���
vector<Rect> detectTarget(Mat srcImg) {
	Mat grayImg;
	cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
	vector<Rect> rect_vec;
	Mat binImg = preSolveImg(grayImg);
	vector<vector<Point>> contours, curves;
	extractContours(binImg, contours);
	approxPoly(curves, contours, 1.0);
	for (auto & contour : curves) {
		int min_x = 0x3f3f3f3f, min_y = 0x3f3f3f3f;
		int max_x = 0, max_y = 0;
		for (auto & pot : contour) {
			min_x = min(min_x, pot.x);
			min_y = min(min_y, pot.y);
			max_x = max(max_x, pot.x);
			max_y = max(max_y, pot.y);
		}
		rect_vec.push_back(Rect(min_x, min_y, max_x - min_x, max_y - min_y));
	}
	return rect_vec;
}

// ͨ��һ��Ŀ��߽�ľ������淶��ԭͼ��
Mat normalizeImg(Mat srcImg, Rect rect) {
	double width = rect.width, height = rect.height;
	double length = sqrt(width * width + height * height);
	int interval_x = (int)ceil((length - width + 32) / 2);
	int interval_y = (int)ceil((length - height + 32) / 2);
	Mat dstImg(rect.height + 2 * interval_y, rect.width + 2 * interval_x, srcImg.type(), Scalar::all(255));
	Mat tgtImg = srcImg(rect);
	tgtImg.copyTo(dstImg(Range(interval_y, interval_y + rect.height), Range(interval_x, interval_x + rect.width)));
	return dstImg;
}
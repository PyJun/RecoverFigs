#include "header.h"

// ��ͼ����д��� ������˹�˲��� canny���ӣ� ��̬ѧ������
// ���յõ��ڰ�ͼ�񣬰�ɫΪǰ������ɫΪ����
Mat preSolveImg(const Mat & srcImg, double c1, double c2, int ksize) {
	Mat tempImg = srcImg.clone(), edges;
	GaussianBlur(tempImg, tempImg, Size(3, 3), 0.1, 0.1);
	Canny(tempImg, edges, c1, c2, 5);
	//imshow("Canny", edges);
	Mat white(tempImg.size(), tempImg.type(), Scalar::all(255));
	tempImg = Mat(tempImg.size(), tempImg.type(), Scalar::all(0));
	white.copyTo(tempImg, edges);
	Mat element1 = getStructuringElement(MORPH_ELLIPSE, Size(ksize, ksize));
	morphologyEx(tempImg, tempImg, MORPH_CLOSE, element1);
	//Mat element2 = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	//morphologyEx(tempImg, tempImg, MORPH_OPEN, element2);
	//threshold(tempImg, tempImg, 150, 255, THRESH_BINARY_INV);
	Mat dstImg = tempImg;
	//vector<Vec4i> hierarchy;
	//vector<vector<Point>> contours;
	//findContours(srcImg, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//int i = 0;
	//for (auto ctIter = contours.begin(); ctIter != contours.end(); ctIter++, i++) {
	//	if (ctIter->size() > 4) drawContours(dstImg, contours, i, Scalar::all(100), FILLED);
	//}
	//imshow("binImg", dstImg);
	//waitKey(0);
	return dstImg;
}

// �Ժڰ׵�����ͼ��ȡ��������
void extractContours(const Mat & srcImg, vector<vector<Point>> & contours) {
	contours.clear();
	vector<Vec4i> hierarchy;
	findContours(srcImg, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0,0));
}

// ����������contours�н��ж������ϣ��õ���������� curves
// minlen Ϊ���������³�����ֵ��epsilon Ϊ�������ϵ����
// ���Եõ����������������꣬ ���Կ����ڶ���Ƭ����ȡ
void approxPoly(vector<vector<Point>> & curves, vector<vector<Point>> & contours, double epsilon, int minlen) {
	curves.clear();
	for (auto & vec : contours) {
		if (vec.size() > minlen) {
			vector<Point> tempVec;
			approxPolyDP(vec, tempVec, epsilon, true);
			curves.push_back(tempVec);
		}
	}
}

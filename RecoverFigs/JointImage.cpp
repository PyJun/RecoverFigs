//#include "header.h"
//
//void createImageVec(vector<Image> & image_vec, const vector<Mat> & img_vec, const vector<int> & id_vec) {
//	if (img_vec.size() != id_vec.size()) return;
//	image_vec.clear();
//	for (int i = 0; i < (int)img_vec.size(); i++) {
//		image_vec.emplace_back(img_vec[i], id_vec[i]);
//	}
//}
//
//
//// �� jointTwo �������أ�ʹ�� Image ��
//Mat jointTwoMat(const vector<pair<Point, Point>> & pot_vec, const  Mat & srcImg1, const Mat & srcImg2) {
//	Point first_p1, last_p1, first_p2, last_p2;
//	first_p1 = pot_vec[0].first;
//	last_p1 = pot_vec[1].first;
//	first_p2 = pot_vec[0].second;
//	last_p2 = pot_vec[1].second;
//	// �ֱ�õ� p1��p2 ֱ�ߵ���б��
//	double theta1 = lineDirection(first_p1, last_p1);
//	double theta2 = lineDirection(first_p2, last_p2);
//	// �� srcImg ͼ����ת������ˮƽƴ��
//	Image dstImage1(srcImg1), dstImage2(srcImg2);
//	dstImage1.matchers.emplace_back(first_p1, last_p1);
//	dstImage2.matchers.emplace_back(first_p2, last_p2);
//	dstImage1.rotate(90 - theta1);
//	dstImage2.rotate(90 - theta2);
//	// ˮƽ��չ���󣬵õ�������ȸ����� Mat �����Ա����ͼ�񲻻����
//	int com_rows = max(dstImage1.img.rows, dstImage2.img.rows), com_cols = dstImage1.img.cols + dstImage2.img.cols;
//	Mat comImg1(com_rows, com_cols, CV_8UC3, Scalar::all(255)), comImg2(com_rows, com_cols, CV_8UC3, Scalar::all(255));
//	dstImage1.img.copyTo(comImg1(Range(0, dstImage1.img.rows), Range(0, dstImage1.img.cols)));
//	dstImage2.img.copyTo(comImg2(Range(0, dstImage2.img.rows), Range(0, dstImage2.img.cols)));
//	dstImage1.img = comImg1;
//	dstImage2.img = comImg2;
//	////hconcat(dstImg1, Mat(dstImg2.size(), dstImg2.type(), Scalar(255, 255, 255)), comImg1);
//	////hconcat(Mat(dstImg1.size(), dstImg1.type(), Scalar(255, 255, 255)), dstImg2, comImg2);
//	// ����ͼƬ1ƽ����ͼƬ2ˮƽƴ��ʱ�����λ����
//	double mv_x = ((dstImage2.matchers[0].first_pot.x - dstImage1.matchers[0].first_pot.x) + (dstImage1.matchers[0]last_p2.x - last_p1.x)) / 2;
//	double mv_y = ((first_p2.y - first_p1.y) + (last_p2.y - last_p1.y)) / 2;
//	cout << mv_x << " " << mv_y << endl;
//	imshow("dstImage1.img", dstImage1.img);
//	imshow("dstImage2ǰ.img", dstImage2.img);
//
//	dstImage2.move(-mv_x, -mv_y);
//	imshow("dstImage2��.img", dstImage2.img);
//	// �õ�������󣬲��� comImg1 ������ comImg �õ�����ƴ�Ӻ��ͼ��
//	Mat mask = preSolveImg(dstImage2.img);
//	//imshow("mask", mask);
//	dstImage2.img.copyTo(dstImage1.img, mask);
//	imshow("mergedImage.img", dstImage1.img);
//	if (dstImage1.normalize()) {
//		return dstImage1.img;
//	}
//	return Mat();
//}
//

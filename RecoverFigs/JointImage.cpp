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
//// 对 jointTwo 进行重载，使用 Image 类
//Mat jointTwoMat(const vector<pair<Point, Point>> & pot_vec, const  Mat & srcImg1, const Mat & srcImg2) {
//	Point first_p1, last_p1, first_p2, last_p2;
//	first_p1 = pot_vec[0].first;
//	last_p1 = pot_vec[1].first;
//	first_p2 = pot_vec[0].second;
//	last_p2 = pot_vec[1].second;
//	// 分别得到 p1，p2 直线的倾斜角
//	double theta1 = lineDirection(first_p1, last_p1);
//	double theta2 = lineDirection(first_p2, last_p2);
//	// 将 srcImg 图像旋转至可以水平拼接
//	Image dstImage1(srcImg1), dstImage2(srcImg2);
//	dstImage1.matchers.emplace_back(first_p1, last_p1);
//	dstImage2.matchers.emplace_back(first_p2, last_p2);
//	dstImage1.rotate(90 - theta1);
//	dstImage2.rotate(90 - theta2);
//	// 水平扩展矩阵，得到二个宽度更长的 Mat 对象，以便填充图像不会溢出
//	int com_rows = max(dstImage1.img.rows, dstImage2.img.rows), com_cols = dstImage1.img.cols + dstImage2.img.cols;
//	Mat comImg1(com_rows, com_cols, CV_8UC3, Scalar::all(255)), comImg2(com_rows, com_cols, CV_8UC3, Scalar::all(255));
//	dstImage1.img.copyTo(comImg1(Range(0, dstImage1.img.rows), Range(0, dstImage1.img.cols)));
//	dstImage2.img.copyTo(comImg2(Range(0, dstImage2.img.rows), Range(0, dstImage2.img.cols)));
//	dstImage1.img = comImg1;
//	dstImage2.img = comImg2;
//	////hconcat(dstImg1, Mat(dstImg2.size(), dstImg2.type(), Scalar(255, 255, 255)), comImg1);
//	////hconcat(Mat(dstImg1.size(), dstImg1.type(), Scalar(255, 255, 255)), dstImg2, comImg2);
//	// 计算图片1平移至图片2水平拼接时所需的位移量
//	double mv_x = ((dstImage2.matchers[0].first_pot.x - dstImage1.matchers[0].first_pot.x) + (dstImage1.matchers[0]last_p2.x - last_p1.x)) / 2;
//	double mv_y = ((first_p2.y - first_p1.y) + (last_p2.y - last_p1.y)) / 2;
//	cout << mv_x << " " << mv_y << endl;
//	imshow("dstImage1.img", dstImage1.img);
//	imshow("dstImage2前.img", dstImage2.img);
//
//	dstImage2.move(-mv_x, -mv_y);
//	imshow("dstImage2后.img", dstImage2.img);
//	// 得到掩码矩阵，并将 comImg1 拷贝至 comImg 得到最终拼接后的图像
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

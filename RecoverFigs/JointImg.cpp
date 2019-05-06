#include "header.h"

// 对二个原图像进行拼接， 若不能拼接，返回空的 Mat 对象
// 这里的 srcImg 为三通道图，即 rgb 图
Mat jointTwo(Mat srcImg1, Mat srcImg2) {
	Mat grayImg1, grayImg2;
	cvtColor(srcImg1, grayImg1, COLOR_BGR2GRAY);
	cvtColor(srcImg2, grayImg2, COLOR_BGR2GRAY);
	vector<pair<Point, Point>> pot_vec;
	if (matchImg(pot_vec, grayImg1, grayImg2)) {
		Point first_p1, last_p1, first_p2, last_p2;
		first_p1 = pot_vec[0].first;
		last_p1 = pot_vec[1].first;
		first_p2 = pot_vec[0].second;
		last_p2 = pot_vec[1].second;
		// 分别得到 p1，p2 直线的倾斜角
		double theta1 = lineDirection(first_p1, last_p1);
		double theta2 = lineDirection(first_p2, last_p2);
		// 将 srcImg 图像旋转至可以水平拼接
		Mat dstImg1 = rotateImg(srcImg1, 90 - theta1, first_p1, last_p1);
		Mat dstImg2 = rotateImg(srcImg2, 90 - theta2, first_p2, last_p2);
		int com_rows = dstImg1.rows+dstImg2.rows, com_cols = dstImg1.cols + dstImg2.cols;
		Mat comImg1(com_rows, com_cols, CV_8UC3, Scalar::all(255)), comImg2(com_rows, com_cols, CV_8UC3, Scalar::all(255));
		// 水平扩展矩阵，得到二个宽度更长的 Mat 对象，以便填充图像不会溢出
		dstImg1.copyTo(comImg1(Range(0, dstImg1.rows), Range(0, dstImg1.cols)));
		dstImg2.copyTo(comImg2(Range(dstImg1.rows, com_rows), Range(dstImg1.cols, com_cols)));
		//hconcat(dstImg1, Mat(dstImg2.size(), dstImg2.type(), Scalar(255, 255, 255)), comImg1);
		//hconcat(Mat(dstImg1.size(), dstImg1.type(), Scalar(255, 255, 255)), dstImg2, comImg2);
		// 计算图片2平移至图片1水平拼接时所需的位移量， 并平移
		double mv_x = ((first_p1.x - first_p2.x) + (last_p1.x - last_p2.x)) / 2 - dstImg1.cols;
		double mv_y = ((first_p1.y - first_p2.y) + (last_p1.y - last_p2.y)) / 2 - dstImg1.rows;
		Mat comImg = moveImg(comImg2, mv_x, mv_y);
		// 得到掩码矩阵，并将 comImg1 拷贝至 comImg 得到最终拼接后的图像
		Mat mask = preSolveImg(comImg1);
		comImg1.copyTo(comImg, mask);

		//// 测试代码
		//imshow("comImg1", comImg1);
		//imshow("comImg2", comImg2);
		//imshow("mask", mask);
		//imshow("comImg", comImg);
		//waitKey(0);

		return comImg;
	}
	return Mat();
}

// 对多个碎片图像进行拼接复原
// img_vec 为 Mat类型 的向量， 返回值为一个拼接后的 Mat 矩阵
Mat jointImg(vector<Mat> img_vec) {
	if (img_vec.empty()) return Mat();
	Mat dstImg = img_vec[0];
	for (int i = 1; !dstImg.empty() && i < (int)img_vec.size(); i++) {
		dstImg = jointTwo(dstImg, img_vec[i]);
	}
	return dstImg;
}


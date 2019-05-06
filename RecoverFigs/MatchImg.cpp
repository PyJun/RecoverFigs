#include "header.h"

// contour1:		图一多边形拟合后端点
// contour2:		图二多边形拟合后端点
//  阈值:
// thresholdLen:	匹配最大长度差
// thresholdDir:	匹配最大角度差
//  传出参数：
// matchNum:		匹配的点坐标数
// matchLen:		匹配轮廓线的总长度
//  返回值:			多组匹配的点坐标 (这里为二组，即第一组匹配的点坐标和最后一组匹配的点坐标， 后期可根据需要改动)
vector<pair<Point, Point>> matchTwo(int & matchNum, double & matchLen, double & matchTheta, const vector<Point> & contour1,
						const vector<Point> & contour2, double thresholdLen, double thresholdDir, double thresholdAveDir)
{
	int size1 = (int)contour1.size();
	int size2 = (int)contour2.size();
	int minsize = min(size1, size2);
	vector<double> lens1;  // 轮廓线长度向量
	vector<double> lens2;
	vector<double> thetas1;  // 轮廓线的角度向量
	vector<double> thetas2;
	// 依次对 lens 和 thetas 进行初始化
	for (int i = 0; i < size1; i++) {
		if (i == 0) {
			lens1.push_back(lineLength(contour1[size1 - 1], contour1[0]));
			thetas1.push_back(lineDirection(contour1[size1 - 1], contour1[0]));
		}
		else {
			lens1.push_back(lineLength(contour1[i - 1], contour1[i]));
			thetas1.push_back(lineDirection(contour1[i - 1], contour1[i]));
		}
	}
	double th1 = thetas1[0];
	for (int i = 0; i < size1 - 1; i++) thetas1[i] = thetas1[i + 1] - thetas1[i];
	thetas1[size1 - 1] = th1 - thetas1[size1 - 1];
	for (int i = 0; i < size2; i++) {
		if (i == size2 - 1) {
			lens2.push_back(lineLength(contour2[0], contour2[size2 - 1]));
			thetas2.push_back(lineDirection(contour2[0], contour2[size2 - 1]));
		}
		else {
			lens2.push_back(lineLength(contour2[i + 1], contour2[i]));
			thetas2.push_back(lineDirection(contour2[i + 1], contour2[i]));
		}
	}
	double th2 = thetas2[size2 - 1];
	for (int i = size2 - 1; i > 0; i--) thetas2[i] = thetas2[i - 1] - thetas2[i];
	thetas2[0] = th2 - thetas2[0];
	for (auto &th : thetas1) th = (th > 0) ? th : th + 360;
	for (auto &th : thetas2) th = (th > 0) ? th : th + 360;
	// 然后根据 lens 和 thetas 来匹配
	double maxMatchLen = 0; // 最长匹配长度
	double minAveTh = 1e10;  // 最小的平均匹配角度
	int maxMatchNum = 0;  // 最大的匹配点数
	int maxBegin1 = 0, maxBegin2 = 0; // 匹配的初始下标
	// 三重循环暴力法遍历
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			int num = 0;
			double lenNow = 0;
			double aveTh = 0;
			for (int k = 0; k < minsize; k++) {
				double del_th = fabs(thetas1[(i + k) % size1] - thetas2[(j - k + size2) % size2]);
				del_th = min(del_th, 360 - del_th);
				double l1_1 = lens1[(i + k) % size1], l1_2 = lens2[(j - k + size2) % size2];
				double l2_1 = lens1[(i + k + 1) % size1], l2_2 = lens2[(j - k - 1 + size2) % size2];
				// 匹配的基本条件
				if (fabs(l1_1 - l1_2) / (l1_1 + l1_2) <= thresholdLen / 2 &&
					fabs(l2_1 - l2_2) / (l2_1 + l2_2) <= thresholdLen / 2 && del_th <= thresholdDir) {
					num++;
					lenNow += (l1_1 + l1_2 + l2_1 + l2_2) / 4;
					aveTh += del_th;
				}
				else {
					break;
				}
			}
			if (num > 1) {
				aveTh /= num;
				//  匹配的优化目标， 这里为匹配长度尽可能长，同时平均匹配角度小于某个阈值
				if (lenNow > maxMatchLen && aveTh < thresholdAveDir) {
					maxMatchNum = num;
					maxMatchLen = lenNow;
					minAveTh = aveTh;
					maxBegin1 = i;
					maxBegin2 = (j - num + 1 + size2) % size2;
				}
			}
		}
	}
	// 传出匹配长度和匹配点数
	matchNum = maxMatchNum;
	matchLen = maxMatchLen;
	matchTheta = minAveTh;
	vector<pair<Point, Point>> pot_vec;
	if (maxMatchNum > 1) {
		pot_vec.resize(2);
		//// 分别表示第一对匹配的点和最后一对匹配的点
		//Point first_p1, last_p1, first_p2, last_p2; 
		//if (maxMatchNum > 1) {
		//	first_p1 = contour1[maxBegin1];
		//	last_p1 = contour1[(maxBegin1 + maxMatchNum - 1) % size1];
		//	first_p2 = contour2[(maxBegin2 + maxMatchNum - 1) % size2];
		//	last_p2 = contour2[maxBegin2];
		//}
		//else {
		//	first_p1 = contour1[(maxBegin1 - 1 + size1) % size1];
		//	last_p1 = contour1[(maxBegin1 + maxMatchNum) % size1];
		//	first_p2 = contour2[(maxBegin2 + maxMatchNum) % size2];
		//	last_p2 = contour2[(maxBegin2 - 1 + size2) % size2];
		//}
		Point first_p1, last_p1, first_p2, last_p2; 
		first_p1 = contour1[(maxBegin1 - 1 + size1) % size1];
		last_p1 = contour1[(maxBegin1 + maxMatchNum) % size1];
		first_p2 = contour2[(maxBegin2 + maxMatchNum) % size2];
		last_p2 = contour2[(maxBegin2 - 1 + size2) % size2];
		pot_vec[0].first = first_p1;
		pot_vec[0].second = first_p2;
		pot_vec[1].first = last_p1;
		pot_vec[1].second = last_p2;
	}
	// 最后返回多组匹配的点坐标
	return pot_vec;
}

// srcImg1, srcImg2 为带匹配的原图， 必须是一通道的，即灰度图
// pot_vec 为成功匹配后的多组匹配点坐标
// 若可以匹配，则放回true, 否则， false
// 封装该函数的目的是为了让 多边形拟合的 epsilong 参数可以自适应， 取得最佳匹配的那个参数
bool matchImg(vector<pair<Point, Point>> & pot_vec, Mat srcImg1, Mat srcImg2, 
				const vector<double> & epsilon_vec, double thresholdTolLen) {
	Mat binImg1 = preSolveImg(srcImg1);
	Mat binImg2 = preSolveImg(srcImg2);
	vector<vector<Point>> contours1, contours2, curves1, curves2;
	vector<Point> curve1, curve2;
	extractContours(binImg1, contours1);
	extractContours(binImg2, contours2);
	// 计算轮廓的总长度，这里只取第一个轮廓
	int maxMatchNum = 0;
	double maxMatchLen = 0;
	double minMatchTheta = 360;
	// 对可能的 epsilong 进行穷举，找到最好的那个匹配的情况
	for (auto epsilon : epsilon_vec) {
		approxPoly(curves1, contours1, epsilon);
		approxPoly(curves2, contours2, epsilon);
		int matchNum = 0;
		double matchLen = 0;
		double matchTheta = 360;
		// 这里总假定 curves 里面只有一组轮廓坐标，这个后期根据需要可以改动
		vector<pair<Point, Point>> temp_vec = matchTwo(matchNum, matchLen, matchTheta, curves1[0], curves2[0]);
		if (matchNum > maxMatchNum || (matchNum == maxMatchNum && matchTheta < minMatchTheta)) {
			maxMatchNum = matchNum;
			maxMatchLen = matchLen;
			minMatchTheta = matchTheta;
			pot_vec = temp_vec;
			// 更新最大值以及 pot_vec
			curve1 = curves1[0];  // test !
			curve2 = curves2[0];
		}
	}
	if (maxMatchNum > 1) {
		double tolLen = min(arcLength(curve1, true), arcLength(curve2, true));

		////测试代码
		//Point first_p1, last_p1, first_p2, last_p2;
		//first_p1 = pot_vec[0].first;
		//last_p1 = pot_vec[1].first;
		//first_p2 = pot_vec[0].second;
		//last_p2 = pot_vec[1].second;
		//Mat img1(srcImg1.size(), srcImg1.type(), Scalar::all(255)), img2(srcImg2.size(), srcImg2.type(), Scalar::all(255));
		//for (int i = 0; i < (int)curve1.size(); i++) {
		//	line(img1, curve1[i], curve1[(i + 1) % (int)curve1.size()], Scalar::all(0), 2);
		//}
		//for (int i = 0; i < (int)curve2.size(); i++) {
		//	line(img2, curve2[i], curve2[(i + 1) % (int)curve2.size()], Scalar::all(0), 2);
		//}
		//ellipse(img1, first_p1, Size(11, 7), 0, 0, 360, Scalar(50), 2);
		//ellipse(img1, last_p1, Size(7, 11), 0, 0, 360, Scalar(50), 2);
		//ellipse(img2, first_p2, Size(11, 7), 0, 0, 360, Scalar(50), 2);
		//ellipse(img2, last_p2, Size(7, 11), 0, 0, 360, Scalar(50), 2);
		//imshow("img1", img1);
		//imshow("img2", img2);
		//cout << "tolLen: " << tolLen << endl;
		//cout << "minMatchNum: " << maxMatchNum << endl;
		//cout << "maxMatchLen: " << maxMatchLen << endl;
		//cout << "minMatchTheta: " << minMatchTheta << endl;

		// 不满足给定的条件，则不能匹配
		return maxMatchLen / tolLen > thresholdTolLen;
	}
	return false;
}



















//double matchShape(Mat srcImg1, Mat srcImg2) {
//	Mat grayImg1, grayImg2;
//	cvtColor(srcImg1, grayImg1, COLOR_BGR2GRAY);
//	cvtColor(srcImg2, grayImg2, COLOR_BGR2GRAY);
//	Mat binImg1 = preSolveImg(grayImg1);
//	Mat binImg2 = preSolveImg(grayImg2);
//	vector<vector<Point>> contours1, contours2, curves1, curves2;
//	extractContours(binImg1, contours1);
//	extractContours(binImg2, contours2);
//	approxPoly(curves1, contours1, 4);
//	approxPoly(curves2, contours2, 4);
//	double rate = matchShapes(curves1[0], curves2[0], CONTOURS_MATCH_I1, 0);
//	return rate;
//}






/*
	double theta1 = lineDirection(first_p1, last_p1);
	double theta2 = lineDirection(first_p2, last_p2);
	double rel_theta = theta1 - theta2;
	//数据
	cout << "contour1: " << contour1.size() << endl;
	cout << "contour2: " << contour2.size() << endl;
	cout << "maxBegin1: " << maxBegin1 << endl;
	cout << "maxBegin2: " << maxBegin2 << endl;
	cout << "maxMatchNum: " << maxMatchNum << endl;
	cout << "minAveTh: " << minAveTh << endl;
	cout << "maxMatchLen: " << maxMatchLen << endl;
	cout << "theta1: " << theta1 << endl;
	cout << "theta2: " << theta2 << endl;
	cout << "rel_theta: " << rel_theta << endl;

	Mat dstImg1 = showImg(srcImg1, contour1, maxBegin1, maxMatchNum, 0);
	Mat dstImg2 = showImg(srcImg2, contour2, maxBegin2, maxMatchNum, 1);
	ellipse(dstImg1, first_p1, Size(11, 7), 0, 0, 360, Scalar(50), 2);
	ellipse(dstImg1, last_p1, Size(7, 11), 0, 0, 360, Scalar(50), 2);
	ellipse(dstImg2, first_p2, Size(11, 7), 0, 0, 360, Scalar(50), 2);
	ellipse(dstImg2, last_p2, Size(7, 11), 0, 0, 360, Scalar(50), 2);
	//putText(dstImg1, "first_p1", first_p1, FONT_HERSHEY_COMPLEX, 1, Scalar(100));
	//putText(dstImg1, "last_p1", last_p1, FONT_HERSHEY_COMPLEX, 1, Scalar(100));
	//putText(dstImg2, "firsr_p2", first_p2, FONT_HERSHEY_COMPLEX, 1, Scalar(100));
	//putText(dstImg2, "last_p2", last_p2, FONT_HERSHEY_COMPLEX, 1, Scalar(100));


	////标出匹配点
	for (int i = maxBegin1; i < maxBegin1 + maxMatchNum; i++){
		//circle(srcimg1, contour1[i%size1], 3, scalar(0), 2);
		cout << lens1[i%size1] << " " << thetas1[i%size1] << " " << contour1[i%size1] << endl;
	}
	cout << endl;	
	for (int i = maxBegin2+maxMatchNum-1; i >= maxBegin2; i--) {
		//circle(srcimg2, contour2[i%size2], 3, scalar(0), 2);
		cout << lens2[i%size2] << " " << thetas2[i%size2] << " " << contour2[i%size2] << endl;
	}
	Mat dstImg3 = rotateImg(srcImg1, 90 - theta1, first_p1, last_p1);
	Mat dstImg4 = rotateImg(srcImg2, 90 - theta2, first_p2, last_p2);
	//ellipse(dstImg3, first_p1, Size(11, 7), 0, 0, 360, Scalar(50), 2);
	//ellipse(dstImg3, last_p1, Size(11, 7), 0, 0, 360, Scalar(50), 2);
	//ellipse(dstImg4, first_p2, Size(11, 7), 0, 0, 360, Scalar(50), 2);
	//ellipse(dstImg4, last_p2, Size(11, 7), 0, 0, 360, Scalar(50), 2);
	Mat comImg1, comImg2, comImg;
	hconcat(dstImg3, Mat(dstImg4.size(), dstImg4.type(), Scalar(255)), comImg1);
	hconcat(Mat(dstImg4.size(), dstImg4.type(), Scalar(255)), dstImg4, comImg2);
	double mv_x = ((first_p1.x - first_p2.x) + (last_p1.x - last_p2.x)) / 2 - dstImg4.cols;
	double mv_y = ((first_p1.y - first_p2.y) + (last_p1.y - last_p2.y)) / 2;
	comImg = moveImg(comImg2, mv_x, mv_y);
	Mat mask = preSolveImg(comImg1);
	comImg1.copyTo(comImg, mask);
	//imshow("srcImg1", srcImg1);
	//imshow("srcImg2", srcImg2);
	imshow("dstImg1", dstImg1);
	imshow("dstImg2", dstImg2);
	//imshow("dstImg3", dstImg3);
	//imshow("dstImg4", dstImg4);
	//imshow("comImg1", comImg1);
	//imshow("comImg2", comImg2);
	//imshow("mask", mask);
	imshow("comImg", comImg);

	waitKey(0);

	return rel_theta;
}

Mat showImg(Mat srcImg, const vector<Point> & contour, int maxBegin, int maxMatchNum, int flag) {
	Mat dstImg(srcImg.size(), srcImg.type(), Scalar(255));
	int size = (int)contour.size();
	for (int i = 0; i < size; i++) {
		line(dstImg, contour[i], contour[(i + 1) % size], Scalar(0), 2);
		//circle(dstImg, contour[i], 3, Scalar(0), 2);
	}
	for (int i = maxBegin; i < maxBegin + maxMatchNum; i++) {
		if (flag == 0) {
			if (i == maxBegin) circle(dstImg, contour[i%size], 5, Scalar(100), 3);
			else circle(dstImg, contour[i%size], 3, Scalar(0), 2);
		}
		else {
			if (i == maxBegin + maxMatchNum - 1) circle(dstImg, contour[i%size], 5, Scalar(100), 3);
			else circle(dstImg, contour[i%size], 3, Scalar(0), 2);
		}
	}
	return dstImg;
}

*/

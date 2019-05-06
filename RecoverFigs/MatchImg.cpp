#include "header.h"

// contour1:		ͼһ�������Ϻ�˵�
// contour2:		ͼ���������Ϻ�˵�
//  ��ֵ:
// thresholdLen:	ƥ����󳤶Ȳ�
// thresholdDir:	ƥ�����ǶȲ�
//  ����������
// matchNum:		ƥ��ĵ�������
// matchLen:		ƥ�������ߵ��ܳ���
//  ����ֵ:			����ƥ��ĵ����� (����Ϊ���飬����һ��ƥ��ĵ���������һ��ƥ��ĵ����꣬ ���ڿɸ�����Ҫ�Ķ�)
vector<pair<Point, Point>> matchTwo(int & matchNum, double & matchLen, double & matchTheta, const vector<Point> & contour1,
						const vector<Point> & contour2, double thresholdLen, double thresholdDir, double thresholdAveDir)
{
	int size1 = (int)contour1.size();
	int size2 = (int)contour2.size();
	int minsize = min(size1, size2);
	vector<double> lens1;  // �����߳�������
	vector<double> lens2;
	vector<double> thetas1;  // �����ߵĽǶ�����
	vector<double> thetas2;
	// ���ζ� lens �� thetas ���г�ʼ��
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
	// Ȼ����� lens �� thetas ��ƥ��
	double maxMatchLen = 0; // �ƥ�䳤��
	double minAveTh = 1e10;  // ��С��ƽ��ƥ��Ƕ�
	int maxMatchNum = 0;  // ����ƥ�����
	int maxBegin1 = 0, maxBegin2 = 0; // ƥ��ĳ�ʼ�±�
	// ����ѭ������������
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
				// ƥ��Ļ�������
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
				//  ƥ����Ż�Ŀ�꣬ ����Ϊƥ�䳤�Ⱦ����ܳ���ͬʱƽ��ƥ��Ƕ�С��ĳ����ֵ
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
	// ����ƥ�䳤�Ⱥ�ƥ�����
	matchNum = maxMatchNum;
	matchLen = maxMatchLen;
	matchTheta = minAveTh;
	vector<pair<Point, Point>> pot_vec;
	if (maxMatchNum > 1) {
		pot_vec.resize(2);
		//// �ֱ��ʾ��һ��ƥ��ĵ�����һ��ƥ��ĵ�
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
	// ��󷵻ض���ƥ��ĵ�����
	return pot_vec;
}

// srcImg1, srcImg2 Ϊ��ƥ���ԭͼ�� ������һͨ���ģ����Ҷ�ͼ
// pot_vec Ϊ�ɹ�ƥ���Ķ���ƥ�������
// ������ƥ�䣬��Ż�true, ���� false
// ��װ�ú�����Ŀ����Ϊ���� �������ϵ� epsilong ������������Ӧ�� ȡ�����ƥ����Ǹ�����
bool matchImg(vector<pair<Point, Point>> & pot_vec, Mat srcImg1, Mat srcImg2, 
				const vector<double> & epsilon_vec, double thresholdTolLen) {
	Mat binImg1 = preSolveImg(srcImg1);
	Mat binImg2 = preSolveImg(srcImg2);
	vector<vector<Point>> contours1, contours2, curves1, curves2;
	vector<Point> curve1, curve2;
	extractContours(binImg1, contours1);
	extractContours(binImg2, contours2);
	// �����������ܳ��ȣ�����ֻȡ��һ������
	int maxMatchNum = 0;
	double maxMatchLen = 0;
	double minMatchTheta = 360;
	// �Կ��ܵ� epsilong ������٣��ҵ���õ��Ǹ�ƥ������
	for (auto epsilon : epsilon_vec) {
		approxPoly(curves1, contours1, epsilon);
		approxPoly(curves2, contours2, epsilon);
		int matchNum = 0;
		double matchLen = 0;
		double matchTheta = 360;
		// �����ܼٶ� curves ����ֻ��һ���������꣬������ڸ�����Ҫ���ԸĶ�
		vector<pair<Point, Point>> temp_vec = matchTwo(matchNum, matchLen, matchTheta, curves1[0], curves2[0]);
		if (matchNum > maxMatchNum || (matchNum == maxMatchNum && matchTheta < minMatchTheta)) {
			maxMatchNum = matchNum;
			maxMatchLen = matchLen;
			minMatchTheta = matchTheta;
			pot_vec = temp_vec;
			// �������ֵ�Լ� pot_vec
			curve1 = curves1[0];  // test !
			curve2 = curves2[0];
		}
	}
	if (maxMatchNum > 1) {
		double tolLen = min(arcLength(curve1, true), arcLength(curve2, true));

		////���Դ���
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

		// ���������������������ƥ��
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
	//����
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


	////���ƥ���
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

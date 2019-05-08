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
vector<pair<Point, Point>> matchTwo(int & matchNum, double & matchLen, double & matchTheta, double & matchPixDiff,
						const Mat & srcImg1, const Mat & srcImg2, const vector<Point> & contour1,const vector<Point> & contour2, 
						double thresholdLen, double thresholdDir, double thresholdAveDir, double thresholdAvePixDiff, int range)
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
	double minAvePixDiff = 1e10;  // ��Сƽ�����ز�
	int maxMatchNum = 0;  // ����ƥ�����
	int maxBegin1 = 0, maxBegin2 = 0; // ƥ��ĳ�ʼ�±�
	// ����ѭ������������
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			int num = 0;
			double lenNow = 0;
			double aveTh = 0;
			double avePixDiff = 0;
			for (int k = 0; k < minsize; k++) {
				double del_th = fabs(thetas1[(i + k) % size1] - thetas2[(j - k + size2) % size2]);
				del_th = min(del_th, 360 - del_th);
				double l1_1 = lens1[(i + k) % size1], l1_2 = lens2[(j - k + size2) % size2];
				double l2_1 = lens1[(i + k + 1) % size1], l2_2 = lens2[(j - k - 1 + size2) % size2];
				Point pot1 = contour1[(i + k) % size1], pot2 = contour2[(j - k + size2) % size2];
				int pix1 = minMatElemnet(srcImg1, pot1, range), pix2 = minMatElemnet(srcImg2, pot2, range);
				// ƥ��Ļ�������
				if (fabs(l1_1 - l1_2) / (l1_1 + l1_2) <= thresholdLen / 2 &&
					fabs(l2_1 - l2_2) / (l2_1 + l2_2) <= thresholdLen / 2 && del_th <= thresholdDir) {
					num++;
					lenNow += (l1_1 + l1_2 + l2_1 + l2_2) / 4;
					aveTh += del_th;
					avePixDiff += fabs(pix1 - pix2);
				}
				else {
					break;
				}
			}
			if (num > 1) {
				aveTh /= num;
				avePixDiff /= num;
				//  ƥ����Ż�Ŀ�꣬ ����Ϊƥ�䳤�Ⱦ����ܳ���ͬʱƽ��ƥ��Ƕ�С��ĳ����ֵ, ����ƽ��ƥ�����ز�С��ĳ����ֵ
				if (lenNow > maxMatchLen && aveTh < thresholdAveDir && avePixDiff < thresholdAvePixDiff) {
					maxMatchNum = num;
					maxMatchLen = lenNow;
					minAveTh = aveTh;
					minAvePixDiff = avePixDiff;
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
	matchPixDiff = minAvePixDiff;
	vector<pair<Point, Point>> pot_vec;
	if (maxMatchNum > 1) {
		pot_vec.resize(2);
		Point first_p1, last_p1, first_p2, last_p2; 
		first_p1 = contour1[maxBegin1];
		last_p1 = contour1[(maxBegin1 + maxMatchNum - 1) % size1];
		first_p2 = contour2[(maxBegin2 + maxMatchNum - 1) % size2];
		last_p2 = contour2[maxBegin2];
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
double matchImg(vector<pair<Point, Point>> & pot_vec, vector<vector<Point>> & contours1, vector<vector<Point>> & contours2, 
				const Mat & srcImg1, const Mat & srcImg2, const vector<double> & epsilon_vec, double thresholdTolLen) {
	//Mat binImg1 = preSolveImg(srcImg1);
	//Mat binImg2 = preSolveImg(srcImg2);
	//vector<vector<Point>> contours1, contours2, curves1, curves2;
	//vector<Point> curve1, curve2;
	//extractContours(binImg1, contours1);
	//extractContours(binImg2, contours2);
	vector<vector<Point>> curves1, curves2;
	vector<Point> curve1, curve2;
	int maxMatchNum = 0;
	double maxMatchLen = 0;
	double minMatchTheta = 360;
	double minMatchPixDiff = 255;
	// �Կ��ܵ� epsilong ������٣��ҵ���õ��Ǹ�ƥ������
	for (auto epsilon : epsilon_vec) {
		approxPoly(curves1, contours1, epsilon);
		approxPoly(curves2, contours2, epsilon);
		int matchNum = 0;
		double matchLen = 0;
		double matchTheta = 360;
		double matchPixDiff = 255;
		// �����ܼٶ� curves ����ֻ��һ���������꣬������ڸ�����Ҫ���ԸĶ�
		vector<pair<Point, Point>> temp_vec;
		temp_vec = matchTwo(matchNum, matchLen, matchTheta, matchPixDiff, srcImg1, srcImg2, curves1[0], curves2[0]);
		if (matchNum > maxMatchNum || (matchNum == maxMatchNum && matchLen > maxMatchLen)) {
			maxMatchNum = matchNum;
			maxMatchLen = matchLen;
			minMatchTheta = matchTheta;
			minMatchPixDiff = matchPixDiff;
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
		//	circle(img1, curve1[i], 3, Scalar::all(0), 2);
		//}
		//for (int i = 0; i < (int)curve2.size(); i++) {
		//	line(img2, curve2[i], curve2[(i + 1) % (int)curve2.size()], Scalar::all(0), 2);
		//	circle(img2, curve2[i], 3, Scalar::all(0), 2);
		//}
		//ellipse(img1, first_p1, Size(11, 7), 0, 0, 360, Scalar(50), 2);
		//ellipse(img1, last_p1, Size(7, 11), 0, 0, 360, Scalar(50), 2);
		//ellipse(img2, first_p2, Size(11, 7), 0, 0, 360, Scalar(50), 2);
		//ellipse(img2, last_p2, Size(7, 11), 0, 0, 360, Scalar(50), 2);
		////imshow("srcimg1", srcImg1);
		////imshow("srcimg2", srcImg2);
		//imshow("img1", img1);
		//imshow("img2", img2);
		//cout << "tolLen: " << tolLen << endl;
		//cout << "maxMatchNum: " << maxMatchNum << endl;
		//cout << "maxMatchLen: " << maxMatchLen << endl;
		//cout << "minMatchTheta: " << minMatchTheta << endl;
		//cout << "minMatchAvePixDiff: " << minMatchPixDiff << endl;

		//// ���������������������ƥ��
		if (maxMatchLen / tolLen <= thresholdTolLen) {
			return -1;
		}
		return maxMatchLen / tolLen;
	}
	return -1;
}

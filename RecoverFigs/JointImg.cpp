#include "header.h"


double isJoint(vector<pair<Point, Point>> & pot_vec, Mat srcImg1, Mat srcImg2) {
	Mat grayImg1, grayImg2;
	cvtColor(srcImg1, grayImg1, COLOR_BGR2GRAY);
	cvtColor(srcImg2, grayImg2, COLOR_BGR2GRAY);
	return matchImg(pot_vec, grayImg1, grayImg2);
}

// �Զ���ԭͼ�����ƴ�ӣ� ������ƴ�ӣ����ؿյ� Mat ����
// ����� srcImg Ϊ��ͨ��ͼ���� rgb ͼ
Mat jointTwo(const vector<pair<Point, Point>> & pot_vec, Mat & lastImg, Mat srcImg1, Mat srcImg2) {
	Point first_p1, last_p1, first_p2, last_p2;
	first_p1 = pot_vec[0].first;
	last_p1 = pot_vec[1].first;
	first_p2 = pot_vec[0].second;
	last_p2 = pot_vec[1].second;
	// �ֱ�õ� p1��p2 ֱ�ߵ���б��
	double theta1 = lineDirection(first_p1, last_p1);
	double theta2 = lineDirection(first_p2, last_p2);
	// �� srcImg ͼ����ת������ˮƽƴ��
	Mat dstImg1 = rotateImg(srcImg1, 90 - theta1, first_p1, last_p1);
	Mat dstImg2 = rotateImg(srcImg2, 90 - theta2, first_p2, last_p2);
	int com_rows = max(dstImg1.rows, dstImg2.rows), com_cols = dstImg1.cols + dstImg2.cols;
	Mat comImg1(com_rows, com_cols, CV_8UC3, Scalar::all(255)), comImg2(com_rows, com_cols, CV_8UC3, Scalar::all(255));
	// ˮƽ��չ���󣬵õ�������ȸ����� Mat �����Ա����ͼ�񲻻����
	dstImg1.copyTo(comImg1(Range(0, dstImg1.rows), Range(0, dstImg1.cols)));
	dstImg2.copyTo(comImg2(Range(0, dstImg2.rows), Range(dstImg1.cols, com_cols)));
	//hconcat(dstImg1, Mat(dstImg2.size(), dstImg2.type(), Scalar(255, 255, 255)), comImg1);
	//hconcat(Mat(dstImg1.size(), dstImg1.type(), Scalar(255, 255, 255)), dstImg2, comImg2);
	// ����ͼƬ1ƽ����ͼƬ2ˮƽƴ��ʱ�����λ������ ��ƽ��
	double mv_x = ((first_p2.x - first_p1.x) + (last_p2.x - last_p1.x)) / 2 + dstImg1.cols;
	double mv_y = ((first_p2.y - first_p1.y) + (last_p2.y - last_p1.y)) / 2;
	comImg2 = moveImg(comImg2, -mv_x, -mv_y);
	// �õ�������󣬲��� comImg1 ������ comImg �õ�����ƴ�Ӻ��ͼ��
	Mat mask = preSolveImg(comImg2);
	comImg2.copyTo(comImg1, mask);
	vector<Rect> rect_vec = detectTarget(comImg1);
	if (rect_vec.size() != 1) {
		cerr << "Error in rect_vec !" << endl;
		exit(-1);
	}
	// һ�������ֻ��һ������
	Mat comImg = normalizeImg(comImg1, rect_vec[0]);
	lastImg = normalizeImg(comImg2, rect_vec[0]);
		 
	//// ���Դ���
	//imshow("comImg1", comImg1);
	//imshow("comImg2", comImg2);
	//imshow("mask", mask);
	//imshow("comImg", comImg);
	//waitKey(0);

	return comImg;
}

//// �Զ����Ƭͼ�����ƴ�Ӹ�ԭ
//// img_vec Ϊ Mat���� �������� ����ֵΪһ��ƴ�Ӻ�� Mat ����
//Mat jointImg(vector<Mat> img_vec) {
//	if (img_vec.empty()) return Mat();
//	Mat dstImg = img_vec[0];
//	for (int i = 1; !dstImg.empty() && i < (int)img_vec.size(); i++) {
//		//imshow(to_string(i), dstImg);
//		//imwrite("data/qipa.png", dstImg);
//		dstImg = jointTwo(dstImg, img_vec[i]);
//
//	}
//	return dstImg;
//}

Mat jointImg(vector<Mat> img_vec) {
	if (img_vec.empty()) return Mat();
	set<int> img_nums;
	for (int i = 0; i < (int)img_vec.size(); i++) img_nums.insert(i);
	RNG rng(getTickCount());
	int randnum = rng.uniform(0, 1000) % img_vec.size();
	Mat dstImg = img_vec[randnum];
	Mat lastImg = dstImg;
	img_nums.erase(img_nums.find(randnum));
	cout << randnum << endl;
	while (!img_nums.empty()) {
		double maxMatchLen = -1;
		Mat tgtImg;
		int tgtnum;
		vector<pair<Point, Point>> pot_vec;
		for (auto num : img_nums) {
			vector<pair<Point, Point>> pot_tmp;
			Mat img = img_vec[num];
			double matchLen = isJoint(pot_tmp, lastImg, img);
			if (matchLen > maxMatchLen) {
				maxMatchLen = matchLen;
				tgtImg = img;
				tgtnum = num;
				pot_vec = pot_tmp;
			}
		}
		if (maxMatchLen <= 0) {
			cout << "end" << endl;
			return Mat();
		}
		img_nums.erase(img_nums.find(tgtnum));
		cout << tgtnum << endl;
		dstImg = jointTwo(pot_vec, lastImg, dstImg, tgtImg);
		imshow("lastImg", lastImg);
	}
	return dstImg;
}

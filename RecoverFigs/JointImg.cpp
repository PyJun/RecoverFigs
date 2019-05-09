#include "header.h"

// imgId1 ��飬 imgId2 ��С��
Mat jointTwo(Mat srcImg1, Mat srcImg2, pair<int,int> pair_id, set<int> & jointedIds, int size) {
	int imgId1 = pair_id.first, imgId2 = pair_id.second;
	Point first_p1 = matchers[imgId1][imgId2].first_p;
	Point last_p1 = matchers[imgId1][imgId2].last_p;
	Point first_p2 = matchers[imgId2][imgId1].first_p;
	Point last_p2 = matchers[imgId2][imgId1].last_p;
	// �ֱ�õ� p1��p2 ֱ�ߵ���б��
	double theta1 = lineDirection(first_p1, last_p1);
	double theta2 = lineDirection(first_p2, last_p2);
	double rot_th1 = (imgId1 > imgId2) ? 90 - theta1 : -90 - theta1;
	double rot_th2 = (imgId1 > imgId2) ? 90 - theta2 : -90 - theta2;
	// �� srcImg ͼ����ת������ˮƽƴ��
	jointedIds.insert(imgId1);
	Mat dstImg1 = rotateImg(srcImg1, rot_th1, first_p1, last_p1, jointedIds, size);
	Mat dstImg2 = rotateImg(srcImg2, rot_th2, first_p2, last_p2, set<int>{imgId2}, size);
	int com_rows = max(dstImg1.rows, dstImg2.rows), com_cols = dstImg1.cols + dstImg2.cols;
	Mat comImg1(com_rows, com_cols, CV_8UC3, Scalar::all(255)), comImg2(com_rows, com_cols, CV_8UC3, Scalar::all(255));
	// ˮƽ��չ���󣬵õ�������ȸ����� Mat �����Ա����ͼ�񲻻����
	dstImg1.copyTo(comImg1(Range(0, dstImg1.rows), Range(0, dstImg1.cols)));
	dstImg2.copyTo(comImg2(Range(0, dstImg2.rows), Range(0, dstImg2.cols)));
	//imshow("dstImg1", comImg1);
	//imshow("dstImg2", comImg2);

	//hconcat(dstImg1, Mat(dstImg2.size(), dstImg2.type(), Scalar(255, 255, 255)), comImg1);
	//hconcat(Mat(dstImg1.size(), dstImg1.type(), Scalar(255, 255, 255)), dstImg2, comImg2);
	// ����ͼƬ1ƽ����ͼƬ2ˮƽƴ��ʱ�����λ������ ��ƽ��
	double mv_x = ((first_p2.x - first_p1.x) + (last_p2.x - last_p1.x)) / 2;
	double mv_y = ((first_p2.y - first_p1.y) + (last_p2.y - last_p1.y)) / 2;
	comImg2 = moveImg(comImg2, -mv_x, -mv_y, first_p2, last_p2, set<int>{imgId2}, size);
	// �õ�������󣬲��� comImg1 ������ comImg �õ�����ƴ�Ӻ��ͼ��
	Mat mask = preSolveImg(comImg2);
	comImg2.copyTo(comImg1, mask);
	vector<Rect> rect_vec = detectTarget(comImg1);
	if (rect_vec.empty()) {
		//cerr << "Error: rect_vec empty!" << endl;
		return Mat();
	}
	// һ�������ֻ��һ������
	//imshow("comImg1", comImg1);
	jointedIds.insert(imgId2);
	Mat comImg = normalizeImg(comImg1, rect_vec[0], jointedIds, size);

	//// ���Դ���
	//imshow("comImg1", comImg1);
	//imshow("comImg2", comImg2);
	//imshow("mask", mask);
	//imshow("comImg", comImg);
	//waitKey(0);

	return comImg;
}


Mat jointImg(const vector<Mat> & img_vec, const vector<pair<int,int>> & imgPairs) {
	if (img_vec.empty() || imgPairs.empty()) return Mat();
	int size = (int)img_vec.size();
	set<int> jointedIds;
	int num1 = imgPairs[0].first, num2 = imgPairs[0].second;
	Mat dstImg = jointTwo(img_vec[num1], img_vec[num2], imgPairs[0], jointedIds, size);
	for (int i = 1; !dstImg.empty() && i < (int)imgPairs.size(); i++) {
		int imgNum = imgPairs[i].second;
		dstImg = jointTwo(dstImg, img_vec[imgNum], imgPairs[i], jointedIds, size);
	}
	return dstImg;
}

#include "header.h"

//const string DIR = "./data/";
const string DIR = "D:/codespace/python/人工智能/深度学习/碎片匹配/data/";
inline string getImgPath(int i) {
	return DIR + to_string(i) + string(".png");
}

vector<Mat> getImgVec(const vector<int> nums) {
	vector<Mat> img_vec;
	for (auto num : nums) {
		string img_path = getImgPath(num);
		Mat srcImg = imread(img_path, IMREAD_COLOR);
		if (!srcImg.empty()) {
			img_vec.push_back(srcImg);
		}
	}
	return img_vec;
}


// 这是二图拼接的主函数
int main(int argc, const char * argv) {
	string img_path1 = getImgPath(8);
	string img_path2 = getImgPath(9);
	//string img_path2 = "data/qipa.png";
	Mat srcImg1 = imread(img_path1, IMREAD_COLOR);
	Mat srcImg2 = imread(img_path2, IMREAD_COLOR);
	if (srcImg1.empty() || srcImg2.empty()) {
		cerr << "无法读取原图像" << endl;
		system("pause");
	}
	else {
		vector<pair<Point, Point>> pot_vec;
		if (isJoint(pot_vec, srcImg1, srcImg2) > 0) { 
			Mat lastImg;
			Mat mergedImg = jointTwo(pot_vec, lastImg, srcImg1, srcImg2);
			imshow(img_path1, srcImg1);
			imshow(img_path2, srcImg2);
			imshow("Merged Img", mergedImg);
			waitKey(0);
		}
		else {
			cout << "无法拼接！" << endl;
			system("pause");
		}
	}
	return 0;
}

/*
1
2
5
4
7
8
*/



//// 这个多图拼接的主函数
//int main(int argc, const char * argv) {
//	vector<Mat> img_vec = getImgVec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
//	Mat mergedImg = jointImg(img_vec);
//	if (!mergedImg.empty()) {
//		resize(mergedImg, mergedImg, Size(600, 600));
//		imshow("Merged Img", mergedImg);
//		waitKey(0);
//	} else {
//		cout << "无法拼接！" << endl;
//		waitKey(0);
//		system("pause");
//	}
//	return 0;
//}
//
//


//int main() {
//		RNG rng(getTickCount());
//		int rand = rng.uniform(0, 1000) % 9;
//		cout << rand << endl;
//		system("pause");
//		return 0;
//	}
//


//int main() {
//	string img_path1 = getImgPath(1);
//	string img_path2 = getImgPath(2);
//	Mat srcImg1 = imread(img_path1, IMREAD_COLOR);
//	Mat srcImg2 = imread(img_path2, IMREAD_COLOR);
//	vector<pair<Point, Point>> pot_vec;
//	Mat lastImg;
//	if (isJoint(pot_vec, srcImg1, srcImg2) > 0) { 
//		Mat mergedImg = jointTwo(pot_vec, lastImg, srcImg1, srcImg2);
//		imshow("srcImg1", srcImg1);
//		imshow("srdImg2", srcImg2);
//		imshow("lastImg", lastImg);
//		imshow("Merged Img", mergedImg);
//		waitKey(0);
//	}
//
//	system("pause");
//	return 0;
//}
//






















/*
int main(int argc, const char * argv) {
	Mat img1, img2, img3, img4, img5, edges;
	img1 = imread(imgpath, IMREAD_GRAYSCALE);
	if (img1.empty()) {
		cerr << imgpath << " is not existed!" << endl;
		system("pause");
		return -1;
	}
	resize(img1, img1, Size(512, 512));
	GaussianBlur(img1, img2, Size(3, 3), 0.1, 0.1);
	Canny(img2, edges, 10, 30, 3);
	Mat black(img2.size(), CV_8UC1, Scalar::all(0));
	img3.create(img2.size(), img2.type());
	img3 = Scalar::all(255);
	black.copyTo(img3, edges);
	Mat element1 = getStructuringElement(MORPH_ELLIPSE, Size(17, 17));
	Mat element2 = getStructuringElement(MORPH_ELLIPSE, Size(17, 17));
	morphologyEx(img3, img4, MORPH_OPEN, element1);
	morphologyEx(img4, img5, MORPH_CLOSE, element2);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(img5, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//GaussianBlur(img4, img4, Size(3, 3), 1, 1);
	vector<vector<Point>> curves(contours.size());

	Mat img6(img5.size(), img5.type(), Scalar(255));
	Mat img7(img6.size(), img6.type(), Scalar(255));
	int idx = 0;
	//for (; idx >= 0; idx = hierarchy[idx][0]) {
	//	drawContours(img6, contours, idx, Scalar(0), FILLED, 8, hierarchy);
	//}
	for (size_t i = 0; i < contours.size(); i++) {
		approxPolyDP(contours[i], curves[i], 1.28, true);
		//drawContours(img7, curves, i, Scalar(0), 2, 8);
		//for (size_t j = 0; j < contours[i].size(); j++) {
		//	line(img6, contours[i][j], contours[i][(j+1)%contours[i].size()], Scalar(0));
		//}
		//for (size_t j = 0; j < curves[i].size(); j++) {
		//	line(img7, curves[i][j], curves[i][(j+1)%curves[i].size()], Scalar(0));
		//}
	}

	imshow("lean原图", img1);
	//imshow("lena高斯滤波", img2);
	imshow("lena Canny算子", img3);
	imshow("lena 开运算", img4);
	imshow("lena 闭运算", img5);
	//imshow("lena 轮廓", img6);
	//imshow("lena 多边形轮廓", img7);

	for (auto v : hierarchy) {
		cout << v << endl;
	}
	for (auto vec : contours) {
		//for (auto p : vec) {
		//	cout << p.x << "," << p.y <<  " ";
		//}
		cout << vec.size() << endl;
	}
	cout << contours.size() << endl;
	//cout << contours[1].size() << endl;
	//cout << curves[1].size() << endl;

	waitKey(0);
	return 0;
}
*/

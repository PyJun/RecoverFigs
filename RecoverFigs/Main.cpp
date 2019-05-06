#include "header.h"

const string DIR = "./data/";
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


//// 这个多图拼接的主函数
//int main(int argc, const char * argv) {
//	vector<Mat> img_vec = getImgVec({ 1, 2, 3, 4});
//	Mat mergedImg = jointImg(img_vec);
//	if (!mergedImg.empty()) {
//		imshow("Merged Img", mergedImg);
//		waitKey(0);
//	} else {
//		cout << "无法拼接！" << endl;
//	}
//	system("pause");
//	return 0;
//}


// 这是二图拼接的主函数
int main(int argc, const char * argv) {
	string img_path1 = getImgPath(2);
	string img_path2 = getImgPath(3);
	Mat srcImg1 = imread(img_path1, IMREAD_COLOR);
	Mat srcImg2 = imread(img_path2, IMREAD_COLOR);
	if (srcImg1.empty() || srcImg2.empty()) {
		cerr << "无法读取原图像" << endl;
	} else {
		Mat mergedImg = jointTwo(srcImg1, srcImg2);
		if (!mergedImg.empty()) {
			imshow(img_path1, srcImg1);
			imshow(img_path2, srcImg2);
			imshow("Merged Img", mergedImg);
		} else {
			cout << "无法拼接！" << endl;
		}
		waitKey(0);
	}
	system("pause");
	return 0;
}

	































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


/*
void main()
{
	// Mat srcImg1 = imread("E:/money11111/2.jpg");
	// Mat srcImg2 = imread("E:/money11111/3.jpg");
	Mat srcImg1 = imread("D:/j计算机设计大赛/lena/3.png");
	Mat srcImg2 = imread("D:/j计算机设计大赛/lena/4.png");

	//imshow("1", srcImg1);
	//imshow("2", srcImg2);
	vector<vector<Point>> contours_poly1 = Function_approxPolyDP(srcImg1);
	vector<vector<Point>> contours_poly2 = Function_approxPolyDP(srcImg2);

	Mat dstImg1(srcImg1.size(), CV_8UC3, Scalar::all(0));
	Mat dstImg2(srcImg2.size(), CV_8UC3, Scalar::all(0));
	drawContours(dstImg1, contours_poly1, 0, Scalar(0, 255, 255), 1, 8);  //绘制

	drawContours(dstImg2, contours_poly2, 0, Scalar(0, 255, 255), 1, 8);  //绘制

	for (int i = 0; i < contours_poly1[0].size(); i++)
	{
		//dstImg1.at<Vec3b>(contours_poly1[0][i]) = Vec3b(255, 255, 255);
		ellipse(dstImg1, contours_poly1[0][i], Size(4, 4), 0, 0, 360, Scalar(255, 255, 255), 1);
	}
	for (int i = 0; i < contours_poly2[0].size(); i++)
	{
		ellipse(dstImg2, contours_poly2[0][i], Size(4, 4), 0, 0, 360, Scalar(255, 255, 255), 1);

	}
	imwrite("3.jpg", dstImg1);
	imwrite("4.jpg", dstImg2);
	imshow("3", dstImg1);
	imshow("4", dstImg2);

	double start = GetTickCount();

	double k = matchTwo(srcImg1, contours_poly1, srcImg2, contours_poly2, 5, 2, 10);
	double end = GetTickCount();
	cout << "GetTickCount:" << end - start << endl;
	cout << k << endl;

	waitKey(0);
}
*/
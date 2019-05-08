#include "header.h"

Matcher matchers[SIZE][SIZE];


int main(int argc, const char * argv) {
	vector<Mat> img_vec = getImgVec(getNums(4));
	Mat recImg;
	if (recoverImg(recImg, img_vec)) { 
		imshow("recoverImg", recImg);
		waitKey(0);
		imwrite(DIR + string("recoverImg.jpg"), recImg);
	} else {
		cout << "无法拼接!" << endl;
		system("pause");
	}
	return 0;
}


//int main() {
//	vector<Mat> img_vec = getImgVec({ 1, 2, 3, 4});
//	int size = (int)img_vec.size();
//	initMatchers(img_vec);
//	vector<pair<int,int>> pair_nums;
//	double tolMatch = imgPrime(pair_nums, size);
//	cout << tolMatch << endl;
//	for (auto pr : pair_nums) {
//		cout << pr.first << " " << pr.second << endl;
//	}
//	cout << endl;
//	system("pause");
//	return 0;
//}


//
//// 这是二图拼接的主函数
//int main(int argc, const char * argv) {
//	vector<Mat> img_vec = getImgVec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
//	int size = img_vec.size();
//	initMatchers(img_vec);
//	set<int> jointedIds;
//	Mat dstImg = img_vec[0];
//	dstImg = jointTwo(dstImg, img_vec[1], { 0, 1}, jointedIds, size);
//	dstImg = jointTwo(dstImg, img_vec[2], { 1, 2 }, jointedIds, size);
//	dstImg = jointTwo(dstImg, img_vec[3], { 0, 3 }, jointedIds, size);
//	imshow("Merged Img", dstImg);
//	waitKey(0);
//	return 0;
//}



//// 这是二图拼接的主函数
//int main(int argc, const char * argv) {
//	string img_path1 = getImgPath(2);
//	string img_path2 = getImgPath(1);
//	//string img_path2 = "data/qipa.png";
//	Mat srcImg1 = imread(img_path1, IMREAD_COLOR);
//	Mat srcImg2 = imread(img_path2, IMREAD_COLOR);
//	if (srcImg1.empty() || srcImg2.empty()) {
//		cerr << "无法读取原图像" << endl;
//		system("pause");
//	}
//	else {
//		vector<pair<Point, Point>> pot_vec;
//		double match = isJoint(pot_vec, srcImg1, srcImg2);
//		cout << match << endl;
//		if (match > 0) { 
//			Mat lastImg;
//			Mat mergedImg = jointTwo(pot_vec, lastImg, srcImg1, srcImg2);
//			imshow(img_path1, srcImg1);
//			imshow(img_path2, srcImg2);
//			imshow("Merged Img", mergedImg);
//			waitKey(0);
//		}
//		else {
//			cout << "无法拼接！" << endl;
//			system("pause");
//		}
//	}
//	return 0;
//}


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

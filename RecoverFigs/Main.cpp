#include "header.h"

Matcher matchers[SIZE][SIZE];
vector<vector<vector<Point>>> contours_vec;


////命令行调用的格式: 
//// RecoverFigs.exe inDir outFile
//// inDir 为碎片图像的目录， outFile 为输出图像的路径
//int main(int argc, const char * argv[]) {
//	//double t1 = (double)getTickCount();
//	const string dir = ((argc > 1) ? argv[1] : DIR) + "/";
//	vector<Mat> img_vec = getImgVec(getNums(9), dir);
//	Mat recImg;
//	if (recoverImg(recImg, img_vec)) { 
//		resize(recImg, recImg, Size(600, 600));
//		//double t2 = (double)getTickCount();
//		//cout << "耗时: " << (t2 - t1) / (getTickFrequency()) << " 秒" << endl;
//		if (argc <= 1) {
//			imshow("recoverImg", recImg);
//			waitKey(0);
//		}
//		if (argc > 2) {
//			imwrite(string(argv[2]), recImg);
//		} else {
//			imwrite(dir + string("recoverImg.jpg"), recImg);
//		}
//		return 0;
//	} else {
//		cout << "无法拼接!" << endl;
//		system("pause");
//		return -1;
//	}
//}


//int main() {
//	double c1 = 12, c2 = 36;
//	int ksize = 21;
//	string file = DIR + "/figs0.png";
//	Mat srcImg = imread(file, IMREAD_COLOR);
//	resize(srcImg, srcImg, Size(800, 600));
//	vector<Rect> rect_vec = detectTarget(srcImg, c1, c2, ksize);
//	vector<Mat> img_vec = extractTarget(srcImg, rect_vec, c1, c2, ksize);
//	cout << rect_vec.size() << endl;
//	for (auto & rt : rect_vec) {
//		rectangle(srcImg, rt, Scalar(255, 0, 0), 1);
//		cout << rt << endl;
//	}
//	int id = 1;
//	for (auto &img : img_vec) {
//		imwrite(DIR + "/" + to_string(id++) + ".png", img);
//	}
//	imshow("srcImg", srcImg);
//	waitKey(0);
//	//system("pause");
//	return 0;
//}




//int main() {
//	vector<Mat> img_vec = getImgVec(getNums(9));
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


////这是二图拼接的主函数
//int main(int argc, const char * argv[]) {
//	vector<Mat> img_vec = getImgVec({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
//	int size = img_vec.size();
//	initMatchers(img_vec);
//	set<int> jointedIds;
//	int id1 = 2, id2 = 4, id3 = 7;
//	cout << matchers[id1][id2].match << endl;
//	Mat dstImg = img_vec[id1];
//	dstImg = jointTwo(dstImg, img_vec[id2], { id1, id2}, jointedIds, size);
//	//dstImg = jointTwo(dstImg, img_vec[id3], { id2, id3 }, jointedIds, size);
//	//dstImg = jointTwo(dstImg, img_vec[3], { 0, 3 }, jointedIds, size);
//	imshow("Merged Img", dstImg);
//	waitKey(0);
//	return 0;
//}


//这是多图拼接的主函数
int main(int argc, const char * argv[]) {
	vector<Mat> img_vec = getImgVec({ 1, 2, 8, 9, 6, 7, 5, 3, 4});
	int size = img_vec.size();
	initMatchers(img_vec);
	set<int> jointedIds;
	Mat dstImg = img_vec[0];
	for (int i = 1; i < 6; i++) {
		dstImg = jointTwo(dstImg, img_vec[i], { i - 1, i }, jointedIds, size);
	}
	//dstImg = jointTwo(dstImg, img_vec[1], { 0, 1 }, jointedIds, size);
	//dstImg = jointTwo(dstImg, img_vec[2], { 1, 2 }, jointedIds, size);
	//dstImg = jointTwo(dstImg, img_vec[3], { 2, 3 }, jointedIds, size);
	//dstImg = jointTwo(dstImg, img_vec[4], { 3, 4 }, jointedIds, size);
	//dstImg = jointTwo(dstImg, img_vec[5], { 4, 5 }, jointedIds, size);

	dstImg = jointTwo(dstImg, img_vec[6], { 3, 6 }, jointedIds, size);
	dstImg = jointTwo(dstImg, img_vec[7], { 4, 7 }, jointedIds, size);
	dstImg = jointTwo(dstImg, img_vec[8], { 5, 8 }, jointedIds, size);

	imshow("Merged Img", dstImg);
	waitKey(0);
	return 0;
}



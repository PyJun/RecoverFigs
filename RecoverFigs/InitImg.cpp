#include "header.h"

inline string getImgPath(int i) {
	return DIR + to_string(i) + string(".png");
}

vector<int> getNums(int n) {
	vector<int> nums;
	for (int i = 1; i <= n; i++) {
		nums.push_back(i);
	}
	return nums;
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

void initMatchers(const vector<Mat> & img_vec) {
	int size = (int)img_vec.size();
	vector<pair<Point, Point>> pot_vec;
	Point first_p1, last_p1, first_p2, last_p2;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i && j < size; j++) {
			double match = isJoint(pot_vec, img_vec[i], img_vec[j]);
			first_p1 = pot_vec[0].first;
			last_p1 = pot_vec[1].first;
			first_p2 = pot_vec[0].second;
			last_p2 = pot_vec[1].second;
			matchers[i][j] = Matcher(first_p1, last_p1, match);
			matchers[j][i] = Matcher(first_p2, last_p2, match);
		}
	}
}


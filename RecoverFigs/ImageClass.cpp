//#include "header.h"
//
//Image::Image(const Mat & m, int id_, const pair<Point, Point> & pot_pair, Image * im_ptr) {
//	this->img = m;
//	this->id = id_;
//	this->matchers.emplace_back(pot_pair.first, pot_pair.second, im_ptr);
//}
//
//bool Image::normalize() {
//	vector<Rect> rect_vec = detectTarget(img);
//	if (rect_vec.size() != 1) {
//		cerr << "Error in rect_vec !" << endl;
//		return false;
//	}
//	// 一般情况下只有一个轮廓
//	Rect rect = rect_vec[0];
//	Mat dstImg = normalizeImg(img, rect);
//	double mv_x = rect.x + (rect.width - dstImg.cols) / 2;
//	double mv_y = rect.y + (rect.height - dstImg.cols) / 2;
//	moveMatchers(-mv_x, -mv_y);
//	this->img = dstImg;
//	return true;
//}
//
//
//void Image::rotateMatchers(Mat rot_mat) {
//	for (auto & match : matchers) {
//		rotatePoint(rot_mat, match.first_pot);
//		rotatePoint(rot_mat, match.last_pot);
//	}
//}
//
//void Image::moveMatchers(double x, double y) {
//	for (auto & match : matchers) {
//		movePoint(x, y, match.first_pot);
//		movePoint(x, y, match.last_pot);
//	}
//}
//
//void Image::rotate(double angle) {
//	Mat dstImg(img.size(), img.type(), Scalar::all(255));
//	Point2f center((float)dstImg.cols / 2, (float)dstImg.rows / 2);
//	Mat rot_mat = getRotationMatrix2D(center, angle, 1);
//	warpAffine(img, dstImg, rot_mat, Size(dstImg.cols, dstImg.rows), INTER_LINEAR, BORDER_CONSTANT, Scalar::all(255));
//	rotateMatchers(rot_mat);
//	this->img = dstImg;
//}
//
//void Image::move(double x, double y) {
//	Mat dstImg;
//	Mat mv_mat = Mat::zeros(2, 3, CV_64FC1);
//	mv_mat.at<double>(0, 0) = 1;
//	mv_mat.at<double>(0, 2) = x; //水平平移量
//	mv_mat.at<double>(1, 1) = 1;
//	mv_mat.at<double>(1, 2) = y; //竖直平移量
//	warpAffine(img, dstImg, mv_mat, img.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar::all(255));
//	moveMatchers(x, y);
//	this->img = dstImg;
//}
//

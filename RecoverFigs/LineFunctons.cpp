#include "header.h"

//�߶γ��Ⱥ����� ����ŷ����þ���
double lineLength(const Point & a, const Point & b) {
	double len = sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
	return len;
}

// �õ����� a->b ����б�ǣ���ʱ�뷽���� X ��ļн�
double lineDirection(const Point & a, const Point & b)
{
	double del_y = b.y - a.y;
	double del_x = b.x - a.x;
	double R = sqrt(del_x*del_x + del_y * del_y);
	double theta = acos(del_x / R);
	if (del_y > 0) {
		theta = 2 * PI - theta;
	}
	return theta / PI * 180;
}

// ���������Χ�ڻҶ�ͼ�е�����һ������
int minMatElemnet(const Mat & srcImg, Point pot, int range) {
	int width = 2 * min(range, srcImg.cols -1 - pot.x) + 1;
	int height = 2 * min(range, srcImg.rows -1 - pot.y) + 1;
	Mat dstImg = srcImg(Rect(max(pot.x - range, 0), max(pot.y - range, 0), width, height));
	int maxElem = 255;
	for (int i = 0; i < dstImg.rows; i++) {
		uchar * row_p = dstImg.ptr<uchar>(i);
		for (int j = 0; j < dstImg.cols; j++) {
			maxElem = min(maxElem, (int)row_p[j]);
		}
	}
	return maxElem;
}

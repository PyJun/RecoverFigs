#include "header.h"

//线段长度函数， 返回欧几里得距离
double lineLength(const Point & a, const Point & b) {
	double len = sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
	return len;
}

// 得到向量 a->b 的倾斜角，逆时针方向与 X 轴的夹角
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


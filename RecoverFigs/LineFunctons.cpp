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



















/*
//计算直线中点坐标
Point lineBaryCenter(const Point & a, const Point & b)
{
	Point bcenter;
	bcenter.x = (a.x + b.x) / 2;
	bcenter.y = (a.y + b.y) / 2;
	return bcenter;
}

//计算直线方向绝对theta角

//小线段特征矢量表述
vector<vector<Vec2i>> lineCharacter(vector<vector<Point>> Clusters, Mat srcImage)
{
	int lineLength(Point a, Point b);
	int lineAveGscale(Mat srcImage, Point a, Point b);
	vector<Vec2i> vec;
	vector<vector<Vec2i>> lineCharacter;
	lineCharacter.clear();
	int l, a;
	for (unsigned int i = 0; i < Clusters.size(); i++)
	{
		vec.clear();
		unsigned int j = 0;
		//计算起始点和终止点【间】形成线段得长度,平均灰度
		for (j; j < Clusters[i].size() - 1; j++)
		{
			l = lineLength(Clusters[i][j], Clusters[i][j + 1]);//计算直线欧几里得长度
			a = lineAveGscale(srcImage, Clusters[i][j], Clusters[i][j + 1]);//计算直线的平均灰度
			//a = cAvGscale(srcImage, cClusters(srcImage)[i][j]);
			vec.push_back(Vec2i(l, a));//将长度和平均灰度存入向量
		}
		// //计算【结束点和起始点构成】线段的长度，平均灰度
		//l = lineLength(Clusters[i][j], Clusters[i][0]);
		//a = lineAveGscale(srcImage, Clusters[i][j], Clusters[i][0]);
		//vec.push_back(Vec2i(l,a));
		lineCharacter.push_back(vec);
	}
	return lineCharacter;
}

//直线平均灰度函数
int lineAveGscale(Mat srcImage, Point a, Point b)
{
	//Mat dstImage;
	//dstImage.create(srcImage.size(), srcImage.type());//创建图像副本
	int nr = srcImage.rows;
	int nl = srcImage.cols*srcImage.channels();//合并三通道，row可能不连续因此不适用
	int count = 0, aveGScale = 0;
	//计算端点范围
	int max_y = (a.y > b.y) ? a.y : b.y;
	int min_y = (a.y < b.y) ? a.y : b.y;
	int max_x = (a.x > b.x) ? a.x : b.x;
	int min_x = (a.x < b.x) ? a.x : b.x;
	for (int k = 0; k < nr; k++)
	{
		const uchar* inData = srcImage.ptr<uchar>(k);
		//uchar*outData = dstImage.ptr<uchar>(k);//降阶，定义Data信息包含行数，故只需要标记列数即可


		for (int i = 0; i < nl; i++)
		{
			if (a.x == b.x)
			{
				if (k == a.x && (i <= max_y && i >= min_y))
				{
					aveGScale = aveGScale + inData[i];
					count++;
				}
			}
			else if (a.y == b.y)
			{
				if (i == a.x && (k <= max_x && k >= min_x))
				{
					aveGScale = aveGScale + inData[i];
					count++;
				}
			}
			//两点式描述直线方程，若点在直线段内则存入其灰度值
			else if ((i - a.y) / (b.y - a.y) == (k - a.x) / (b.x - a.x) && (i <= max_y && i >= min_y))
			{
				aveGScale = aveGScale + inData[i];
				count++;
			}
		}
	}
	if (count == 0) count = 1;
	return aveGScale = aveGScale / count;
}

*/

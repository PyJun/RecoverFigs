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



















/*
//����ֱ���е�����
Point lineBaryCenter(const Point & a, const Point & b)
{
	Point bcenter;
	bcenter.x = (a.x + b.x) / 2;
	bcenter.y = (a.y + b.y) / 2;
	return bcenter;
}

//����ֱ�߷������theta��

//С�߶�����ʸ������
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
		//������ʼ�����ֹ�㡾�䡿�γ��߶εó���,ƽ���Ҷ�
		for (j; j < Clusters[i].size() - 1; j++)
		{
			l = lineLength(Clusters[i][j], Clusters[i][j + 1]);//����ֱ��ŷ����ó���
			a = lineAveGscale(srcImage, Clusters[i][j], Clusters[i][j + 1]);//����ֱ�ߵ�ƽ���Ҷ�
			//a = cAvGscale(srcImage, cClusters(srcImage)[i][j]);
			vec.push_back(Vec2i(l, a));//�����Ⱥ�ƽ���Ҷȴ�������
		}
		// //���㡾���������ʼ�㹹�ɡ��߶εĳ��ȣ�ƽ���Ҷ�
		//l = lineLength(Clusters[i][j], Clusters[i][0]);
		//a = lineAveGscale(srcImage, Clusters[i][j], Clusters[i][0]);
		//vec.push_back(Vec2i(l,a));
		lineCharacter.push_back(vec);
	}
	return lineCharacter;
}

//ֱ��ƽ���ҶȺ���
int lineAveGscale(Mat srcImage, Point a, Point b)
{
	//Mat dstImage;
	//dstImage.create(srcImage.size(), srcImage.type());//����ͼ�񸱱�
	int nr = srcImage.rows;
	int nl = srcImage.cols*srcImage.channels();//�ϲ���ͨ����row���ܲ�������˲�����
	int count = 0, aveGScale = 0;
	//����˵㷶Χ
	int max_y = (a.y > b.y) ? a.y : b.y;
	int min_y = (a.y < b.y) ? a.y : b.y;
	int max_x = (a.x > b.x) ? a.x : b.x;
	int min_x = (a.x < b.x) ? a.x : b.x;
	for (int k = 0; k < nr; k++)
	{
		const uchar* inData = srcImage.ptr<uchar>(k);
		//uchar*outData = dstImage.ptr<uchar>(k);//���ף�����Data��Ϣ������������ֻ��Ҫ�����������


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
			//����ʽ����ֱ�߷��̣�������ֱ�߶����������Ҷ�ֵ
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

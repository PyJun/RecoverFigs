#include "header.h"

double max_match[SIZE];
bool visited[SIZE];
int pre_nums[SIZE];

// Prime �㷨�������������ͼ�е���С������
// ���������ͼƬ���㼯�е����ƥ��ϵ������Ӧ������
double imgPrime(vector<pair<int,int>> & pair_nums, int size, int start) {
	fill(max_match, max_match+SIZE, -1);
	memset(visited, false, sizeof(visited));
	double ans = 0;
	max_match[start] = 0;
	pair_nums.clear();
	for (int i = 0; i < size; i++) {
		int u = -1;
		double match = -1;
		for (int j = 0; j < size; j++) {
			if (!visited[j] && max_match[j] > match) {
				match = max_match[j];
				u = j;
			}
		}
		if (u == -1) return -1;
		visited[u] = true;
		ans += max_match[u];
		for (int v = 0; v < size; v++) {
			if (!visited[v] && matchers[u][v].match > max_match[v]) {
				max_match[v] = matchers[u][v].match;
				pre_nums[v] = u;
			}
		}
		if (u != start) pair_nums.emplace_back(pre_nums[u], u);
	}
	return ans;
}


// ��ԭͼ��
bool recoverImg(Mat & dstImg, const vector<Mat> & img_vec) {
	int size = (int)img_vec.size();
	initMatchers(img_vec);
	vector<pair<int, int>> pair_nums;
	double tolMatch = imgPrime(pair_nums, size);
	if (tolMatch <= 0) return false;
	dstImg = jointImg(img_vec, pair_nums);
	if (dstImg.empty()) return false;
	vector<Rect> rect_vec = detectTarget(dstImg);
	if ((int)rect_vec.size() != 1) return false;
	dstImg = normalizeImg(dstImg, rect_vec[0]);
	return true;
}



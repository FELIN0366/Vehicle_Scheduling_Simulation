//map:知道整张地图，获取点与点之间的最短路径
#pragma once

#include<vector>
#include"utility.h"

using namespace std;


class Map {
public:
	Map();
	//~Map();
	//void site_acquisition();//获取站点
	void graph_creation();//创建无向图
	vector<vector<vector<int>>> Get_Path();
	vector<vector<int>> Get_Distance();
	//void dijkstra(int k, vector<int>& outcome, vector<int>& dis, int n); //使用迪杰斯特拉算两点之间的最短路径，并将其储存起来

private:
	int num_node;//站点数量
	vector<vector<vector<int>>>Path;//a[i][j]代表以i为出发点，到达j所经过的最短站点路径点
	vector<vector<int>> Distance;//a[i][j]代表以i为出发点，到达j所经过的最短路径值
	vector<vector<int>>graph;
};
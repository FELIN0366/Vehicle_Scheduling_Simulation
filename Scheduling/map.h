//map:֪�����ŵ�ͼ����ȡ�����֮������·��
#pragma once

#include<vector>
#include"utility.h"

using namespace std;


class Map {
public:
	Map();
	//~Map();
	//void site_acquisition();//��ȡվ��
	void graph_creation();//��������ͼ
	vector<vector<vector<int>>> Get_Path();
	vector<vector<int>> Get_Distance();
	//void dijkstra(int k, vector<int>& outcome, vector<int>& dis, int n); //ʹ�õϽ�˹����������֮������·���������䴢������

private:
	int num_node;//վ������
	vector<vector<vector<int>>>Path;//a[i][j]������iΪ�����㣬����j�����������վ��·����
	vector<vector<int>> Distance;//a[i][j]������iΪ�����㣬����j�����������·��ֵ
	vector<vector<int>>graph;
};
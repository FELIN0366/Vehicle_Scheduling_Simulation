#include <stdio.h>
#include<vector>
#include<iostream>
#include"map.h"
#define V 9    //�趨ͼ�еĶ�����
#define INF 99999   // ����һ�����ֵ
using namespace std;

Map::Map() :Distance(10, vector<int>(10)), Path(10,vector<vector<int>>(10,vector<int>(10))) {
    this->num_node = 9;
}

vector<vector<vector<int>>> Map::Get_Path() {
    return this->Path;
}

vector<vector<int>> Map::Get_Distance() {
    return this->Distance;
}

// ����ݹ������������֮�����·���ľ�����·
void printPath(int i, int j, int D_i, int D_j, vector<vector<int>>& Point, vector<vector<vector<int>>>& Path, int P[][V])
{
    int k = P[i][j];
    if (k == 0)
        return;
    printPath(i, k, D_i, D_j, Point, Path, P);
    // printf("%d-", k + 1);
    int pointer = Point[D_i + 1][D_j + 1];
    Path[D_i + 1][D_j + 1][pointer] = k + 1;
    Point[D_i + 1][D_j + 1]++;
    printPath(k, j, D_i, D_j, Point, Path, P);
}

// �����������֮������·��
void printMatrix(int graph[][V], vector<vector<int>>& Point, vector<vector<vector<int>>>& Path, int P[][V]) {
    int i, j;
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (j == i) {
                continue;
            }
            //printf("%d - %d: ���·��Ϊ:", i + 1, j + 1);
            if (graph[i][j] == INF) {
                // printf("%s\n", "INF");
            }
            else {
                // printf("%d", graph[i][j]);
                // printf("�����ξ�����%d-", i + 1);
                Path[i + 1][j + 1][0] = i + 1;
                Point[i + 1][j + 1]++;
                //���õݹ麯��
                printPath(i, j, i, j, Point, Path, P);
                // printf("%d\n", j + 1);
                int pointer = Point[i + 1][j + 1];
                Path[i + 1][j + 1][pointer] = j + 1;
            }
        }
    }
}

//��ͼ
void Map::graph_creation(){
    // �����Ȩͼ�и�������֮���·����Ϣ
    int graph[V][V] = { {0,INF,INF,110,70,INF,50,INF,INF},
                          {INF,0,100,INF,INF,INF,INF,INF,150},
                          {INF,100,0,50,INF,INF,INF,INF,INF},
                          {INF,INF,50,0,50,70,INF,INF,INF},
                          {70,INF,INF,50,0,50,50,INF,INF} ,
                          {INF,INF,INF,70,50,0,INF,50,70} ,
                          {50,INF,INF,INF,50,INF,0,50,INF} ,
                          {INF,INF,INF,INF,INF,50,50,0,50} ,
                           {INF,150,INF,INF,INF,70,INF,50,0} };
    
    //floydWarshall(graph);
    int  i, j, k;
    int P[V][V] = { 0 }; //��¼��������֮������·��
    //����ÿ�����㣬������Ϊ��������֮����м䶥�㣬���� graph ����
    vector<vector<int>>Point(10, vector<int>(10));
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                //����µ�·����֮ǰ��¼�ĸ��̣������ graph ����
                if (graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    //this->Distance[i+1][j+1] = graph[i][j];��������
                    //��¼��·��
                    P[i][j] = k;
                }
            }
        }
    }
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            this->Distance[i + 1][j + 1] = graph[i][j];
    // �����������֮������·��
    printMatrix(graph, Point,this->Path,P);
}

#include <stdio.h>
#include<vector>
#include<iostream>
#include"map.h"
#define V 9    //设定图中的顶点数
#define INF 99999   // 设置一个最大值
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

// 中序递归输出各个顶点之间最短路径的具体线路
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

// 输出各个顶点之间的最短路径
void printMatrix(int graph[][V], vector<vector<int>>& Point, vector<vector<vector<int>>>& Path, int P[][V]) {
    int i, j;
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (j == i) {
                continue;
            }
            //printf("%d - %d: 最短路径为:", i + 1, j + 1);
            if (graph[i][j] == INF) {
                // printf("%s\n", "INF");
            }
            else {
                // printf("%d", graph[i][j]);
                // printf("，依次经过：%d-", i + 1);
                Path[i + 1][j + 1][0] = i + 1;
                Point[i + 1][j + 1]++;
                //调用递归函数
                printPath(i, j, i, j, Point, Path, P);
                // printf("%d\n", j + 1);
                int pointer = Point[i + 1][j + 1];
                Path[i + 1][j + 1][pointer] = j + 1;
            }
        }
    }
}

//建图
void Map::graph_creation(){
    // 有向加权图中各个顶点之间的路径信息
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
    int P[V][V] = { 0 }; //记录各个顶点之间的最短路径
    //遍历每个顶点，将其作为其它顶点之间的中间顶点，更新 graph 数组
    vector<vector<int>>Point(10, vector<int>(10));
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                //如果新的路径比之前记录的更短，则更新 graph 数组
                if (graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    //this->Distance[i+1][j+1] = graph[i][j];（？？）
                    //记录此路径
                    P[i][j] = k;
                }
            }
        }
    }
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            this->Distance[i + 1][j + 1] = graph[i][j];
    // 输出各个顶点之间的最短路径
    printMatrix(graph, Point,this->Path,P);
}

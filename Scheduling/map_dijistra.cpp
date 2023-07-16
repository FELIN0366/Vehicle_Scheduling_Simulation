#include "map.h"
#include<vector>
#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>
#include<stdlib.h>

/*
void doit(int x, int y, int val, int cur, int* head) {
    son[cur].next = head[x];
    son[cur].val = val;
    son[cur].to = y;
    head[x] = cur;
    //std::cout << cur << " " << son[cur].val << " " << son[cur].to << " " << son[cur].next << " " << head[x];
    return;
    //head是否会被修改
}
*/

Map::Map() {
    for (int i = 0; i < 50;++i)
        this->head[i] = 0;
    this->num_node = 0;
}

void Map::site_acquisition() {
    // csv文件里储存的是 点*2+val*1
    ifstream fp("C:\\Users\\20216\\Desktop\\net.csv");
    string line;
    int cur = -1;
    int count = 0;
    while (getline(fp, line)) {
        istringstream readstr(line);
        int x, y, val;
        for (int i = 0; i < 3; i++) {
            std::string number;
            std::getline(readstr, number, ',');
            if (i == 0) { x = atoi(number.c_str()); }
            if (i == 1) { y = atoi(number.c_str()); }
            if (i == 2) { val = atoi(number.c_str()); }
        }
        cur++;
        //doit(x, y, val, cur,this->head);
        this->son[cur].next = head[x];
        this->son[cur].val = val;
        this->son[cur].to = y;
        cur++;
        //doit(y, x, val, cur,this->head);
        this->son[cur].next = head[y];
        this->son[cur].val = val;
        this->son[cur].to = x;
        if (x > count) count = x;
        if (y > count) count = y;
    }
    this->num_node = count;
}

/*
void dijkstra(int k, vector<int>& outcome, vector<int>& dis, int n,int *head) {
    int flag[50];
    int ans[50];
    for (int i = 0; i < 50; i++) {
        flag[i] = 0; ans[i] = 9999999;
    }
    flag[k] = 1;
    ans[k] = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = head[k]; j != -1; j = son[j].next) {
            if (ans[son[j].to] > ans[k] + son[j].val && flag[son[j].to] == 0)
                ans[son[j].to] = ans[k] + son[j].val;
            std::cout << ans[son[j].to] << " " << ans[k] << " " << son[j].val << " " << son[j].next << endl;
        }
        int minn = 99999;
        for (int j = 1; j <= n; j++) {
            if (ans[j] < minn && flag[j] == 0) {
                minn = ans[j];
                k = j;
            }
        }
        flag[k] = 1;
        outcome.push_back(k);
        dis.push_back(ans[k]);
    }
}*/

void Map::graph_creation() {
    for (int i = 1; i <= this->num_node; ++i) {
        vector<int> outcome;
        vector<int>dis;

        //dijkstra(i, outcome, dis, this->num_node,this->head);
        int *flag=new int [50];
        int *ans=new int[50];
        int k = i;
        int n = this->num_node;

        for (int j = 0; j < 50; j++) {
            flag[j] = 0; ans[j] = 9999999;
        }

        flag[k] = 1;
        ans[k] = 0;

        for (int i = 1; i < n; ++i) {
            for (int j = head[k]; j != -1; j = this->son[j].next) {
                if (ans[this->son[j].to] > ans[k] + this->son[j].val && flag[this->son[j].to] == 0)
                    ans[this->son[j].to] = ans[k] + this->son[j].val;
                std::cout << ans[this->son[j].to] << " " << ans[k] << " " << this->son[j].val << " " << this->son[j].next << endl;
            }
            int minn = 99999;
            for (int j = 1; j <= n; j++) {
                if (ans[j] < minn && flag[j] == 0) {
                    minn = ans[j];
                    k = j;
                }
            }
            flag[k] = 1;
            outcome.push_back(k);
            dis.push_back(ans[k]);
        }
        //dijkstra end;

        this->Path.push_back(outcome);
        this->Distance.push_back(dis);
        outcome.clear();
        dis.clear();
    }
}

vector<vector<int>> Map::Get_Path() {
    return this->Path;
}

vector<vector<int>> Map::Get_Distance() {
    return this->Distance;
}
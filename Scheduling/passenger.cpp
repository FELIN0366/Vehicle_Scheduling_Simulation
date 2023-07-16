#include"passenger.h"
#include"utility.h"
#include<vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include<string>
using namespace std;


Passenger_List::Passenger_List() {
	this->Sum_Passenger_Num = 0;
	Passenger_info.clear();
}

Passenger_List::~Passenger_List() {
	vector<Quest*>::iterator it;
	for (it = Passenger_info.begin(); it != Passenger_info.end(); it++)
		delete (*it);
}

//预处理：
//随机生成csv文件(一轮里所有顾客请求 略大于车辆数量3-5）
void Passenger_List::Generate_passenger_info()
{
	ofstream outFile;
	outFile << "passenger_id" << ',' << "start_position" << ',' << "destination" << endl;
	int passenger_num = 0;
	unsigned seed;
	seed = time(0);
	srand(seed);
	passenger_num = rand() % (25 - 15 + 1) + 30;
	outFile.open("passenger_list.csv", ios::out);
	for (int i = 1; i < passenger_num + 1; )
	{
		int start_position = 0;
		int destination = 0;
		start_position = rand() % (9 - 1 + 1) + 1;
		destination = rand() % (9 - 1 + 1) + 1;
		if (start_position == destination)
		{
			i = i;
			continue;
		}
		else
		{
			//outFile.open("passenger_list.csv", ios::out);
			outFile << i << ',' << start_position << ',' << destination << endl;
			i = i + 1;
		}

	}
	outFile.close();
}

//局部函数：获取最短路径将会经过的站点（使用策略三的时候将会对此进行更改）
void get_NumSite(Quest* x, vector<vector<vector<int>>>Path) {
	//vector<vector<int>>Path = SL_Map.Get_Path();
	vector<int>::iterator it;
	int val1 = 0;
	for (it = Path[x->startPos][x->endPos].begin(); it != Path[x->startPos][x->endPos].end(); ++it) {
		if (*it == x->endPos) break;
		else val1++;
	}
	x->Num_Site = val1;
	return;
}

//读入每个乘客的信息（出发地、目的地）-->放入请求
vector<Quest*> Passenger_List::Read_passenger_info(vector<vector<vector<int>>>Path)
{	
	FILE* fp;
	//vector<Quest*> passenger_info;
	errno_t err;
	err = fopen_s(&fp, "passenger_list.csv", "r");//文件路径(没打全的）
	while (1)
	{	
		if (feof(fp)) break;
		Quest* Request = new Quest();
		fscanf(fp, "%d,%d,%d", &(Request->id), &(Request->startPos), &(Request->endPos));
		if (Request->endPos == 0) continue;
		get_NumSite(Request, Path);
		this->Passenger_info.push_back(Request);
		
	}
	if (fp == NULL) //无该条件判断将会出现警告Warning C6387
	{
		this->Passenger_info.clear();
		return this->Passenger_info;
	}
	fclose(fp);
	this->Sum_Passenger_Num = this->Passenger_info.size();
	return this->Passenger_info;
	//Felin：？？？我的return去了哪里？？
	// jyw:好了我给你return回去了！！（你打的字比打一行return还长！）
	//Felin: is_quest, WaitingTime, RidingPath需要重置
}

//每一轮开始的时候对车辆进行初始化
void Passenger_List::Utilize_Passenger_Info() {
	//Felin:这干什么的？？
	ofstream fileout("passenger_list.csv", ios_base::out);//ios::trunc是清除原文件内容,可不写,默认就是它
	if (!fileout) {
		cout << "Clear successfully!\n";
		exit(0);
	}
	fileout.close();
	vector<Quest*> ::iterator it;
	for (it = this->Passenger_info.begin(); it != this->Passenger_info.end(); it++) {
		delete (*it);
	}
	this->Passenger_info.clear();
	this->Sum_Passenger_Num = 0;
}
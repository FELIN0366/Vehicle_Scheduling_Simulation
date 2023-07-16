#pragma once
#include <iostream>
#include <cstdlib> 
#include <ctime>
#include"map.h"
#include"utility.h"
#include<vector>

//记录每一分钟乘客信息
class Passenger_List {
public:
	Passenger_List();
	~Passenger_List();
	//预处理：
	//随机生成csv文件(一轮里所有顾客请求 略大于车辆数量3-5）
	void Generate_passenger_info();
	//读入每个乘客的信息（出发地、目的地）-->放入请求
	vector<Quest*> Read_passenger_info(vector<vector<vector<int>>>Path);
	//更新一轮中的各种信息
	void Utilize_Passenger_Info();

private:
	std::vector<Quest*> Passenger_info;//一轮里所有乘客信息
	int Sum_Passenger_Num;//一轮里（随机数生成某范围里的数）

};

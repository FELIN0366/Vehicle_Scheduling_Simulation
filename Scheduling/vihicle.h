#pragma once 

#include<vector>
#include"utility.h"

//一轮内车的信息
class Vehicle_List {
public:
	Vehicle_List();
	~Vehicle_List();
	//更新数据（一轮是指所有汽车都停止的情况），下一轮的初始化（已经转走）
	std::vector<Each_Car*> Get_Car_Info();
	//更新车辆信息
	void Utilize_Car_Info();

private:
	std::vector<Each_Car*> Car_info;//每轮里所有车的信息 一轮完后更新
	//一定要传地址 不然没有办法更新
	int Car_Amount;
};

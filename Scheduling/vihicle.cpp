#include"vihicle.h"
#include"utility.h"
//#include"map.h"
#include<vector>
#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>
#include<stdlib.h>
using namespace std;

//车12辆，每辆车的起始位置已知

//未开始模拟前对车辆的初始位置进行读取(capacity,custnum,current-position
Vehicle_List::Vehicle_List() {
	this->Car_Amount = 12;
	Car_info.clear();
	ifstream fp("Vihicle_Initialization.csv");
	string line;
	getline(fp, line);
	while (getline(fp, line)) {
		istringstream readstr(line);
		Each_Car* temp = new Each_Car();//内部已经做好了初始化
		for (int i = 0; i <= 2; i++) {
			std::string number;
			std::getline(readstr, number, ',');
			if (i == 0) { temp->capacity = atoi(number.c_str()); }
			if (i == 1) { temp->custNum = atoi(number.c_str()); }
			if (i == 2) { temp->current_position = atoi(number.c_str()); }
		}
		this->Car_info.push_back(temp);
	}
}

Vehicle_List::~Vehicle_List() {
	vector<Each_Car*>::iterator it;
	for (it = Car_info.begin(); it != Car_info.end(); it++)
		delete (*it);
}

//删除并更新数据（所有车都停止）
void Vehicle_List::Utilize_Car_Info() {
	vector<Each_Car*> ::iterator it;
	for (it = this->Car_info.begin(); it != this->Car_info.end(); it++) {
		(* it)->current_position = (*it)->determination;
		(*it)->tobeTravelled.clear();
		(*it)->Pick_Passenger.clear();
		(*it)->custNum = 0;
		(*it)->determination = 0;
	}
}

//获取起始点（每轮一次）
std::vector<Each_Car*> Vehicle_List::Get_Car_Info() {
	return this->Car_info;
}

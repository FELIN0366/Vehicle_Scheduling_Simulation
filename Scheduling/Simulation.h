#ifndef Simulator
#define Simulator
#include<vector>
#include "vihicle.h"
#include "utility.h"
//一轮定义：每产生一次订单为一轮
class Simulator {
public:
	Simulator();
	~Simulator();
	void runSinulate() {
		for (int i = 1; i <= 1440; i++)
		{
			//生成用户请求
			//读入此时的车辆状态
			//进行匹配
			//数据更新
			//输出结果
		}
	}
	void get_car();//得到车辆信息（调用vihicle里的函数）
	void get_passenger();//得到用户信息
};
#endif
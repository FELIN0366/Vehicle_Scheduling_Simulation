# pragma once

#include <vector>
#include "vihicle.h"
#include "utility.h"

class Allocation {
public:
	~Allocation();
	void Str_One(const std::vector<std::vector<std::vector<int>>>& Path, const std::vector<std::vector<int>>& Distance, std::vector<Each_Car*>& Car_Info, std::vector<Quest*>& Passenger_Info);//返回匹配策略一接单数
	void Str_Two(const std::vector<std::vector<std::vector<int>>>& Path, const std::vector<std::vector<int>>& Distance, std::vector<Each_Car*>& Car_Info, std::vector<Quest*>& Passenger_Info);//返回策略二的接单数
	void Str_Three(const std::vector<std::vector<std::vector<int>>>& Path, const std::vector<std::vector<int>>& Distance, std::vector<Each_Car*>& Car_Info, std::vector<Quest*>& Passenger_Info);//返回策略三
	void Outcome(const std::vector<Each_Car*>& Car_Info, int minute, int plan);//返回并输出结果
	void TotalOutcome();
private:
	std::vector<int>Cus_One;
	std::vector<int>Cus_Three;
};

//以轮次为单位进行匹配

/*匹配策略--拼单策略：【优势：走最短路径】
1、在满足所有乘客最短路径需求的同时进行拼单
步骤：
1.就经过站点数由大到小排列
2.一辆辆车寻找离车最近的且途径站点最多的订单a
（跳出条件：找到较近站点or该轮订单全部结束）
3.由a做匹配项，寻找有无a的子集
（终止条件是：1.满4个订单 2.该轮乘客匹配完 3、车辆匹配完）
*/

//匹配策略二--不拼单策略： 暴力解法：一车接一单

/*
策略三--拼单策略：【优势：拼车为王】
1、满足前两个站点在形式路径内，则加入拼车大军
步骤：
1、对乘客的最短路径经过站点数从大到小排列
2、一辆辆车寻找离车最近的且途径站点最多的订单a
（跳出条件：找到较近站点or该轮订单全部结束）
3、多次循环，做车辆c的匹配项，若乘客b的最短形式路径的前2个点在c的行驶路径内，则接上，
并更改c的形式路径。
（跳出条件：若所有车辆的载客人数已满）
【接送顺序：若为完全子集关系，则先站点数小的先下；若非子集关系，则先上先下】
*/
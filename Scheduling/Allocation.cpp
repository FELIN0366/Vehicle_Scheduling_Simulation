/*匹配策略--拼单策略：【优势：走最短路径】
1、在满足所有乘客最短路径需求的同时进行拼单
步骤：
1.就经过站点数由大到小排列
2.一辆辆车寻找离车最近的且途径站点最多的订单a
（跳出条件：找到较近站点or该轮订单全部结束）
3.由a做匹配项，寻找有无a的子集
（终止条件是：1.满4个订单 2.该轮乘客匹配完 3、车辆匹配完）
*/

#include <iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include"Allocation.h"
using namespace std;

Allocation::~Allocation() {
	this->Cus_One.clear();
	this->Cus_Three.clear();
}
//strOne 部分
bool cmp(Quest* x, Quest* y) {
	if (x->Num_Site > y->Num_Site) return true;
	else return false;
}
//该乘客是否在车辆的形式路径当中（全包含）
int is_in_path(Quest cus, Each_Car* car) {
	int flag = 0;
	int count = 0;
	vector<int>::iterator it;
	for (it = car->tobeTravelled.begin(); it != car->tobeTravelled.end(); ++it) {
		if (flag == 0) count++;
		if (*it == cus.startPos) flag = 1;
		if (flag == 1 && (*it) == cus.endPos) return count;
	}
	return -1;
}
//所有乘客都被接上
bool All_Passenger_Pick(vector<Quest*>& Passenger_Info) {
	//vector<Quest> Passenger_Info = SL_Passenger_List.Read_passenger_info();
	vector<Quest*>::iterator it;
	for (it = Passenger_Info.begin(); it != Passenger_Info.end(); ++it) {
		if ((*it)->is_quest == 0) return false;
	}
	return true;
}
//所有汽车都在工作
bool All_Car_Work(vector<Each_Car*>& Car_Info) {
	//vector<Each_Car*> Car_Info = SL_Vehicle_List.Get_Car_Info();
	vector<Each_Car*>::iterator it;
	for (it = Car_Info.begin(); it != Car_Info.end(); ++it) {
		if ((*it)->determination == 0) return false;
	}
	return true;
}
//寻找该车辆的最近点
int Find_Nearest_Point(const vector<vector<int>>& Distance, int Point, int count) {
	vector<int>NP;//最近的点从大到小排序
	for (int i = 0; i < Distance[Point].size(); i++) {
		if(Distance[Point][i]!=0) NP.push_back(Distance[Point][i]);
	}
	sort(NP.begin(), NP.end());//从小到大排序
	int val = NP[count];
	//count==0 -》找到最小的
	for (int i = 0; i < Distance[Point].size(); i++) {
		if (Distance[Point][i] == val) {
			return i;
		}
	}
	//return NP[NP.size() - 1 - count];
}

void Update_Car_Info_One(Each_Car* car, int next_pos, Quest* passenger, const std::vector<std::vector<std::vector<int>>>& Path) {
	//看车辆列表中的数据是否修改
	if (car->custNum == car->capacity) {
		cout << "错误加入！";
		return;
	}
	car->custNum++;
	car->Pick_Passenger.push_back(passenger);

	if (car->determination == 0) {
		car->determination = next_pos;
		for (int i = 0; i < Path[car->current_position][car->determination].size(); i++) {
			int point = Path[car->current_position][car->determination][i];
			if (point == 0) break;
			else car->tobeTravelled.push_back(point);
		}
	}
	return;
}

// 更新一轮中的各种信息
void Update_Passenger_Info_One(Quest* Passenger, int dis, const std::vector<std::vector<std::vector<int>>>& Path) {
	Passenger->is_quest = 1;
	//车和人的距离+人进入第X轮的时间(车辆的速度是多少？）
	Passenger->WaitingTime = dis / 5;//speed;

	//从startPos走到endPos
	for (int i = 0; i < Path[Passenger->startPos][Passenger->endPos].size(); ++i) {
		int point = Path[Passenger->startPos][Passenger->endPos][i];
		if (point == 0) break;
		else Passenger->RidingPath.push_back(point);
	}
}
void Allocation::Str_One(const vector<vector<vector<int>>>& Path, const vector<vector<int>>& Distance, vector<Each_Car*>& Car_Info, vector<Quest*>& Passenger_Info) {
	/*
	//获取车辆和用户的状态
	vector<vector<int>>Path = SL_Map.Get_Path();
	vector<vector<int>> Distance = SL_Map.Get_Distance();//地图信息
	vector<Each_Car*> Car_Info = SL_Vehicle_List.Get_Car_Info();//车辆信息（目前所在地），匹配结束后可以调用回该函数，更改其数据
	vector<Quest> Passenger_Info = SL_Passenger_List.Read_passenger_info();//乘客信息（id，起始点，终点）
	*/

	//进行匹配算法
	//排序，从站点大到小排序
	sort(Passenger_Info.begin(), Passenger_Info.end(),cmp);
	//这里改不了，可能后面要写一个快排

	//车寻找离车最近的且途径站点最多的订单a（无限循环直到所有乘客都被接到，车第一次接最近的乘客，第二次接第二近的乘客）
	vector<Each_Car*> ::iterator it;
	int count = -2;//作为选择最近点的指针
	int SL_pick_positon = 0;//模拟车辆i接客位置

	while (true) {

		//接客点更改+判断是否所有接客点都遍历了一次
		count++;
		if (count == Path.size()) break;

		//判断是否所有乘客都被接上+所有车都已经接到人
		if (All_Passenger_Pick(Passenger_Info)) break;
		if (All_Car_Work(Car_Info)) break;

		//车辆进行匹配
		for (it = Car_Info.begin(); it != Car_Info.end(); ++it) {
			//若车辆未进入工作状态（即上一轮未成功匹配）
			if ((*it)->determination == 0) {

				//获取车辆i接客位置
				if (count == -1) SL_pick_positon = (*it)->current_position;
				else SL_pick_positon = Find_Nearest_Point(Distance, (*it)->current_position, count);//从车的位置开始查找距离车最近的点

				//对所有乘客进行遍历
				for (int i = 0; i < Passenger_Info.size(); ++i) {
					if (Passenger_Info[i]->is_quest == 0)//0是乘客未搭载吗？？？
						if ((*it)->determination == 0)//车未搭载乘客？（第一个乘客储存其行进路线）
						{
							if (Passenger_Info[i]->startPos == SL_pick_positon) {
								//更新名单--数据更新
								Update_Car_Info_One(*it, Passenger_Info[i]->endPos, Passenger_Info[i], Path);
								Update_Passenger_Info_One(Passenger_Info[i], Distance[(*it)->current_position][Passenger_Info[i]->startPos], Path);
							}
						}
						else {//接到第一位客人之后，就开始去寻找拼车问题
							//如果乘客startpos在车的tobetravel中，endpos也在
							int point = is_in_path(*Passenger_Info[i], *it);
							if (point != -1) {
								//更新名单--数据更新
								Update_Car_Info_One(*it, Passenger_Info[i]->endPos, Passenger_Info[i], Path);
								int far_dis = Distance[(*it)->current_position][SL_pick_positon] + Distance[SL_pick_positon][Passenger_Info[i]->startPos];
								Update_Passenger_Info_One(Passenger_Info[i], far_dis, Path);
							}
						}
					//若刚好满员，跳出
					if ((*it)->capacity == (*it)->custNum) break;
				}
			}
		}
	}


}
//匹配策略二--不拼单策略： 暴力解法：一车接一单
//StrTwo部分
void Allocation::Str_Two(const vector<vector<vector<int>>>& Path, const vector<vector<int>>& Distance, vector<Each_Car*>& Car_Info, vector<Quest*>& Passenger_Info) {
	vector<Each_Car*> ::iterator it;
	vector<Quest*>::iterator itt;
	itt = Passenger_Info.begin();
	for (it = Car_Info.begin(); it != Car_Info.end(); ++it) {
		if (itt == Passenger_Info.end()) break;
		Update_Car_Info_One(*it, (*itt)->endPos, (*itt), Path);
		Update_Passenger_Info_One((*itt), Distance[(*it)->current_position][(*itt)->startPos], Path);
		++itt;
	}
}

/*
策略三--拼单策略：【优势：拼车为王】
1、满足前两个站点在形式路径内，则加入拼车大军
步骤：
1、对乘客的最短路径经过站点数从大到小排列
2、一辆辆车寻找离车最近的且途径站点最多的订单a
（跳出条件：找到较近站点or该轮订单全部结束）
3、多次循环，做车辆c的匹配项，若乘客b的最短形式路径的前2个点在c的行驶路径内，则接上，
并更改c的形式路径。
【接送顺序：若为完全子集关系，则先站点数小的先下；若非子集关系，则先上先下】
*/
//乘客排序：站点多->少
bool cmp1(Each_Car* x, Each_Car* y) {
	return x->custNum < y->custNum;
}
//统计乘客与车辆c行驶路径的统一
int is_in_request(Quest cus, Each_Car* car, const vector<vector<vector<int>>>& Path) {
	int flag = 0;
	int count = 0;
	//比较车辆的形式路径
	for (int i = 0; i < car->tobeTravelled.size(); ++i) {
		if (car->tobeTravelled[i] == cus.startPos) {
			count++;
			for (int j = i+1; j < car->tobeTravelled.size(); ++j) {
				if (car->tobeTravelled[j] == Path[cus.startPos][cus.endPos][j - i]) count++;
				else return count;
			}
		}
	}
	return -1;
}
//更新车辆数据
void Update_Car_Info_Three(Each_Car* car,int next_pos, Quest* passenger, const std::vector<std::vector<std::vector<int>>>& Path, int re) {
	//看车辆列表中的数据是否修改
	if (car->custNum == car->capacity) {
		//cout << "错误加入！";
		return;
	}
	car->custNum++;
	car->Pick_Passenger.push_back(passenger);

	if (car->determination == 0) {
		car->determination = next_pos;
		for (int i = 0; i < Path[passenger->startPos][car->determination].size(); i++) {
			int point = Path[passenger->startPos][car->determination][i];
			if (point == 0) break;
			else car->tobeTravelled.push_back(point);
		}
	}
	else {//将不重合部分加入队尾
		car->determination = next_pos;
		//re:重复数量(>=2)re=1 1个重复的

		for (int i = re; i < Path[passenger->startPos][passenger->endPos].size(); i++) {
			int point = Path[passenger->startPos][passenger->endPos][i];
			if (point == 0) break;
			car->tobeTravelled.push_back(point);
			
		}

	}
	return;
}
//更新乘客数据
void Update_Passenger_Info_Three(Quest* Passenger, int dis, const Each_Car* car, const vector<vector<int>>& Distance) {
	Passenger->is_quest = 1;
	//车和人的距离+人进入第X轮的时间(车辆的速度是多少？）
	Passenger->WaitingTime = dis / 5;//speed;
	
	//从startPos走到endPos
	int flag = 0;
	//int distance = 0;
	for (int i = 0; i < car->tobeTravelled.size(); i++) {
		int point = car->tobeTravelled[i];
		if (point == Passenger->startPos) flag = 1;
		if (flag == 1) {
			Passenger->RidingPath.push_back(point);
			if (point == Passenger->endPos) break;
			//distance += Distance[point][car->tobeTravelled[i+1]];
		}

	}
	//distance = distance - Distance[Passenger->startPos][Passenger->endPos];
	//Passenger->extra_distance = distance;

}

void Allocation::Str_Three(const vector<vector<vector<int>>>& Path, const vector<vector<int>>& Distance, vector<Each_Car*>& Car_Info, vector<Quest*>& Passenger_Info)
{
	//for4层
	/*
	* 车遍历，之后接起点相同的乘客
	* 对车进行排序（车空程度）
	* 再遍历，乘客符合条件，并增加行驶路线（条件：从起点算，有两个相同的站点，接！）
	* 对车进行排序（车空程度）
	* 再遍历，接行驶路线上的乘客，并增加行驶路线
	*/
	
	sort(Passenger_Info.begin(), Passenger_Info.end(), cmp);
	//车遍历，接起点尽量近的乘客
	vector<Each_Car*> ::iterator it;
	for (it = Car_Info.begin(); it != Car_Info.end(); ++it) {
		int count = -1;
		int SL_pick_positon = 0;
		while ((*it)->determination == 0) {
			//获取车辆i接客位置
			if (count == -1) SL_pick_positon = (*it)->current_position;
			else SL_pick_positon = Find_Nearest_Point(Distance, (*it)->current_position, count);
			vector<Quest*>::iterator itt;
			for (itt = Passenger_Info.begin(); itt != Passenger_Info.end(); ++itt) {
				if ((*itt)->startPos ==SL_pick_positon &&(*itt)->is_quest==0) {
					Update_Car_Info_Three(*it, (*itt)->endPos, (*itt), Path,0);
					Update_Passenger_Info_Three((*itt), Distance[(*it)->current_position][SL_pick_positon], *it,Distance);
					break;
				}
			}
			count++;
		}
		
	}
	//开始拼单
	vector<Quest*>::iterator itt;
	for(int i=1;i<=4;i++){
		sort(Car_Info.begin(), Car_Info.end(), cmp1);
		for (it = Car_Info.begin(); it != Car_Info.end(); ++it) {
			for (itt = Passenger_Info.begin(); itt != Passenger_Info.end(); ++itt) {
				int count = is_in_request(*(*itt), *it, Path);
				if (count >= 1 && (*itt)->is_quest == 0) {
					Update_Car_Info_Three(*it, (*itt)->endPos, (*itt), Path, count);
					int dis = Distance[(*it)->current_position][(*it)->tobeTravelled[0]];
					for (int i = 1; i < (*it)->tobeTravelled.size(); ++i) {
						dis += Distance[(*it)->tobeTravelled[i - 1]][(*it)->tobeTravelled[i]];
						if ((*it)->tobeTravelled[i] == (*itt)->startPos) break;
					}
					Update_Passenger_Info_Three((*itt), dis, *it,Distance);
					break;
				}
			}
		}
	}
}


//输出结果（结束了一轮）
//遍历车：每辆车的乘客容量+所接乘客名单（*QUEST）+目的地之前会经过的点
//对应的车遍历乘客：乘客id+乘客的行走路线+乘客等候时间
void Allocation::Outcome(const vector<Each_Car*>& Car_Info,int minute,int plan) {
	//Car_Info 车辆信息（目前所在地），匹配结束后可以调用回该函数，更改其数据
	cout << "方案" << plan << "的行车结果： " << endl;
	int cus_ammount = 0;
	int waiting_time = 0;
	//int extra_dis = 0;
	for (int i = 0; i < Car_Info.size(); ++i) {
		cout << "第" << i + 1 << "辆车在第" << minute << "分钟的行驶数据: " << endl;
		cout << "乘客数量：" << Car_Info[i]->custNum << endl;
		vector<Quest*>::iterator it;
		for (it = Car_Info[i]->Pick_Passenger.begin(); it != Car_Info[i]->Pick_Passenger.end(); ++it) {

			cout << "乘客id：" << left << setw(4) << (*it)->id << " waiting time: " << left << setw(4) << (*it)->WaitingTime << "行走路线：";
			for (int i = 0; i < (*it)->RidingPath.size() - 1; ++i) {
				cout << (*it)->RidingPath[i] << "-->";
			}
			cout << (*it)->endPos << endl;
			cus_ammount++;
			waiting_time += (*it)->WaitingTime;
			//extra_dis += (*it)->extra_distance;
		}
		cout << endl << endl;
	}
	cout << "方案" << plan << "的接单数量为： "<<cus_ammount<< endl << endl;
	//int extraTime=0;
	// extraTime= extra_dis / cus_ammount ;
	//cout << "方案" << plan << "乘客平均绕路距离为： " << extraTime << endl;
	//return waiting_time;//思考：接单数怎么弄
	//通过哪些信息进行比较(乘客接单数量+乘客的总体等待时间）
	//因两种方案走的都是最短路径，所以不考虑路途。
	if (plan == 1) {
		this->Cus_One.push_back(cus_ammount);
	}
	if (plan == 3) {
		this->Cus_Three.push_back(cus_ammount);
		//this->extra_Time[minute]=extraTime;
	}
}

void Allocation::TotalOutcome() {
	cout << "方案一的接单数汇总： " << endl;
	vector<int>::iterator it;
	it = this->Cus_One.begin();
	int count = 0;
	while (it != this->Cus_One.end()) {
		count++;
		for (int i = 1; i <= 5; ++i) {
			cout << right<<setw(7) << "第" << i * count << "天";
		}
		cout << endl;
		for (int i = 1; i <= 5; ++i) {
			cout << setw(10) << (*it);
			it++;
		}
		cout << endl;
	}
	cout << "方案三的接单数汇总： " << endl;

	it = this->Cus_Three.begin();
	count = 0;
	while (it != this->Cus_Three.end()) {
		count++;
		for (int i = 1; i <= 5; ++i) {
			cout << right << setw(7) << "第" << i * count << "天";
		}
		cout << endl;
		for (int i = 1; i <= 5; ++i) {
			cout << setw(10) << (*it);
			it++;
		}
		cout << endl;
	}
}


/*
核心算法：
1、第一层循环（乘客全部接上or车辆全部运行or所有接客点均遍历一次-->跳出）->设定该轮每辆车的接客点i（最近点、第二近点、第三近点）
2、第二层循环（对所有车辆进行遍历）
	->判断车i是否接客（未接客）
		获取车辆i的接客位置SL_pick_position;
	3、第三层循环（对乘客进行遍历）
		->判断乘客j是否被搭载（未搭载）
			->判断车i是否接客（未接客）
				->判断乘客j的startpos与车辆i的SL_pick_position是否相等（相等）
					车辆参数更新（车的终点、车的行驶路径、车的搭载人id）
					乘客参数更新（已上车）//是否需要增加更多参数
			->判断车i是否接客（已接客--拼车）
				-> 判断乘客i的startpos和endpos是否在车i的tobetravell中（在--可拼车）
					车辆参数更新（车的搭载人id)
					乘客参数更新（已上车）
			->判断车i是否满员，若满员，跳出第三层循环
Q：
1、轮：每一分钟一次（乘客全部接上or车辆全部运行or所有接客点均遍历一次）
【未接到的乘客进入下一轮->等待时间+1，已完成订单的车也进入下一轮）
2、乘客参数信息太少（waittime-车到人、pos-乘客所经过的站点、gotime-大概行驶时间）
*/
#include<vector>
#include<iostream>
#include<windows.h>
#include"map.h"
#include"passenger.h"
#include"vihicle.h"
#include"Allocation.h"
#include"utility.h"
using namespace std;

int main() {

	//头文件类的创建
	Map SL_Map;
	Vehicle_List SL1_Vehicle_List;
	Vehicle_List SL2_Vehicle_List;
	Vehicle_List SL3_Vehicle_List;
	Passenger_List SL1_Passenger_List;
	Passenger_List SL2_Passenger_List;
	Passenger_List SL3_Passenger_List;
	Allocation SL_Allocation;

	//建图
	SL_Map.graph_creation();
	vector<vector<vector<int>>>Path = SL_Map.Get_Path();
	vector<vector<int>> Distance = SL_Map.Get_Distance();

	//模拟：每一分钟作为一轮
	for (int i = 1; i <= 10; i++)
	{	//生成新的订单
		SL1_Passenger_List.Generate_passenger_info();//生成新的乘客订单
		
		vector<Quest*> Passenger_Info1 = SL1_Passenger_List.Read_passenger_info(Path);//将新的乘客订单放入对应的位置+获取乘客信息（id，起始点，终点）
		vector<Each_Car*> Car_Info1 = SL1_Vehicle_List.Get_Car_Info();//车辆信息（目前所在地），匹配结束后可以调用回该函数，更改其数据
		SL_Allocation.Str_One(Path, Distance, Car_Info1, Passenger_Info1);//进行匹配+更新数据(是否成功更新了呢passenger）
		SL_Allocation.Outcome(Car_Info1,i,1);//输出结果数据

		Sleep(1000);
		//vector<Quest*> Passenger_Info2 = SL2_Passenger_List.Read_passenger_info(Path);
		//vector<Each_Car*> Car_Info2 = SL2_Vehicle_List.Get_Car_Info();
		//SL_Allocation.Str_Two(Path, Distance, Car_Info2, Passenger_Info2);
		//SL_Allocation.Outcome(Car_Info2,i,2);

		vector<Quest*> Passenger_Info3 = SL3_Passenger_List.Read_passenger_info(Path);
		vector<Each_Car*> Car_Info3 = SL3_Vehicle_List.Get_Car_Info();
		SL_Allocation.Str_Three(Path, Distance, Car_Info3, Passenger_Info3);
		SL_Allocation.Outcome(Car_Info3, i, 3);

		//先车后人，对QUEST的删除
		SL1_Vehicle_List.Utilize_Car_Info();//车辆初始化
		SL1_Passenger_List.Utilize_Passenger_Info();//对乘客相关信息的清除

		//SL2_Vehicle_List.Utilize_Car_Info();
		//SL2_Passenger_List.Utilize_Passenger_Info();

		SL3_Vehicle_List.Utilize_Car_Info();
		SL3_Passenger_List.Utilize_Passenger_Info();

		Sleep(1000);//休眠1s
	}
	SL_Allocation.TotalOutcome();

	SL1_Vehicle_List.~Vehicle_List();
	SL1_Passenger_List.~Passenger_List();
	SL2_Vehicle_List.~Vehicle_List();
	SL2_Passenger_List.~Passenger_List();
	SL3_Vehicle_List.~Vehicle_List();
	SL3_Passenger_List.~Passenger_List();
	SL_Allocation.~Allocation();
}


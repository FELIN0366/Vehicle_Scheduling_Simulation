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

	//ͷ�ļ���Ĵ���
	Map SL_Map;
	Vehicle_List SL1_Vehicle_List;
	Vehicle_List SL2_Vehicle_List;
	Vehicle_List SL3_Vehicle_List;
	Passenger_List SL1_Passenger_List;
	Passenger_List SL2_Passenger_List;
	Passenger_List SL3_Passenger_List;
	Allocation SL_Allocation;

	//��ͼ
	SL_Map.graph_creation();
	vector<vector<vector<int>>>Path = SL_Map.Get_Path();
	vector<vector<int>> Distance = SL_Map.Get_Distance();

	//ģ�⣺ÿһ������Ϊһ��
	for (int i = 1; i <= 10; i++)
	{	//�����µĶ���
		SL1_Passenger_List.Generate_passenger_info();//�����µĳ˿Ͷ���
		
		vector<Quest*> Passenger_Info1 = SL1_Passenger_List.Read_passenger_info(Path);//���µĳ˿Ͷ��������Ӧ��λ��+��ȡ�˿���Ϣ��id����ʼ�㣬�յ㣩
		vector<Each_Car*> Car_Info1 = SL1_Vehicle_List.Get_Car_Info();//������Ϣ��Ŀǰ���ڵأ���ƥ���������Ե��ûظú���������������
		SL_Allocation.Str_One(Path, Distance, Car_Info1, Passenger_Info1);//����ƥ��+��������(�Ƿ�ɹ���������passenger��
		SL_Allocation.Outcome(Car_Info1,i,1);//����������

		Sleep(1000);
		//vector<Quest*> Passenger_Info2 = SL2_Passenger_List.Read_passenger_info(Path);
		//vector<Each_Car*> Car_Info2 = SL2_Vehicle_List.Get_Car_Info();
		//SL_Allocation.Str_Two(Path, Distance, Car_Info2, Passenger_Info2);
		//SL_Allocation.Outcome(Car_Info2,i,2);

		vector<Quest*> Passenger_Info3 = SL3_Passenger_List.Read_passenger_info(Path);
		vector<Each_Car*> Car_Info3 = SL3_Vehicle_List.Get_Car_Info();
		SL_Allocation.Str_Three(Path, Distance, Car_Info3, Passenger_Info3);
		SL_Allocation.Outcome(Car_Info3, i, 3);

		//�ȳ����ˣ���QUEST��ɾ��
		SL1_Vehicle_List.Utilize_Car_Info();//������ʼ��
		SL1_Passenger_List.Utilize_Passenger_Info();//�Գ˿������Ϣ�����

		//SL2_Vehicle_List.Utilize_Car_Info();
		//SL2_Passenger_List.Utilize_Passenger_Info();

		SL3_Vehicle_List.Utilize_Car_Info();
		SL3_Passenger_List.Utilize_Passenger_Info();

		Sleep(1000);//����1s
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


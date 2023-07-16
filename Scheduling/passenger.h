#pragma once
#include <iostream>
#include <cstdlib> 
#include <ctime>
#include"map.h"
#include"utility.h"
#include<vector>

//��¼ÿһ���ӳ˿���Ϣ
class Passenger_List {
public:
	Passenger_List();
	~Passenger_List();
	//Ԥ����
	//�������csv�ļ�(һ�������й˿����� �Դ��ڳ�������3-5��
	void Generate_passenger_info();
	//����ÿ���˿͵���Ϣ�������ء�Ŀ�ĵأ�-->��������
	vector<Quest*> Read_passenger_info(vector<vector<vector<int>>>Path);
	//����һ���еĸ�����Ϣ
	void Utilize_Passenger_Info();

private:
	std::vector<Quest*> Passenger_info;//һ�������г˿���Ϣ
	int Sum_Passenger_Num;//һ������������ĳ��Χ�������

};

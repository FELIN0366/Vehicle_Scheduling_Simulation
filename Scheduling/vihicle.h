#pragma once 

#include<vector>
#include"utility.h"

//һ���ڳ�����Ϣ
class Vehicle_List {
public:
	Vehicle_List();
	~Vehicle_List();
	//�������ݣ�һ����ָ����������ֹͣ�����������һ�ֵĳ�ʼ�����Ѿ�ת�ߣ�
	std::vector<Each_Car*> Get_Car_Info();
	//���³�����Ϣ
	void Utilize_Car_Info();

private:
	std::vector<Each_Car*> Car_info;//ÿ�������г�����Ϣ һ��������
	//һ��Ҫ����ַ ��Ȼû�а취����
	int Car_Amount;
};

# pragma once

#include <vector>
#include "vihicle.h"
#include "utility.h"

class Allocation {
public:
	~Allocation();
	void Str_One(const std::vector<std::vector<std::vector<int>>>& Path, const std::vector<std::vector<int>>& Distance, std::vector<Each_Car*>& Car_Info, std::vector<Quest*>& Passenger_Info);//����ƥ�����һ�ӵ���
	void Str_Two(const std::vector<std::vector<std::vector<int>>>& Path, const std::vector<std::vector<int>>& Distance, std::vector<Each_Car*>& Car_Info, std::vector<Quest*>& Passenger_Info);//���ز��Զ��Ľӵ���
	void Str_Three(const std::vector<std::vector<std::vector<int>>>& Path, const std::vector<std::vector<int>>& Distance, std::vector<Each_Car*>& Car_Info, std::vector<Quest*>& Passenger_Info);//���ز�����
	void Outcome(const std::vector<Each_Car*>& Car_Info, int minute, int plan);//���ز�������
	void TotalOutcome();
private:
	std::vector<int>Cus_One;
	std::vector<int>Cus_Three;
};

//���ִ�Ϊ��λ����ƥ��

/*ƥ�����--ƴ�����ԣ������ƣ������·����
1�����������г˿����·�������ͬʱ����ƴ��
���裺
1.�;���վ�����ɴ�С����
2.һ������Ѱ���복�������;��վ�����Ķ���a
�������������ҵ��Ͻ�վ��or���ֶ���ȫ��������
3.��a��ƥ���Ѱ������a���Ӽ�
����ֹ�����ǣ�1.��4������ 2.���ֳ˿�ƥ���� 3������ƥ���꣩
*/

//ƥ����Զ�--��ƴ�����ԣ� �����ⷨ��һ����һ��

/*
������--ƴ�����ԣ������ƣ�ƴ��Ϊ����
1������ǰ����վ������ʽ·���ڣ������ƴ�����
���裺
1���Գ˿͵����·������վ�����Ӵ�С����
2��һ������Ѱ���복�������;��վ�����Ķ���a
�������������ҵ��Ͻ�վ��or���ֶ���ȫ��������
3�����ѭ����������c��ƥ������˿�b�������ʽ·����ǰ2������c����ʻ·���ڣ�����ϣ�
������c����ʽ·����
�����������������г������ؿ�����������
������˳����Ϊ��ȫ�Ӽ���ϵ������վ����С�����£������Ӽ���ϵ�����������¡�
*/
#pragma once

//ÿ���û�����
struct Quest {
	int id=0;
	int is_quest=0;
	int startPos=0;
	int endPos=0;
	//double submitTime;
	int Num_Site = 0;//���·��;��վ������
	int WaitingTime=0;
	std::vector<int> RidingPath;
	Quest() {}
};
//����waiting time(����ȥ��ʱ��+����ÿһ�ֵ�ʱ�䣩+ ����·��(vector<int>����)��� RidingPath + ������������

//ÿ������״̬
struct Each_Car {
	//double speed;
	int capacity;//ÿ�����ĳ˿�����
	int current_position;//Ŀǰ�ڵĵ�

	int custNum;//��ǰ�����صĳ˿�����
	//int flag;//�Ƿ������һ���ӵĽӵ�
	int determination;//��ǰ������Ŀ�ĵ�(ͬʱҲ��Ϊ�Ƿ��ڶ��������еı�־��
	std::vector<int> tobeTravelled;//��Ŀ�ĵ�֮ǰ�ᾭ���ĵ�
	std::vector<Quest*> Pick_Passenger;//���ӳ˿�����
	
	Each_Car() {
		capacity = 0;
		custNum = 0;
		current_position = 0;
		determination = 0;
		tobeTravelled.clear();
		Pick_Passenger.clear();
	}
};

//map��һЩ���м����
struct Son {
	int val = 0;
	int to = 0;
	int next = -1;
};
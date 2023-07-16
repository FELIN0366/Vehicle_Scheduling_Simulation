/*ƥ�����--ƴ�����ԣ������ƣ������·����
1�����������г˿����·�������ͬʱ����ƴ��
���裺
1.�;���վ�����ɴ�С����
2.һ������Ѱ���복�������;��վ�����Ķ���a
�������������ҵ��Ͻ�վ��or���ֶ���ȫ��������
3.��a��ƥ���Ѱ������a���Ӽ�
����ֹ�����ǣ�1.��4������ 2.���ֳ˿�ƥ���� 3������ƥ���꣩
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
//strOne ����
bool cmp(Quest* x, Quest* y) {
	if (x->Num_Site > y->Num_Site) return true;
	else return false;
}
//�ó˿��Ƿ��ڳ�������ʽ·�����У�ȫ������
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
//���г˿Ͷ�������
bool All_Passenger_Pick(vector<Quest*>& Passenger_Info) {
	//vector<Quest> Passenger_Info = SL_Passenger_List.Read_passenger_info();
	vector<Quest*>::iterator it;
	for (it = Passenger_Info.begin(); it != Passenger_Info.end(); ++it) {
		if ((*it)->is_quest == 0) return false;
	}
	return true;
}
//�����������ڹ���
bool All_Car_Work(vector<Each_Car*>& Car_Info) {
	//vector<Each_Car*> Car_Info = SL_Vehicle_List.Get_Car_Info();
	vector<Each_Car*>::iterator it;
	for (it = Car_Info.begin(); it != Car_Info.end(); ++it) {
		if ((*it)->determination == 0) return false;
	}
	return true;
}
//Ѱ�Ҹó����������
int Find_Nearest_Point(const vector<vector<int>>& Distance, int Point, int count) {
	vector<int>NP;//����ĵ�Ӵ�С����
	for (int i = 0; i < Distance[Point].size(); i++) {
		if(Distance[Point][i]!=0) NP.push_back(Distance[Point][i]);
	}
	sort(NP.begin(), NP.end());//��С��������
	int val = NP[count];
	//count==0 -���ҵ���С��
	for (int i = 0; i < Distance[Point].size(); i++) {
		if (Distance[Point][i] == val) {
			return i;
		}
	}
	//return NP[NP.size() - 1 - count];
}

void Update_Car_Info_One(Each_Car* car, int next_pos, Quest* passenger, const std::vector<std::vector<std::vector<int>>>& Path) {
	//�������б��е������Ƿ��޸�
	if (car->custNum == car->capacity) {
		cout << "������룡";
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

// ����һ���еĸ�����Ϣ
void Update_Passenger_Info_One(Quest* Passenger, int dis, const std::vector<std::vector<std::vector<int>>>& Path) {
	Passenger->is_quest = 1;
	//�����˵ľ���+�˽����X�ֵ�ʱ��(�������ٶ��Ƕ��٣���
	Passenger->WaitingTime = dis / 5;//speed;

	//��startPos�ߵ�endPos
	for (int i = 0; i < Path[Passenger->startPos][Passenger->endPos].size(); ++i) {
		int point = Path[Passenger->startPos][Passenger->endPos][i];
		if (point == 0) break;
		else Passenger->RidingPath.push_back(point);
	}
}
void Allocation::Str_One(const vector<vector<vector<int>>>& Path, const vector<vector<int>>& Distance, vector<Each_Car*>& Car_Info, vector<Quest*>& Passenger_Info) {
	/*
	//��ȡ�������û���״̬
	vector<vector<int>>Path = SL_Map.Get_Path();
	vector<vector<int>> Distance = SL_Map.Get_Distance();//��ͼ��Ϣ
	vector<Each_Car*> Car_Info = SL_Vehicle_List.Get_Car_Info();//������Ϣ��Ŀǰ���ڵأ���ƥ���������Ե��ûظú���������������
	vector<Quest> Passenger_Info = SL_Passenger_List.Read_passenger_info();//�˿���Ϣ��id����ʼ�㣬�յ㣩
	*/

	//����ƥ���㷨
	//���򣬴�վ���С����
	sort(Passenger_Info.begin(), Passenger_Info.end(),cmp);
	//����Ĳ��ˣ����ܺ���Ҫдһ������

	//��Ѱ���복�������;��վ�����Ķ���a������ѭ��ֱ�����г˿Ͷ����ӵ�������һ�ν�����ĳ˿ͣ��ڶ��νӵڶ����ĳ˿ͣ�
	vector<Each_Car*> ::iterator it;
	int count = -2;//��Ϊѡ��������ָ��
	int SL_pick_positon = 0;//ģ�⳵��i�ӿ�λ��

	while (true) {

		//�ӿ͵����+�ж��Ƿ����нӿ͵㶼������һ��
		count++;
		if (count == Path.size()) break;

		//�ж��Ƿ����г˿Ͷ�������+���г����Ѿ��ӵ���
		if (All_Passenger_Pick(Passenger_Info)) break;
		if (All_Car_Work(Car_Info)) break;

		//��������ƥ��
		for (it = Car_Info.begin(); it != Car_Info.end(); ++it) {
			//������δ���빤��״̬������һ��δ�ɹ�ƥ�䣩
			if ((*it)->determination == 0) {

				//��ȡ����i�ӿ�λ��
				if (count == -1) SL_pick_positon = (*it)->current_position;
				else SL_pick_positon = Find_Nearest_Point(Distance, (*it)->current_position, count);//�ӳ���λ�ÿ�ʼ���Ҿ��복����ĵ�

				//�����г˿ͽ��б���
				for (int i = 0; i < Passenger_Info.size(); ++i) {
					if (Passenger_Info[i]->is_quest == 0)//0�ǳ˿�δ�����𣿣���
						if ((*it)->determination == 0)//��δ���س˿ͣ�����һ���˿ʹ������н�·�ߣ�
						{
							if (Passenger_Info[i]->startPos == SL_pick_positon) {
								//��������--���ݸ���
								Update_Car_Info_One(*it, Passenger_Info[i]->endPos, Passenger_Info[i], Path);
								Update_Passenger_Info_One(Passenger_Info[i], Distance[(*it)->current_position][Passenger_Info[i]->startPos], Path);
							}
						}
						else {//�ӵ���һλ����֮�󣬾Ϳ�ʼȥѰ��ƴ������
							//����˿�startpos�ڳ���tobetravel�У�endposҲ��
							int point = is_in_path(*Passenger_Info[i], *it);
							if (point != -1) {
								//��������--���ݸ���
								Update_Car_Info_One(*it, Passenger_Info[i]->endPos, Passenger_Info[i], Path);
								int far_dis = Distance[(*it)->current_position][SL_pick_positon] + Distance[SL_pick_positon][Passenger_Info[i]->startPos];
								Update_Passenger_Info_One(Passenger_Info[i], far_dis, Path);
							}
						}
					//���պ���Ա������
					if ((*it)->capacity == (*it)->custNum) break;
				}
			}
		}
	}


}
//ƥ����Զ�--��ƴ�����ԣ� �����ⷨ��һ����һ��
//StrTwo����
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
������--ƴ�����ԣ������ƣ�ƴ��Ϊ����
1������ǰ����վ������ʽ·���ڣ������ƴ�����
���裺
1���Գ˿͵����·������վ�����Ӵ�С����
2��һ������Ѱ���복�������;��վ�����Ķ���a
�������������ҵ��Ͻ�վ��or���ֶ���ȫ��������
3�����ѭ����������c��ƥ������˿�b�������ʽ·����ǰ2������c����ʻ·���ڣ�����ϣ�
������c����ʽ·����
������˳����Ϊ��ȫ�Ӽ���ϵ������վ����С�����£������Ӽ���ϵ�����������¡�
*/
//�˿�����վ���->��
bool cmp1(Each_Car* x, Each_Car* y) {
	return x->custNum < y->custNum;
}
//ͳ�Ƴ˿��복��c��ʻ·����ͳһ
int is_in_request(Quest cus, Each_Car* car, const vector<vector<vector<int>>>& Path) {
	int flag = 0;
	int count = 0;
	//�Ƚϳ�������ʽ·��
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
//���³�������
void Update_Car_Info_Three(Each_Car* car,int next_pos, Quest* passenger, const std::vector<std::vector<std::vector<int>>>& Path, int re) {
	//�������б��е������Ƿ��޸�
	if (car->custNum == car->capacity) {
		//cout << "������룡";
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
	else {//�����غϲ��ּ����β
		car->determination = next_pos;
		//re:�ظ�����(>=2)re=1 1���ظ���

		for (int i = re; i < Path[passenger->startPos][passenger->endPos].size(); i++) {
			int point = Path[passenger->startPos][passenger->endPos][i];
			if (point == 0) break;
			car->tobeTravelled.push_back(point);
			
		}

	}
	return;
}
//���³˿�����
void Update_Passenger_Info_Three(Quest* Passenger, int dis, const Each_Car* car, const vector<vector<int>>& Distance) {
	Passenger->is_quest = 1;
	//�����˵ľ���+�˽����X�ֵ�ʱ��(�������ٶ��Ƕ��٣���
	Passenger->WaitingTime = dis / 5;//speed;
	
	//��startPos�ߵ�endPos
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
	//for4��
	/*
	* ��������֮��������ͬ�ĳ˿�
	* �Գ��������򣨳��ճ̶ȣ�
	* �ٱ������˿ͷ�����������������ʻ·�ߣ�������������㣬��������ͬ��վ�㣬�ӣ���
	* �Գ��������򣨳��ճ̶ȣ�
	* �ٱ���������ʻ·���ϵĳ˿ͣ���������ʻ·��
	*/
	
	sort(Passenger_Info.begin(), Passenger_Info.end(), cmp);
	//������������㾡�����ĳ˿�
	vector<Each_Car*> ::iterator it;
	for (it = Car_Info.begin(); it != Car_Info.end(); ++it) {
		int count = -1;
		int SL_pick_positon = 0;
		while ((*it)->determination == 0) {
			//��ȡ����i�ӿ�λ��
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
	//��ʼƴ��
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


//��������������һ�֣�
//��������ÿ�����ĳ˿�����+���ӳ˿�������*QUEST��+Ŀ�ĵ�֮ǰ�ᾭ���ĵ�
//��Ӧ�ĳ������˿ͣ��˿�id+�˿͵�����·��+�˿͵Ⱥ�ʱ��
void Allocation::Outcome(const vector<Each_Car*>& Car_Info,int minute,int plan) {
	//Car_Info ������Ϣ��Ŀǰ���ڵأ���ƥ���������Ե��ûظú���������������
	cout << "����" << plan << "���г������ " << endl;
	int cus_ammount = 0;
	int waiting_time = 0;
	//int extra_dis = 0;
	for (int i = 0; i < Car_Info.size(); ++i) {
		cout << "��" << i + 1 << "�����ڵ�" << minute << "���ӵ���ʻ����: " << endl;
		cout << "�˿�������" << Car_Info[i]->custNum << endl;
		vector<Quest*>::iterator it;
		for (it = Car_Info[i]->Pick_Passenger.begin(); it != Car_Info[i]->Pick_Passenger.end(); ++it) {

			cout << "�˿�id��" << left << setw(4) << (*it)->id << " waiting time: " << left << setw(4) << (*it)->WaitingTime << "����·�ߣ�";
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
	cout << "����" << plan << "�Ľӵ�����Ϊ�� "<<cus_ammount<< endl << endl;
	//int extraTime=0;
	// extraTime= extra_dis / cus_ammount ;
	//cout << "����" << plan << "�˿�ƽ����·����Ϊ�� " << extraTime << endl;
	//return waiting_time;//˼�����ӵ�����ôŪ
	//ͨ����Щ��Ϣ���бȽ�(�˿ͽӵ�����+�˿͵�����ȴ�ʱ�䣩
	//�����ַ����ߵĶ������·�������Բ�����·;��
	if (plan == 1) {
		this->Cus_One.push_back(cus_ammount);
	}
	if (plan == 3) {
		this->Cus_Three.push_back(cus_ammount);
		//this->extra_Time[minute]=extraTime;
	}
}

void Allocation::TotalOutcome() {
	cout << "����һ�Ľӵ������ܣ� " << endl;
	vector<int>::iterator it;
	it = this->Cus_One.begin();
	int count = 0;
	while (it != this->Cus_One.end()) {
		count++;
		for (int i = 1; i <= 5; ++i) {
			cout << right<<setw(7) << "��" << i * count << "��";
		}
		cout << endl;
		for (int i = 1; i <= 5; ++i) {
			cout << setw(10) << (*it);
			it++;
		}
		cout << endl;
	}
	cout << "�������Ľӵ������ܣ� " << endl;

	it = this->Cus_Three.begin();
	count = 0;
	while (it != this->Cus_Three.end()) {
		count++;
		for (int i = 1; i <= 5; ++i) {
			cout << right << setw(7) << "��" << i * count << "��";
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
�����㷨��
1����һ��ѭ�����˿�ȫ������or����ȫ������or���нӿ͵������һ��-->������->�趨����ÿ�����Ľӿ͵�i������㡢�ڶ����㡢�������㣩
2���ڶ���ѭ���������г������б�����
	->�жϳ�i�Ƿ�ӿͣ�δ�ӿͣ�
		��ȡ����i�Ľӿ�λ��SL_pick_position;
	3��������ѭ�����Գ˿ͽ��б�����
		->�жϳ˿�j�Ƿ񱻴��أ�δ���أ�
			->�жϳ�i�Ƿ�ӿͣ�δ�ӿͣ�
				->�жϳ˿�j��startpos�복��i��SL_pick_position�Ƿ���ȣ���ȣ�
					�����������£������յ㡢������ʻ·�������Ĵ�����id��
					�˿Ͳ������£����ϳ���//�Ƿ���Ҫ���Ӹ������
			->�жϳ�i�Ƿ�ӿͣ��ѽӿ�--ƴ����
				-> �жϳ˿�i��startpos��endpos�Ƿ��ڳ�i��tobetravell�У���--��ƴ����
					�����������£����Ĵ�����id)
					�˿Ͳ������£����ϳ���
			->�жϳ�i�Ƿ���Ա������Ա������������ѭ��
Q��
1���֣�ÿһ����һ�Σ��˿�ȫ������or����ȫ������or���нӿ͵������һ�Σ�
��δ�ӵ��ĳ˿ͽ�����һ��->�ȴ�ʱ��+1������ɶ����ĳ�Ҳ������һ�֣�
2���˿Ͳ�����Ϣ̫�٣�waittime-�����ˡ�pos-�˿���������վ�㡢gotime-�����ʻʱ�䣩
*/
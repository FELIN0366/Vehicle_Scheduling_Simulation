#include"passenger.h"
#include"utility.h"
#include<vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include<string>
using namespace std;


Passenger_List::Passenger_List() {
	this->Sum_Passenger_Num = 0;
	Passenger_info.clear();
}

Passenger_List::~Passenger_List() {
	vector<Quest*>::iterator it;
	for (it = Passenger_info.begin(); it != Passenger_info.end(); it++)
		delete (*it);
}

//Ԥ����
//�������csv�ļ�(һ�������й˿����� �Դ��ڳ�������3-5��
void Passenger_List::Generate_passenger_info()
{
	ofstream outFile;
	outFile << "passenger_id" << ',' << "start_position" << ',' << "destination" << endl;
	int passenger_num = 0;
	unsigned seed;
	seed = time(0);
	srand(seed);
	passenger_num = rand() % (25 - 15 + 1) + 30;
	outFile.open("passenger_list.csv", ios::out);
	for (int i = 1; i < passenger_num + 1; )
	{
		int start_position = 0;
		int destination = 0;
		start_position = rand() % (9 - 1 + 1) + 1;
		destination = rand() % (9 - 1 + 1) + 1;
		if (start_position == destination)
		{
			i = i;
			continue;
		}
		else
		{
			//outFile.open("passenger_list.csv", ios::out);
			outFile << i << ',' << start_position << ',' << destination << endl;
			i = i + 1;
		}

	}
	outFile.close();
}

//�ֲ���������ȡ���·�����ᾭ����վ�㣨ʹ�ò�������ʱ�򽫻�Դ˽��и��ģ�
void get_NumSite(Quest* x, vector<vector<vector<int>>>Path) {
	//vector<vector<int>>Path = SL_Map.Get_Path();
	vector<int>::iterator it;
	int val1 = 0;
	for (it = Path[x->startPos][x->endPos].begin(); it != Path[x->startPos][x->endPos].end(); ++it) {
		if (*it == x->endPos) break;
		else val1++;
	}
	x->Num_Site = val1;
	return;
}

//����ÿ���˿͵���Ϣ�������ء�Ŀ�ĵأ�-->��������
vector<Quest*> Passenger_List::Read_passenger_info(vector<vector<vector<int>>>Path)
{	
	FILE* fp;
	//vector<Quest*> passenger_info;
	errno_t err;
	err = fopen_s(&fp, "passenger_list.csv", "r");//�ļ�·��(û��ȫ�ģ�
	while (1)
	{	
		if (feof(fp)) break;
		Quest* Request = new Quest();
		fscanf(fp, "%d,%d,%d", &(Request->id), &(Request->startPos), &(Request->endPos));
		if (Request->endPos == 0) continue;
		get_NumSite(Request, Path);
		this->Passenger_info.push_back(Request);
		
	}
	if (fp == NULL) //�޸������жϽ�����־���Warning C6387
	{
		this->Passenger_info.clear();
		return this->Passenger_info;
	}
	fclose(fp);
	this->Sum_Passenger_Num = this->Passenger_info.size();
	return this->Passenger_info;
	//Felin���������ҵ�returnȥ�������
	// jyw:�����Ҹ���return��ȥ�ˣ����������ֱȴ�һ��return��������
	//Felin: is_quest, WaitingTime, RidingPath��Ҫ����
}

//ÿһ�ֿ�ʼ��ʱ��Գ������г�ʼ��
void Passenger_List::Utilize_Passenger_Info() {
	//Felin:���ʲô�ģ���
	ofstream fileout("passenger_list.csv", ios_base::out);//ios::trunc�����ԭ�ļ�����,�ɲ�д,Ĭ�Ͼ�����
	if (!fileout) {
		cout << "Clear successfully!\n";
		exit(0);
	}
	fileout.close();
	vector<Quest*> ::iterator it;
	for (it = this->Passenger_info.begin(); it != this->Passenger_info.end(); it++) {
		delete (*it);
	}
	this->Passenger_info.clear();
	this->Sum_Passenger_Num = 0;
}
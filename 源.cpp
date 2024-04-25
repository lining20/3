#include<iostream>
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<iomanip>
#include<string>
using namespace std;

#define MaxNum 50//��������
#define MaxInt 10000//�����
#define MinInt 0//�ǳ�С
string Name[MaxNum];//��������

typedef struct
{
	int Weight[MaxNum][MaxNum];//����֮����·����ɱ�
	int Nv, Ne;//����������
}graph, * Graph;

typedef struct Edge
{
	int A, B;//��㣬�յ�
	int weight;
}Edge;

//��ʼ��ͼ
void ZeroGraph(Graph& G)
{
	G->Ne = G->Nv = 0;
	for (int i = 0; i < MaxNum; i++)
	{
		for (int j = 0; j < MaxNum; j++)
		{
			G->Weight[i][j] = MaxInt;//��ʼ��Ϊ����֮�佨����·����Զ
		}
		G->Weight[i][i] = MinInt;
	}
}

//����ͼ
void CreatGraph(Graph& G)
{
	cout << "�������������";
	cin >> G->Nv;
	cout << "����������ƣ�";
	string n;
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> Name[i];
	}
	cout << "����·��������";
	cin >> G->Ne;
	cout << "������������֮���·�ߣ����ա�����1 ����2 ���á�" << endl;
	string name1, name2;
	int Fare, flag1 = 0, flag2 = 0;
	for (int i = 0; i < G->Ne; i++)
	{
		int j;
		cin >> name1 >> name2 >> Fare;
		for (j = 0; j < G->Nv; j++)
		{
			if (name1 == Name[j]) flag1 = j;
			if (name2 == Name[j]) flag2 = j;
		}

		G->Weight[flag1][flag2] = Fare;
		G->Weight[flag2][flag1] = Fare;
	}
}

//���
void Print(Graph& G)
{
	cout << std::left << setw(7) << " ";
	for (int i = 0; i < G->Nv; i++)
	{
		cout << std::left << setw(7) << Name[i];
	}
	cout << endl;
	for (int i = 0; i < G->Nv; i++)
	{
		cout << std::left << setw(7) << Name[i];
		for (int j = 0; j < G->Nv; j++)
		{
			cout << std::left << setw(7) << G->Weight[i][j];
		}
		cout << endl;
	}
	cout << "��-----10000��ʾû��·��-----��" << endl;
}

//���·���㷨
void Short_K(Graph& G)
{
	cout << endl << "-----�Ѿ�Ϊ���ó�·��-----" << endl;
	Edge Hi[MaxNum];
	int NUM = 0;
	for (int i = 0; i < G->Nv; i++)
	{
		for (int j = i + 1; j < G->Nv; j++)
		{
			if (G->Weight[i][j] != 10000)
			{
				Hi[NUM].A = i;
				Hi[NUM].B = j;
				Hi[NUM].weight = G->Weight[i][j];
				//cout << Name[Hi[NUM].A] << "->" << Name[Hi[NUM].B] << "------"<< Hi[NUM].weight<<endl;
				NUM++;
			}
		}
	}
	//����
	int temp, j;
	for (int i = 0; i < NUM; i++)
	{
		temp = i;
		for (j = i; j < NUM; j++)
		{
			if (Hi[temp].weight > Hi[j].weight)
			{
				temp = j;
			}
		}

		Hi[49] = Hi[temp];
		Hi[temp] = Hi[i];
		Hi[i] = Hi[49];
		//cout << Name[Hi[i].A] << "->" << Name[Hi[i].B] << "------" << Hi[i].weight << endl;
	}
	int flag[MaxNum] = { 0 };
	for (int i = 0; i <= G->Nv; i++)
	{
		flag[i] = i;
	}
	int ADD = 0;
	for (int i = 0; i < NUM; i++)
	{
		if (flag[Hi[i].A] != flag[Hi[i].B])
		{
			int find = flag[Hi[i].B];
			for (int j = 0; j < G->Nv; j++)
			{
				if (flag[j] == find)
				{
					flag[j] = flag[Hi[i].A];
				}
			}
			cout << Name[Hi[i].A] << "-" << G->Weight[Hi[i].A][Hi[i].B] << "->" << Name[Hi[i].B] << endl;
			ADD += G->Weight[Hi[i].A][Hi[i].B];
		}
	}
	cout << "�޽���̷��ã�" << ADD << endl;
}

//չʾ����
void Show()
{
	cout << "***************չʾ����*****************" << endl;
	cout << "------------1.������·����--------------" << endl;
	cout << "------------2.������·��--------------" << endl;
	cout << "------------3.���ӳ�����·--------------" << endl;
	cout << "------------4.���ٳ�����·--------------" << endl;
	cout << "-----------5.����������·-------------" << endl;
	cout << "--------------6.�˳�����----------------" << endl;
	cout << "****************************************" << endl;
}

//���ӳ���
void Put(Graph& G)
{
	string city;
	cout << "���ӳ��е����ƣ�";
	cin >> city;
	Name[G->Nv] = city;
	G->Nv++;
	cout << "������·��������";
	int Num;
	cin >> Num;
	G->Ne += Num;
	cout << "������������֮���·�ߣ����ա�����1 ����2 ���á�" << endl;
	string name1, name2;
	int Fare, flag1 = 0, flag2 = 0;
	for (int i = 0; i < Num; i++)
	{
		int j;
		cin >> name1 >> name2 >> Fare;
		for (j = 0; j < G->Nv; j++)
		{
			if (name1 == Name[j]) flag1 = j;
			if (name2 == Name[j]) flag2 = j;
		}
		G->Weight[flag1][flag2] = Fare;
		G->Weight[flag2][flag1] = Fare;
	}
}

//���ٳ���
void  Delete(Graph& G)
{
	cout << "ɾ���������ƣ�";
	string city;
	cin >> city;
	int flag = 0;
	for (int i = 0; i < G->Nv; i++)
	{
		if (city == Name[i]) flag = i;
	}
	for (int i = 0; i < G->Nv; i++)
	{
		if (G->Weight[flag][i] != 10000) G->Ne--;
	}
	G->Ne++;
	for (int i = 0; i < G->Nv; i++)
	{
		for (int j = flag; j < G->Nv; j++)
		{
			G->Weight[i][j] = G->Weight[i][j + 1];
			//G->Weight[j][i] = G->Weight[j + 1][i];
		}
	}
	for (int i = 0; i < G->Nv; i++)
	{
		for (int j = flag; j < G->Nv; j++)
		{
			//G->Weight[i][j] = G->Weight[i][j + 1];
			G->Weight[j][i] = G->Weight[j + 1][i];
		}
	}
	for (int i = flag; i < G->Nv; i++)
	{
		Name[i] = Name[i + 1];
	}
	G->Nv--;
}

//ϵͳ
void System(Graph& G)
{
	while (1)
	{
		int choice;
		cout << "������ѡ��";
		cin >> choice;
		if (choice == 0) Show();
		else if (choice == 1) CreatGraph(G);
		else if (choice == 2) Short_K(G);
		else if (choice == 3) Put(G);
		else if (choice == 4) Delete(G);
		else if (choice == 5) Print(G);
		else if (choice == 6) break;
		else cout << "û�д�ѡ��������ѡ������뿴չʾ���棬�밴�� 0 ��" << endl;
	}
}

//������
int main()
{

	graph* G;
	G = (Graph)malloc(sizeof(graph));
	ZeroGraph(G);
	Show();
	System(G);

	return 0;
}

//��������
/*
���� �Ϻ� ���� ���� ���� ������ �ɶ�

���� �Ϻ� 6
���� ���� 9
�Ϻ� ���� 12
���� ���� 3
�ɶ� ���� 4
���� ������ 7
���� ������ 3
������ �ɶ� 25


��ɽ
��ɽ ���� 1
��ɽ ���� 4
*/
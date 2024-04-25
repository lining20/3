#include<iostream>
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<iomanip>
#include<string>
using namespace std;

#define MaxNum 50//最大的数量
#define MaxInt 10000//无穷大
#define MinInt 0//非常小
string Name[MaxNum];//城市名称

typedef struct
{
	int Weight[MaxNum][MaxNum];//城市之间线路建设成本
	int Nv, Ne;//点数，边数
}graph, * Graph;

typedef struct Edge
{
	int A, B;//起点，终点
	int weight;
}Edge;

//初始化图
void ZeroGraph(Graph& G)
{
	G->Ne = G->Nv = 0;
	for (int i = 0; i < MaxNum; i++)
	{
		for (int j = 0; j < MaxNum; j++)
		{
			G->Weight[i][j] = MaxInt;//初始认为城市之间建设线路无限远
		}
		G->Weight[i][i] = MinInt;
	}
}

//创建图
void CreatGraph(Graph& G)
{
	cout << "输入城市数量：";
	cin >> G->Nv;
	cout << "输入城市名称：";
	string n;
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> Name[i];
	}
	cout << "输入路线数量：";
	cin >> G->Ne;
	cout << "输入两座城市之间的路线，按照“城市1 城市2 费用”" << endl;
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

//输出
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
	cout << "“-----10000表示没有路径-----”" << endl;
}

//最短路径算法
void Short_K(Graph& G)
{
	cout << endl << "-----已经为您得出路径-----" << endl;
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
	//排序
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
	cout << "修建最短费用：" << ADD << endl;
}

//展示界面
void Show()
{
	cout << "***************展示界面*****************" << endl;
	cout << "------------1.城市线路输入--------------" << endl;
	cout << "------------2.输出最短路径--------------" << endl;
	cout << "------------3.增加城市线路--------------" << endl;
	cout << "------------4.减少城市线路--------------" << endl;
	cout << "-----------5.输出保存的线路-------------" << endl;
	cout << "--------------6.退出程序----------------" << endl;
	cout << "****************************************" << endl;
}

//增加城市
void Put(Graph& G)
{
	string city;
	cout << "增加城市的名称：";
	cin >> city;
	Name[G->Nv] = city;
	G->Nv++;
	cout << "增加线路的数量：";
	int Num;
	cin >> Num;
	G->Ne += Num;
	cout << "输入两座城市之间的路线，按照“城市1 城市2 费用”" << endl;
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

//减少城市
void  Delete(Graph& G)
{
	cout << "删除城市名称：";
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

//系统
void System(Graph& G)
{
	while (1)
	{
		int choice;
		cout << "请做出选择：";
		cin >> choice;
		if (choice == 0) Show();
		else if (choice == 1) CreatGraph(G);
		else if (choice == 2) Short_K(G);
		else if (choice == 3) Put(G);
		else if (choice == 4) Delete(G);
		else if (choice == 5) Print(G);
		else if (choice == 6) break;
		else cout << "没有此选择，请重新选择，如果想看展示界面，请按“ 0 ”" << endl;
	}
}

//主函数
int main()
{

	graph* G;
	G = (Graph)malloc(sizeof(graph));
	ZeroGraph(G);
	Show();
	System(G);

	return 0;
}

//测试用例
/*
北京 上海 重庆 长春 沈阳 哈尔滨 成都

北京 上海 6
重庆 北京 9
上海 重庆 12
长春 沈阳 3
成都 重庆 4
北京 哈尔滨 7
长春 哈尔滨 3
哈尔滨 成都 25


鞍山
鞍山 沈阳 1
鞍山 北京 4
*/
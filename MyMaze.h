#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stack>
#include<set>
#include<vector>
#include<map>
#include<iomanip>
using namespace std;

//���峣��
const int WAY_NUM = 4;
const int WAY_RIGHT = 0;
const int WAY_DOWN = 1;
const int WAY_LEFT = 2;
const int WAY_UP = 3;

//�Թ�·���Ƿ�����Թ�·��
const int  WAY_OK = 6;  //����·��
const int WAY_NO = 7;  //������·��

//�����Թ��������
class MazeNode
{
private:
	int _val;   //����е�ֵ
	int _x; //x����
	int _y;//y����
	int _way[WAY_NUM];

public:
	MazeNode();
	//new���鲻�ܵ��ô������Ķ��󣬽��г�ʼ��------new�����ʱ���ܽ��г�ʼ��
	MazeNode(int val, int x, int y);
	void SetMaze(int val, int x, int y);
	void SetWay(int *way);
	int*WayArr(int **arr, int x, int y, int size, int way[4]);
	int*getway() { return _way; }
	int getval() { return _val; }
	int setval();
	int setnodeval();
	int getx() { return _x; }
	int gety() { return _y; }

};

//�����Թ�����
class  Maze
{
public:
	Maze(int size);
	~Maze();

	bool FindPath();
	void ShowPath();
	void ShowSolution(); // ���·������
private:
	stack<MazeNode>_stack;
	int _row;  //��
	int _col;  //��
	MazeNode  **Pnode;    //����һ��ָ���Թ��ڽڵ��ָ��
};



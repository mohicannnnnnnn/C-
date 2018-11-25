#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stack>
#include<set>
#include<vector>
#include<map>
#include<iomanip>
using namespace std;

//定义常量
const int WAY_NUM = 4;
const int WAY_RIGHT = 0;
const int WAY_DOWN = 1;
const int WAY_LEFT = 2;
const int WAY_UP = 3;

//迷宫路径是否存在迷宫路径
const int  WAY_OK = 6;  //存在路径
const int WAY_NO = 7;  //不存在路径

//设置迷宫结点类型
class MazeNode
{
private:
	int _val;   //结点中的值
	int _x; //x坐标
	int _y;//y坐标
	int _way[WAY_NUM];

public:
	MazeNode();
	//new数组不能调用带参数的对象，进行初始化------new数组的时候不能进行初始化
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

//设置迷宫类型
class  Maze
{
public:
	Maze(int size);
	~Maze();

	bool FindPath();
	void ShowPath();
	void ShowSolution(); // 输出路径坐标
private:
	stack<MazeNode>_stack;
	int _row;  //行
	int _col;  //列
	MazeNode  **Pnode;    //设置一个指向迷宫内节点的指针
};



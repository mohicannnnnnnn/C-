/*

0 0 1 0 1
1 0 0 0 1
0 0 0 1 0
1 1 0 1 0
0 0 0 0 0

# # 1 0 1
1 # # 0 1
0 0 # 1 0
1 1 # 1 0
0 0 # # #
*/

#include<iostream>
#include"MyMaze.h"
using namespace std;
MazeNode::MazeNode()
{
	/*for(int i=0;i<_way[WAY_NUM];i++)
	{
	_way[WAY_NUM]=WAY_NO;
	}*/
}

MazeNode::MazeNode(int val,int x,int y) : _val(val),_x(x),_y(y)
{
	for(int i=0;i<_way[WAY_NUM];i++)
	{
		_way[WAY_NUM]=WAY_NO;
	}
}

void MazeNode::SetMaze(int val,int x ,int y)
{
	_val=val;
	_x=x;
	_y=y;
}

void MazeNode::SetWay(int *way)
{
	for(int i =0;i<WAY_NUM;i++)
	{
		_way[i]=way[i];
	}
}



int* MazeNode::WayArr(int **arr,int x,int y,int size,int way[4])
{
	if(x==0)
		way[WAY_UP]=1;
	else
		way[WAY_UP] = arr[x-1][y];

	if(x==size-1)
		way[WAY_DOWN] =1;
	else
		way[WAY_DOWN] =arr[x+1][y];

	if(y==0)
		way[WAY_LEFT] = 1;
	else 
		way[WAY_LEFT] = arr[x][y-1];

	if(y==size-1)
		way[WAY_RIGHT] =1;
	else
		way[WAY_RIGHT] = arr[x][y+1];

	return way;
}


Maze::Maze(int size)
{
	_row = size;
	_col = size;
	Pnode = new MazeNode*[_row];//  
	for(int i =0;i<_row;i++)
	{
		Pnode[i] = new MazeNode [_col]; 
	}
	cout<<"please input an array"<<endl;

	int **arr;  
	arr = new int*[_row];
	for(int i =0;i<_row;i++)
	{ 
		arr[i]=new int [_col];
		for(int j=0;j<_col;j++)
		{
			cin>>arr[i][j];
		}
	}

	int  way[4]={0};
	for(int i=0;i<_row;i++)
		for(int j=0;j<_col;j++)
		{
			Pnode[i][j].SetMaze(arr[i][j],i,j);
			Pnode[i][j].SetWay(Pnode[i][j].WayArr(arr,i,j,size,way));
		}
		for(int i=0;i<_row;i++)
		{
			delete[]arr[i];
			arr[i]=NULL;
		}
		delete[]arr;
		arr = NULL;
}

Maze::~Maze()
{
	for(int i=0;i<_row;i++)
	{
		delete []Pnode[i];
		Pnode[i]=NULL;
	}
	delete[]Pnode;
	Pnode = NULL;
}

bool Maze::FindPath()
{
	if(Pnode[0][0].getval()==1)
	{
		cout<<"There Has No Entrance "<<endl;
		return false;
	}

	if(Pnode[_row-1][_col-1].getval()==1)
	{
		cout<<"There has No Exit"<<endl;
		return false;
	}

	int i=0; int j=0;
	_stack.push(Pnode[i][j]);
	bool wrongflag = false;
	auto inrange = [=](int left, int right, int val) -> bool 
	{
		return val >= left && val < right;
	};

	while ( !_stack.empty()
		&& !(Pnode[i][j].getx() == _row - 1 && Pnode[i][j].gety() == _col - 1) ) 
	{

		if (inrange(0, _col, j+1) &&
			Pnode[i][j + 1].getval() == 0 && Pnode[i][j].getway()[WAY_RIGHT] == 0) {
				_stack.push(Pnode[i][j + 1]);
		}

		else if (inrange(0, _row, i+1) &&
			Pnode[i + 1][j].getval() == 0 && Pnode[i][j].getway()[WAY_DOWN] == 0) {
				_stack.push(Pnode[i + 1][j]);
		}

		else if (inrange(0, _col, j-1) &&
			Pnode[i][j - 1].getval() == 0 && Pnode[i][j].getway()[WAY_LEFT] == 0) {
				_stack.pop();
				Pnode[i][j].setval();
		}

		else if (inrange(0, _row, i-1) &&
			Pnode[i - 1][j].getval() == 0 && Pnode[i][j].getway()[WAY_UP] == 0) {
				_stack.pop();

				Pnode[i][j].setval();
		}
		else {
			wrongflag = true;
			break;
		}
		i = _stack.top().getx();
		j = _stack.top().gety();
	}
	if (_stack.empty() || wrongflag) 
		return false;
	else
		return true;
}

int MazeNode::setval()
{
	if (_val == 0)
	{
		_val = 3;
	}
	return _val;
}

int MazeNode::setnodeval()
{
	if (_val == 0)
	{
		_val = 6;
	}
	return _val;
}
void Maze::ShowSolution() {
	if (_stack.size() < (_col + _row - 1)) {
		cout << "please find path first!" << endl;
		return;
	}
	cout << "Show The Path Node" << endl;
	MazeNode tmpNode;
	stack<MazeNode> tmpStack;
	while (!_stack.empty()) {
		tmpStack.push(_stack.top());
		Pnode[tmpStack.top().getx()][tmpStack.top().gety()].setnodeval();
		_stack.pop();
	}
	while (!tmpStack.empty()) {
		cout << "<" << tmpStack.top().getx() << ", " << tmpStack.top().gety() << ">" << endl;
		tmpStack.pop();
	}
}

void Maze::ShowPath()
{
	cout << "Show The Maze" << endl;
	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _col; j++)

			cout << setiosflags(ios::left) << setw(3) << Pnode[i][j].getval();    
		putchar(10);
	}
}

int main()
{
	cout<<"Please Input The Size"<<endl;
	int size;
	cin>>size;
	Maze p(size);

	if (p.FindPath())
	{
	 p.ShowSolution();
	 p.ShowPath();}
	else
		cout << "There has no path at all!" << endl;
	system("pause");
}


#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stack>
#include<set>
#include<vector>
#include<map>
#include<iomanip>
using namespace std;


const int WAY_NUM = 4;
const int WAY_RIGHT = 0;
const int WAY_DOWN = 1;
const int WAY_LEFT = 2;
const int WAY_UP = 3;


const int  WAY_OK = 6; 
const int WAY_NO = 7;  

//�����Թ��������
class MazeNode
{
private:
	int _val;  ֵ
	int _x; 
	int _y;
	int _way[WAY_NUM];

public:
	MazeNode();
	
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


class  Maze
{
public:
	Maze(int size);
	~Maze();

	bool FindPath();
	void ShowPath();
	void ShowSolution(); 
private:
	stack<MazeNode>_stack;
	int _row; 
	int _col;  
	MazeNode  **Pnode;   
};



#include <iostream>
#include <ctime>

using namespace std;

class Point
{
public:
	int x;
	int y;

public:
	Point(){}
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

Point p[16];
char A[4][4];
char BK[4][4];
int X[16];
int minChange;
int cntChange;

int X_near[4] = {-1, 1, 0, 0};
int Y_near[4] = {0, 0, -1, 1};


void changeColor(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		int xNear = X_near[i] + x;
		int yNear = Y_near[i] + y;

		if(A[x][y] == 'b')
		{
			A[xNear][yNear] = 'w';
		} else
		{
			A[xNear][yNear] = 'b';	
		}
	}
}

void undoChangeColor(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		int xNear = X_near[i] + x;
		int yNear = Y_near[i] + y;

		if(A[xNear][yNear] == 'b')
		{
			A[xNear][yNear] = 'w';
		} else
		{
			A[xNear][yNear] = 'b';	
		}
	}
}

void countBlackAndWhite(int &countBlack, int &countWhite)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if(A[i][j] == 'b')
			{
				countBlack++;
			} else
			{
				countWhite++;
			}
		}
	}
}

void display()
{
	for (int i = 0; i < 16; i++)
	{
		cout << X[i] << " ";
	}
	cout << endl;
}

int countOne()
{
	int count = 0;
	for (int i = 0; i < 16; i++)
	{
		if(X[i] == 1)
		{
			count++;
		}
	}
	return count;
}

void genC(int i)
{
	for (int j = 0; j < 2; j++)
	{
		if(cntChange >= minChange)
		{
			continue;
		}

		X[i] = j;
		if(j == 1)
		{
			changeColor(p[i].x, p[i].y);
			cntChange++;
		}

		int blacks = 0;
		int white = 0;
		countBlackAndWhite(blacks, white);

		if(blacks == 16 || white == 16)
		{
			if(cntChange < minChange)
			{
				minChange = cntChange;
			}
		} else if (i < 15)
		{
			genC(i+1);
			if(j == 1)
			{
				undoChangeColor(p[i].x, p[i].y);
				cntChange--;
			}
		}
	}
}

int main()
{
	clock_t begin = clock();

	freopen("input.txt", "r", stdin);

	minChange = 100;
	cntChange = 0;

	int k = 0;
	for (int i = 0; i < 4; i++)
	{
		cin >> A[i];
		for (int j = 0; j < 4; j++)
		{
			p[k++] = Point(i, j);
			BK[i][j] = A[i][j];
		}
	}

	genC(0);

	if(minChange != 100)
	{
		cout << "Min operations: " << minChange;
	} else
	{
		cout << "impossible";
	}

	clock_t end = clock();

	cout << "\ntime: " << double(end-begin)/CLOCKS_PER_SEC;
	return 0;
}
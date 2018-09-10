#include <iostream>
using namespace std;

struct Point2D
{
	int x;
	int y;
} p[100];

double length(Point2D a, Point2D b);


int _tmain(int argc, _TCHAR* argv[])
{
	int n = 7;
	double iMin;
	Point2D a, b;

	cout << "Nhap diem. " << endl;
	for (int i = 0; i < n; i++){
		cout << "Nhap x: ";
		cin >> p[i].x;

		cout << "Nhap y: ";
		cin >> p[i].y;
	}

	iMin = length(p[0], p[1]);
	a = p[0];
	b = p[1];

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if ((length(p[i], p[j]) < iMin) && (length(p[i], p[j]) != 0))
			{
				iMin = length(p[i], p[j]);
				a = p[i];
				b = p[j];
			}
		}
	}


	cout << "Hai diem gan nhat: (" << a.x << "; " << a.y << ") va (" << b.x << "; " << b.y << ")" << endl;

	system("pause");
	return 0;


}



double length(Point2D a, Point2D b)
{
	return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}
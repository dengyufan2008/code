#include <iostream>
#include <Windows.h>
using namespace std;

void sort(int a[], int n)
{
	for (int i = 1; i <= n - 1; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			if (a[i] < a[j])
				swap(a[i], a[j]);
		}
	}
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
	return ;
}

int main()
{
	int  n= 0;
	int a[10000] = {};
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sort(a,n);
	system("pause");
	return 0;
}

#include <iostream>
#define LL long long

using namespace std;

int n, h, qx[100001], zx[100001];

void Find(int qxl, int zxl) {
  if (qxl > n || zxl > n) {
    return;
  }
  int i;
  for (i = qxl; qx[qxl] != zx[i]; i++)
    ;
  Find(qxl + 1, zxl), Find(i + 1, i + 1);
  cout << qxl << " ";
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> qx[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> zx[i];
  }
  Find(1, 1);
  return 0;
}

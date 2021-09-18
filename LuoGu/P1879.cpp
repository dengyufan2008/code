#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int m, n, a[12][12], d[2][1 << 12];

int M(int x, int y) {
  return (x + y + !((m + n) & 1)) & 1;
}

int main() {
  cin >> m >> n;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      
    }
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

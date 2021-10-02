#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int m, f[100001] = {0, 1};

int main() {
  freopen("t1.in", "r", stdin);
  freopen("t1.out", "w", stdout);
  cin >> m;
  fill(&f[2], &f[m] + 1, 0x7fffffff);
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j * j * j * j <= i; j++) {
      f[i] = min(f[i], f[i - j * j * j * j] + 1);
    }
  }
  cout << f[m] << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

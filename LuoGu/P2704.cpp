#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, m, ans, d[2][4][1024] = {1};
bool b, a[101][11];
char ch;

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> ch;
      a[i][j] = ch == 'P';
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      b ^= 1;
      fill(&d[b][0][0], &d[b][3][1024], 0);
      for (int k = 0; k < 4; k++) {
        for (int l = 0; l < 1024; l++) {
          int _k = ((k & (1 << m - 1)) > 0) * 2 + ((k & (1 << m - 2)) > 0);
          
        }
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 1024; j++) {
      ans += d[b][i][j];
    }
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

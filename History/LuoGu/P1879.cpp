#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

const int kMod = 100000000;
int n, m, ans, a[12][12], d[2][4096] = {1};
bool b = 1;

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      fill(&d[b][0], &d[b][1 << m], 0);
      b ^= 1;
      for (int k = 0; k < (1 << m); k++) {
        bool l = (j > 0) * ((1 << m - 1) & k), u = (i > 0) * (1 & k);
        d[b ^ 1][k >> 1] = (d[b ^ 1][k >> 1] + d[b][k]) % kMod;
        if (!u && !l && a[i][j]) {
          d[b ^ 1][(k >> 1) + (1 << m - 1)] = (d[b ^ 1][(k >> 1) + (1 << m - 1)] + d[b][k]) % kMod;
        }
      }
    }
  }
  for (int i = 0; i < (1 << m); i++) {
    ans = (ans + d[b ^ 1][i]) % kMod;
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

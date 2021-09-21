#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

const int kMod = 100000000;
int n, m, ans, a[12][12], d[2][4096];
bool b;

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  d[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      b ^= 1;
      fill(&d[b][0], &d[b][4096], 0);
      for (int k = 0; k < (1 << m); k++) {
        bool l = (j > 0) * ((1 << (j - 1)) & k), u = (1 << j) & k;
        if ((i || !u) && (j || !l)) {
          if (!u) {
            d[b][k] = (d[b][k] + d[b ^ 1][k]) % kMod;
          }
          if (u || !l && a[i][j]) {
            d[b][k ^ (1 << j)] = (d[b][k ^ (1 << j)] + d[b ^ 1][k]) % kMod;
          }
        }
      }
    }
  }
  for (int i = 0; i < (1 << m); i++) {
    ans = (ans + d[b][i]) % kMod;
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

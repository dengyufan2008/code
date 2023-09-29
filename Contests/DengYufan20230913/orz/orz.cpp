#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("orz.in");
ofstream cout("orz.out");

const int kMaxN = 1e6 + 1;
int n, ans;
vector<int> a[kMaxN], f[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 0; i < kMaxN; i++) {
    a[i].resize(1);
  }
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x >> y;
    a[y].push_back(x);
  }
  for (int i = 0; i < kMaxN; i++) {
    sort(a[i].begin(), a[i].end());
    a[i].push_back(kMaxN);
    f[i].resize(a[i].size());
  }
  for (int o = 0; o < 2; o++) {  // 0:偶入奇出
    for (int i = 1; i < kMaxN; i++) {
      fill(f[i].begin(), f[i].end(), 0);
      if (i & 1 ^ o) {  // 出
        for (int j = a[i].size() - 1, k = a[i - 1].size() - 2; j >= 1 && k >= 0; j--) {
          for (; k >= 0 && a[i - 1][k] > a[i][j]; k--) {
          }
          if (k >= 0 && a[i - 1][k] <= a[i][j]) {
            f[i][a[i].size() - j - 1] = f[i - 1][k] + a[i].size() - j - 1;
          }
        }
      } else {
        for (int j = 0, k = 1; j < a[i].size() - 1 && k < a[i - 1].size(); j++) {
          for (; k < a[i - 1].size() && a[i - 1][k] < a[i][j]; k++) {
          }
          if (k < a[i - 1].size() && a[i - 1][k] >= a[i][j]) {
            f[i][j] = f[i - 1][a[i - 1].size() - k - 1] + j;
          }
        }
      }
      for (int j = 1; j < a[i].size() - 1; j++) {
        f[i][j] = max(f[i][j], f[i][j - 1]);
      }
    }
    ans += f[kMaxN - 1][a[kMaxN - 1].size() - 2];
  }
  cout << ans - n;
  return 0;
}

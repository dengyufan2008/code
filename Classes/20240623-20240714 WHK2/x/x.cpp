#include <fstream>
#include <vector>

using namespace std;

ifstream cin("x.in");
ofstream cout("x.out");

const int kInf = 1e9;
int n, m[2], ans;
char c, p;
vector<int> a[2];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int o : {0, 1}) {
    for (int i = 0; i < n; i++) {
      cin >> c;
      !i && c == '1' ? a[o].push_back(0) : void();
      i && c != p ? a[o].push_back(i) : void();
      p = c;
    }
    c == '1' ? a[o].push_back(n) : void();
  }
  a[0].size() > a[1].size() ? a[0].swap(a[1]) : void();
  m[0] = a[0].size(), m[1] = a[1].size(), ans = kInf;
  for (int i = -m[0]; i <= m[1]; i += 2) {
    int w = 0;
    for (int j = min(0, -i); j < max(m[0], m[1] - i); j++) {
      int w1, w2;
      w1 = j < 0 ? 0 : j >= m[0] ? n : a[0][j];
      w2 = j < -i ? 0 : j >= m[1] - i ? n : a[1][j + i];
      w += abs(w1 - w2);
    }
    ans = min(ans, w);
  }
  cout << ans << '\n';
  return 0;
}

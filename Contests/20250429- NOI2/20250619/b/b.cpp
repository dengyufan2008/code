#include <fstream>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 33;
int t;
pair<int, int> ans[kMaxN + 1];

void Solve(int a, int b, int c, int x, int y, int z, int t) {
  if (c & 1) {
    if (a & 1 ^ 1) {
      swap(a, c), swap(x, z);
    } else {
      swap(b, c), swap(y, z);
    }
  }
  if (a > b) {
    swap(a, b), swap(x, y);
  }
  ans[t] = {x, y};
  if (t < kMaxN) {
    Solve(a, b - a >> 1, c >> 1, t, y, z, t + 1);
  }
  !ans[t].first && (ans[t].first = kMaxN);
  !ans[t].second && (ans[t].second = kMaxN);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> ans[3].first;
  for (int u = 1, a, b, x, y, z; u <= t; u++) {
    cin >> a >> b;
    Solve(a, b, (1U << kMaxN - 2) - a - b, 1, 2, 0, 3);
    cout << kMaxN << ' ' << kMaxN << '\n';
    for (int i = 3; i <= kMaxN; i++) {
      cout << ans[i].first << ' ' << ans[i].second << '\n';
      ans[i] = {0, 0};
    }
    cout << '\n';
  }
  return 0;
}

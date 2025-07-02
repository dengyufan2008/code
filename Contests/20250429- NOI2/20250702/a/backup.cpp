// 现在是 WA 的. 差是偶数的情况需要分讨 0 和 2.
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1;
struct V {
  int f, g;
  bool ans;
  vector<int> e;
} v[kMaxN];
int t, o, n, ans;

void Dp(int f, int x) {
  static vector<int> e;
  for (int i : v[x].e) {
    if (i != f) {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();

  v[x].f = 1, v[x].g = -1;
  if (v[x].e.empty()) {
    v[x].g = 0;
    return;
  }
  for (int i : v[x].e) {
    Dp(x, i);
  }
  for (int u = 2; u >= 0; u--) {
    for (int i : v[x].e) {
      if (v[i].f - v[i].g == u) {
        if (v[x].f == v[x].g) {
          v[x].f += v[i].f, v[x].g += v[i].g;
        } else {
          v[x].f += v[i].g, v[x].g += v[i].f;
          v[i].ans = 1;
        }
      }
    }
  }
  ans = max(ans, max(v[x].f, v[x].g));
}

void CalcAns(int x) {
  for (int i : v[x].e) {
    v[i].ans ^= v[x].ans;
    CalcAns(i);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> o;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      v[i].ans = 0, v[i].e.clear();
    }
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    ans = 0, Dp(0, 1);
    cout << ans << '\n';
    if (o >= 2) {
      CalcAns(1);
      for (int i = 1; i <= n; i++) {
        cout << v[i].ans << " \n"[i == n];
      }
    }
  }
  return 0;
}

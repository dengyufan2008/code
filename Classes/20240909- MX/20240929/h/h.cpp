#include <fstream>
#include <queue>

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");

const int kMaxN = 2e5 + 1;
struct V {
  int f, c;
  bool o, s;
  vector<int> e;
} v[kMaxN];
int n;
priority_queue<int, vector<int>, greater<int>> q1, q2;

void T(int f, int x) {
  v[x].f = f, v[x].s = v[x].o, v[x].c = 0;
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i), v[x].s ^= v[i].s, v[x].c += v[i].s;
    }
  }
  v[x].o && !v[x].c ? q1.push(x) : void();
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    static char c;
    cin >> c, v[i].o = c == 'W';
  }
  T(0, 1);
  if (v[1].s ^ 1) {
    cout << -1 << '\n';
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    int x = q1.top(), f = v[x].f;
    v[x].c = n, q1.pop(), cout << x << " \n"[i == n];
    if (f) {
      v[f].o && !v[f].c ? q2.push(f) : void();
      v[f].o ^= 1, v[f].c += v[x].s ? -1 : 1;
      v[f].o && !v[f].c ? q1.push(f) : void();
    }
    for (int j : v[x].e) {
      if (j != v[x].f) {
        v[j].o ^= 1, v[j].s ^= 1;
        if (!v[j].c) {
          v[j].o ? q1.push(j) : q2.push(j);
        }
      }
    }
    while (!q2.empty() && q1.top() == q2.top()) {
      q1.pop(), q2.pop();
    }
  }
  return 0;
}

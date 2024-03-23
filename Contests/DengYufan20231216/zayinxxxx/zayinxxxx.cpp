#include <algorithm>
#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("zayinxxxx.in");
ofstream cout("zayinxxxx.out");

const LL kMaxN = 2e5 + 1, kInf = 1e18;
struct V {
  int a, b, p;

  int W(int x) {
    return x ? a + b * (x - 1) : 0;
  }
} v[kMaxN];
struct A {
  int x, w;

  bool operator<(const A &a) const {
    return w < a.w || w == a.w && x > a.x;
  }

  bool operator==(const A &a) const {
    return x == a.x && w == a.w;
  }
};
class Q {
 private:
  priority_queue<A> a, b;

  void Update() {
    while (!b.empty() && a.top() == b.top()) {
      a.pop(), b.pop();
    }
  }

 public:
  void Push(int x, int w) { a.push({x, w}); }

  void Erase(int x, int w) { b.push({x, w}); }

  bool Empty() { return a.size() == b.size(); }

  int Size() { return a.size() - b.size(); }

  A Top() { return Update(), a.top(); }
} q[4][4];
int n, m, p[4];
LL s, ans, d[4];

void Init() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].a >> v[i].b;
  }
  sort(v + 1, v + n + 1, [](V i, V j) { return i.a > j.a; });
  for (int i = 1; i <= n && i * 2 <= m && v[i].a > 0; i++) {
    s += v[i].a;
  }
  ans = s, s = 0;
  if (n >= m) {
    sort(v + 1, v + n + 1, [](V i, V j) { return i.a + i.b * 2 > j.a + j.b * 2; });
    for (int i = 1; i <= m; i++) {
      s += v[i].a + v[i].b * 2;
    }
    ans = max(ans, s), s = 0;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= 3; j++) {
      q[0][j].Push(i, v[i].W(j));
    }
  }
}

/*
警钟撅烂 !!!!!
最长路不能使用 Dij , 反例:
1 2 2
1 3 1
2 4 2
3 4 4
*/
void Floyd(bool o) {
  LL w[4][4] = {};
  for (int i = 0; i <= 3; i++) {
    for (int j = 0; j <= 3; j++) {
      if (i != j) {
        if (o) {
          w[j][i] = q[i][j].Empty() ? -kInf : q[i][j].Top().w;
        } else {
          w[i][j] = q[i][j].Empty() ? -kInf : q[i][j].Top().w;
        }
      }
    }
  }
  d[0] = 0, d[1] = d[2] = d[3] = -kInf;
  for (int i = 0; i <= 3; i++) {
    for (int j = 0; j <= 3; j++) {
      for (int k = 0; k <= 3; k++) {
        if (d[k] < d[j] + w[j][k]) {
          d[k] = d[j] + w[j][k], p[k] = j;
        }
      }
    }
  }
}

void Reverse(int x, int y) {
  A t = q[x][y].Top();
  s += t.w, v[t.x].p = y;
  for (int i = 0; i <= 3; i++) {
    if (i != x) {
      q[x][i].Erase(t.x, v[t.x].W(i) - v[t.x].W(x));
    }
    if (i != y) {
      q[y][i].Push(t.x, v[t.x].W(i) - v[t.x].W(y));
    }
  }
}

/// @param x Vertice
/// @param o Forced Or Not
/// @param t Increase(0) Or Decrease(1)
/// @return Seccess Or Not
bool Change(int x, bool o, bool t) {
  Floyd(t);
  if (!o && d[x] <= 0) {
    return 0;
  }
  for (int i = x; i; i = p[i]) {
    t ? Reverse(i, p[i]) : Reverse(p[i], i);
  }
  return 1;
}

void Calc() {
  if (n >= 2 && m >= 3) {
    Change(2, 1, 0), Change(2, 1, 0);
    for (; q[1][0].Size() < min(n - 2, m - 3 >> 1) && Change(1, 0, 0);) {
    }
    ans = max(ans, s);
    for (int i = 1; i <= min(n - 2, m - 3); i++) {
      int j = min(n - i - 2, m - i - 3 >> 1);
      for (; q[1][0].Size() > j; Change(1, 1, 1)) {
      }
      Change(3, 1, 0);
      for (; Change(1, 0, 1);) {
      }
      ans = max(ans, s);
    }
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Calc();
}

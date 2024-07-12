#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 3e5 + 1;
struct A {
  LL w;
  int d;
  A() : w(0), d(0) {}
  A(LL _w, int _d) : w(_w), d(_d) {}
  bool operator<(const A &a) const {
    return w > a.w;
  }
};
struct E {
  int x, y;
  LL w;
} e[kMaxN];
struct V {
  int f, s;
  LL w, t;
  priority_queue<A> q;
} v[kMaxN];
int n, m;
priority_queue<int, vector<int>, greater<int>> q;
vector<int> ans;

int GetRoot(int x) { return v[x].f == x ? x : v[x].f = GetRoot(v[x].f); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].w;
    v[i].f = i, v[i].s = 1;
  }
  for (int i = 1; i <= m; i++) {
    cin >> e[i].x >> e[i].y >> e[i].w;
    LL w = e[i].w - e[i].x - e[i].y;
    if (w > 0) {
      v[e[i].x].q.emplace(w >> 1, i);
      v[e[i].y].q.emplace(w >> 1, i);
    } else {
      q.push(i);
    }
  }
  for (int o; !q.empty();) {
    o = q.top(), q.pop(), ans.push_back(o);
    int x = GetRoot(e[o].x), y = GetRoot(e[o].y);
    v[x].s < v[y].s ? swap(x, y) : void();
    v[x].t += v[y].w, v[y].t += v[x].w;
    for (A i; !v[y].q.empty();) {
      i = v[y].q.top(), v[y].q.pop();
      v[x].q.emplace(i.w - v[y].t + v[x].t, i.d);
    }
    for (A i; !v[x].q.empty();) {
      i = v[x].q.top();
      if (i.w <= v[x].t) {
        v[x].q.pop();
      }
    }
  }
  return 0;
}

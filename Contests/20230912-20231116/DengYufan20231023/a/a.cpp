#include <iostream>
#include <queue>
#define LL long long

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const int kMaxN = 1e5 + 1, kMaxM = 1e6 + 1;
const LL kInf = 1e18;
struct E {
  int p, d, w;
} e[kMaxM << 1];
struct V {
  int t, l, r, et;
  LL d = kInf;
} v[kMaxN];
int n, m, s, t;
priority_queue<pair<LL, int>> q;

void Update(int x, LL d) {
  if (d % v[x].t < v[x].l) {
    d += v[x].l - d % v[x].t;
  } else if (d % v[x].t > v[x].r) {
    d += v[x].l - d % v[x].t + v[x].t;
  }
  if (v[x].d > d) {
    v[x].d = d, q.push({-d, x});
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> s >> t;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].t >> v[i].l >> v[i].r;
  }
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    e[i << 1] = {v[x].et, y, z}, v[x].et = i << 1;
    e[i << 1 | 1] = {v[y].et, x, z}, v[y].et = i << 1 | 1;
  }
  for (Update(s, 0); !q.empty();) {
    int x = q.top().second;
    q.pop();
    for (int i = v[x].et; i; i = e[i].p) {
      Update(e[i].d, v[x].d + e[i].w);
    }
  }
  cout << v[t].d;
  return 0;
}

#include <iostream>
#include <queue>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const LL kMaxN = 2e5 + 1, kInf = 1e18;
struct E {
  LL p, d, w;
} e[kMaxN * 22];
struct V {
  LL et, d;
} v[kMaxN * 6];
LL n, m, k;
priority_queue<pair<LL, LL>> q;

void AddEdge(LL x, LL y, LL z, bool b) {
  if (b) {
    x += n * 3, y += n * 3;
  }
  e[++k] = {v[x].et, y, z}, v[x].et = k;
}

void Update(LL x, LL d) {
  if (v[x].d > d) {
    v[x].d = d, q.push({-d, x});
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n * 6; i++) {
    v[i].d = kInf;
  }
  AddEdge(1, 1 + n * 2, 0, 0), AddEdge(1, 1 + n * 2, 0, 1);
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    AddEdge(x, y, z, 0), AddEdge(y, x, z, 0);
    AddEdge(x + n, y + n, z, 0), AddEdge(y + n, x + n, z, 0);
    AddEdge(x + n * 2, y + n * 2, z, 0), AddEdge(y + n * 2, x + n * 2, z, 0);
    AddEdge(x, y + n, 0, 0), AddEdge(y, x + n, 0, 0);
    AddEdge(x + n, y + n * 2, z * 2, 0), AddEdge(y + n, x + n * 2, z * 2, 0);
    AddEdge(x, y, z, 1), AddEdge(y, x, z, 1);
    AddEdge(x + n, y + n, z, 1), AddEdge(y + n, x + n, z, 1);
    AddEdge(x + n * 2, y + n * 2, z, 1), AddEdge(y + n * 2, x + n * 2, z, 1);
    AddEdge(x, y + n, z * 2, 1), AddEdge(y, x + n, z * 2, 1);
    AddEdge(x + n, y + n * 2, 0, 1), AddEdge(y + n, x + n * 2, 0, 1);
  }
  for (Update(1, 0); !q.empty();) {
    int t = q.top().second;
    q.pop();
    for (int i = v[t].et; i; i = e[i].p) {
      Update(e[i].d, v[t].d + e[i].w);
    }
  }
  for (Update(1 + n * 3, 0); !q.empty();) {
    int t = q.top().second;
    q.pop();
    for (int i = v[t].et; i; i = e[i].p) {
      Update(e[i].d, v[t].d + e[i].w);
    }
  }
  for (int i = 2; i <= n; i++) {
    cout << min(v[i + n * 2].d, v[i + n * 5].d) << ' ';
  }
  return 0;
}

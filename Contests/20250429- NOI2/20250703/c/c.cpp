#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const LL kMaxN = 1e5 + 1, kInf = 1e18;
struct V {
  int s, d, l;
  LL w, add, *f, *tag;
  vector<int> e;
} v[kMaxN];
int t, u, n;
LL *h, tmp[kMaxN * 20];

void Init(int f, int x) {
  v[x].s = 1, v[x].d = v[f].d + 1;
  v[x].l = v[x].w = v[x].add = 0;
  for (int &i : v[x].e) {
    if (i != f) {
      Init(x, i);
      v[x].s += v[i].s;
      v[x].w += v[i].w + v[i].s;
      if (v[x].l < v[i].l) {
        v[x].l = v[i].l;
        swap(v[x].e[0], i);
      }
    }
  }
  v[x].l++;
}

void Dp(int f, int x, bool o) {
  if (o) {
    v[x].f = h, h += v[x].l, v[x].tag = h, h += v[x].l;
    fill(&v[x].f[0], &v[x].f[v[x].l], 0);
    fill(&v[x].tag[0], &v[x].tag[v[x].l], 0);
  }
  if (!v[x].e.empty() && v[x].e[0] != f) {
    v[v[x].e[0]].f = v[x].f + 1, v[v[x].e[0]].tag = v[x].tag + 1;
    Dp(x, v[x].e[0], 0), v[x].f[0] = v[v[x].e[0]].w + v[v[x].e[0]].s;
    v[x].add += v[v[x].e[0]].add, v[x].f[0] -= v[v[x].e[0]].add;
    v[x].add += v[x].w - v[v[x].e[0]].w - v[v[x].e[0]].s;
    v[x].tag[0] += v[x].s - v[v[x].e[0]].s;
    if (v[x].d < v[x].l) {
      v[x].tag[v[x].d] -= v[x].s - v[v[x].e[0]].s;
    }
  }
  for (int i : v[x].e) {
    if (i != f && i != v[x].e[0]) {
      Dp(x, i, 1);
      v[i].add += v[x].w - v[i].w - v[i].s;
      if (v[x].d >= 1) {
        v[i].add += v[x].s - v[i].s, v[i].tag[0] += v[x].s - v[i].s;
        if (v[x].d <= v[i].l) {
          v[i].tag[v[x].d - 1] -= v[x].s - v[i].s;
        }
      }
      LL add = v[i].add, tag = 0;
      for (int j = 0; j < v[i].l; j++) {
        v[i].f[j] += add;
        tag += v[i].tag[j];
        add += tag;
      }
      add = v[x].add, tag = 0;
      for (int j = 0; j < v[i].l; j++) {
        tag += v[x].tag[j];
        add += tag;
        v[i].f[j] -= add;
      }
      for (int j = 0; j < v[i].l; j++) {
        v[x].f[j + 1] = min(v[x].f[j + 1], v[i].f[j]);
      }
    }
  }
}

LL CalcAns(int x) {
  h = tmp, Init(0, x), Dp(0, x, 1);
  LL ans = kInf, add = v[x].add, tag = 0;
  for (int i = 0; i < v[x].l; i++) {
    v[x].f[i] += add;
    tag += v[x].tag[i];
    add += tag;
    ans = min(ans, v[x].f[i]);
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> u, v[0].d = -1;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      v[i].e.clear();
    }
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    if (u == 1) {
      LL ans = kInf;
      for (int i = 1; i <= n; i++) {
        ans = min(ans, CalcAns(i));
      }
      cout << ans << '\n';
    } else if (u == 2) {
      cout << CalcAns(1) << '\n';
    } else {
      for (int i = 1; i <= n; i++) {
        cout << CalcAns(i) << " \n"[i == n];
      }
    }
  }
  return 0;
}

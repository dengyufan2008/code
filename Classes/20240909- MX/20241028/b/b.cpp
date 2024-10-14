#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e5 + 1;
int n, m, w;
LL a[kMaxN], b[kMaxN], c[kMaxN];

namespace CalcABC {
struct V {
  int f;
  LL d;
  vector<pair<int, int>> e;
} v[kMaxN];
int s, t;
LL mx;

void CalcD(int f, int x) {
  mx = max(mx, v[x].d);
  for (auto i : v[x].e) {
    if (i.first != f) {
      v[i.first].f = x;
      v[i.first].d = v[x].d + i.second;
      CalcD(x, i.first);
    }
  }
}

void Solve() {
  m = 1;
  for (int i = 1; i <= n; i++) {
    v[i].e.clear();
  }
  for (int i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
  mx = v[1].f = v[1].d = 0, CalcD(0, 1), s = 1;
  for (int i = 2; i <= n; i++) {
    v[s].d < v[i].d && (s = i);
  }
  mx = v[s].f = v[s].d = 0, CalcD(0, s), t = 1;
  for (int i = 2; i <= n; i++) {
    v[t].d < v[i].d && (t = i);
  }
  for (int i = t, f; i != s; i = f) {
    m++, f = v[i].f, mx = 0;
    for (auto j : v[f].e) {
      if (j.first == i) {
        a[m] = a[m - 1] + j.second;
      } else if (j.first != v[f].f) {
        v[j.first].d = j.second, CalcD(f, j.first);
      }
    }
    b[m] = mx - a[m], c[m] = mx + a[m];
  }
}
}  // namespace CalcABC

namespace CalcAns {
const LL kInf = 2e14;
LL bb, bc, cb, cc;

void CalcBC(LL x) {
  int h = 1, t = 0;
  LL mxb = -kInf, mxc = -kInf;
  static pair<LL, LL> q[kMaxN];
  bb = bc = cb = cc = -kInf;
  for (int i = 1; i <= m; i++) {
    for (; h <= t && q[h].first + c[i] > x; h++) {
      mxb = max(mxb, q[h].first);
      mxc = max(mxc, q[h].second);
    }
    bb = max(bb, mxb + b[i]), bc = max(bc, mxb + c[i]);
    cb = max(cb, mxc + b[i]), cc = max(cc, mxc + c[i]);
    for (; t >= h && q[t].first <= b[i]; t--) {
    }
    q[++t] = {b[i], c[i]};
  }
}

bool Check(LL x) {
  int l1 = m, r1 = m, l2 = 1, r2 = 1;  // (l1, r1], [l2, r2)
  cc = cc + w - x, bb = x - bb - w;
  bc = bc + w - x, cb = x - cb - w;
  for (int i = 1; i <= m; i++) {
    for (; l1 >= 1 && a[l1] >= cc - a[i]; l1--) {
    }
    for (; r1 >= 1 && a[r1] > bb - a[i]; r1--) {
    }
    for (; l2 <= m && a[l2] < bc + a[i]; l2++) {
    }
    for (; r2 <= m && a[r2] <= cb + a[i]; r2++) {
    }
    if (max(max(l1 + 1, l2), i) <= min(r1, r2 - 1)) {
      return 1;
    }
  }
  return 0;
}

void Solve() {
  LL l = 0, r = kInf;
  while (l <= r) {
    LL mid = l + r >> 1;
    if (CalcBC(mid), Check(mid)) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << l << '\n';
}
}  // namespace CalcAns

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> w;
  while (n || w) {
    CalcABC::Solve(), CalcAns::Solve();
    cin >> n >> w;
  }
  return 0;
}

#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1;
struct V {
  int s;
  bool ans;
  vector<int> e;
} v[kMaxN];
vector<int> l[kMaxN];
int t, o, n, m, r;

void FindR(int f, int x) {
  int mx = 0;
  v[x].s = v[x].e.size() == 1;
  for (int i : v[x].e) {
    if (i != f) {
      FindR(x, i), v[x].s += v[i].s;
      mx = max(mx, v[i].s);
    }
  }
  if (v[x].e.size() > 1 && max(mx, m - v[x].s) <= m >> 1) {
    r = x;
  }
}

void CalcChain(int f, int x, int p) {
  v[x].s = 0, l[p].push_back(x);
  if (v[x].e.size() == 1) {
    v[x].s = 1;
    return;
  }
  for (int i : v[x].e) {
    if (i != f) {
      CalcChain(x, i, p + v[x].s);
      v[x].s += v[i].s;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> o;
  while (t--) {
    cin >> n, m = 0;
    for (int i = 1; i <= n; i++) {
      v[i].e.clear();
    }
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    for (int i = 1; i <= n; i++) {
      m += v[i].e.size() == 1;
    }
    cout << (m + 1 >> 1) << '\n';
    if (o == 1) {
      continue;
    } else if (n == 2) {
      cout << 0 << ' ' << 1 << '\n';
      continue;
    }
    for (int i = 1; i <= m + 1; i++) {
      l[i].clear();
    }
    FindR(0, 1), CalcChain(0, r, 1);
    for (int i = 1, j = m + 3 >> 1; i <= m + 1 >> 1; i++, j++) {
      reverse(l[i].begin(), l[i].end());
      l[i].insert(l[i].end(), l[j].begin(), l[j].end());
    }
    for (int i = 1, j = 0; i <= m + 1 >> 1; i++) {
      for (int x : l[i]) {
        v[x].ans = j, j ^= 1;
      }
    }
    for (int i = 1; i <= n; i++) {
      cout << v[i].ans << " \n"[i == n];
    }
  }
  return 0;
}

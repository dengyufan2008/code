#include <fstream>
#include <map>
#include <queue>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxL = 2001, kMaxN = 101, kMaxM = 2001;
struct V {
  int l, c;
  map<int, int> e;
} v[kMaxL];
int l, n, m, w, a[kMaxM], q[kMaxL];
vector<int> s[kMaxN];

void Input() {
  int shit[kMaxL];
  cin >> l >> n >> m >> w;
  for (int i = 2; i <= l; i++) {
    cin >> shit[i];
  }
  for (int i = 2, x; i <= l; i++) {
    cin >> x;
    v[x].e[shit[i]] = i;
  }
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    for (int j = 1, y; j <= x; j++) {
      cin >> y;
      s[i].push_back(y);
    }
  }
  for (int i = 1; i <= m; i++) {
    cin >> a[i];
  }
}

void CalcNt() {
  int h, t;
  for (h = t = q[1] = 1; h <= t; h++) {
    int x = q[h], y, z;
    for (auto i : v[x].e) {
      y = i.second, q[++t] = y;
      for (z = v[x].l; z && !v[z].e.count(i.first); z = v[z].l) {
      }
      v[y].l = z ? v[z].e[i.first] : 1;
    }
  }
}

void Match() {
  int p = 1;
  for (int i = 1; i <= m; i++) {
    for (int j : s[a[i]]) {
      for (; p && !v[p].e.count(j); p = v[p].l) {
      }
      p = p ? v[p].e[j] : 1, v[p].c++;
    }
  }
  for (int i = l; i >= 1; i--) {
    v[v[q[i]].l].c += v[q[i]].c;
  }
  for (int i = 2; i <= l; i++) {
    cout << v[i].c << " \n"[i == l];
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), CalcNt(), Match();
  return 0;
}

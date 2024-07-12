#include <fstream>
#include <vector>

using namespace std;

ifstream cin("construct.in");
ofstream cout("construct.out");

const int kMaxN = 1e5 + 1;
struct A {
  int x, y, z;
} a[kMaxN];
struct V {
  int i;
  vector<int> e, g;
} v[kMaxN];
int n, m, t, e[kMaxN], q[kMaxN], p[kMaxN], ans[kMaxN];
bool b[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> a[i].x >> a[i].y >> a[i].z;
    v[a[i].x].e.push_back(i), v[a[i].z].e.push_back(i);
    e[i] = a[i].y, v[a[i].y].i++;
  }
  for (int i = 1; i <= n; i++) {
    if (!v[i].i) {
      q[++t] = i, p[i] = t;
    }
  }
  for (int h = 1; h <= t; h++) {
    for (int i : v[q[h]].e) {
      if (e[i] > 0 && !--v[e[i]].i) {
        q[++t] = e[i], p[e[i]] = t;
      }
      e[i] = -e[i];
    }
  }
  for (int i = 1; i <= m; i++) {
    if (p[a[i].x] > p[a[i].z]) {
      swap(a[i].x, a[i].z);
    }
    v[min(p[a[i].y], p[a[i].z])].g.push_back(i);
  }
  for (int i = 1, l = 1, r = n; i <= n; i++) {
    int s[2] = {0, 0};
    for (int j : v[i].g) {
      s[b[p[a[j].x]] ^ (p[a[j].y] > p[a[j].z])]++;
    }
    if (s[0] >= s[1]) {
      ans[q[i]] = l++, b[i] = 0;
    } else {
      ans[q[i]] = r--, b[i] = 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " \n"[i == n];
  }
  return 0;
}

#include <bitset>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("ya.in");
ofstream cout("ya.out");

const int kMaxN = 3001;
struct V {
  int d, c1, c2;  // c1:从下往上连的 c2:从上往下连的
  bool b;
  vector<int> e;
} v[kMaxN];
int n, m, k, ans;
bitset<kMaxN> b[kMaxN];

bool T(int f, int x) {
  if (v[x].d) {
    return 0;
  }
  v[x].d = ++k;
  for (int i : v[x].e) {
    if (i != f) {
      if (!v[i].d) {
        v[x].b |= T(x, i);
      } else if (v[i].d < v[x].d) {
        v[x].c1++, v[i].c2++;
      }
    }
  }
  if (!v[x].b && !v[x].c2) {
    v[x].b = 1, ans++;
  } else {
    v[x].b = 0;
    for (int i : v[x].e) {
      if (i != f && v[i].d && v[i].d < v[x].d) {
        v[x].c1--, v[i].c2--;
      }
    }
  }
  return v[x].b;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    b[max(x, y)][min(x, y)] = 1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      if (!b[i][j]) {
        v[i].e.push_back(j), v[j].e.push_back(i);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    T(0, i);
  }
  cout << ans << '\n';
  for (int i = 1; i <= n; i++) {
    if (v[i].b) {
      cout << i << ' ';
    }
  }
  return 0;
}

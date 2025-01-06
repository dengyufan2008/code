#include <fstream>
#include <vector>

using namespace std;

ifstream cin("k.in");
ofstream cout("k.out");

const int kMaxN = 5000;
struct V {
  int p, n;
} v[kMaxN];
int n, mn, ans, mx[kMaxN];
bool a1[kMaxN], a2[kMaxN], b[kMaxN][kMaxN];
vector<int> p[kMaxN << 1];

void Input() {
  int m1, m2;
  cin >> m1 >> m2 >> n;
  for (int i = 1, x, y; i <= m1; i++) {
    cin >> x >> y, a1[x] = a2[y] = 1;
  }
  for (int i = 1, x, y; i <= m2; i++) {
    cin >> x >> y, b[x][y] = 1, mx[y] = max(mx[y], x);
  }
}

int Dis(int x) { return x <= 0 ? x + n : x; }

void Calc() {
  mn = n - 1, ans = n * n;
  for (; !a1[mn]; mn--) {
  }
  for (int i = 0, u, w; i < n; i++) {
    for (int j = mn; j < i + n; j++) {
      p[j].clear();
    }
    for (int j = 0; j < n; j++) {
      if (!a2[j] && mx[j] > mn) {
        p[mx[j]].push_back(j);
      }
    }
    w = 0;
    for (u = n - 1; !a2[u] && mx[u] <= mn; u--) {
    }
    for (int j = 0; j < n; j++) {
      if (a2[j] || mx[j] > mn) {
        v[j].p = u, v[u].n = j;
        w = max(w, Dis(j - u)), u = j;
      }
    }
    for (int j = mn; j < i + n; j++) {
      for (int k : p[j]) {
        v[v[k].p].n = v[k].n, v[v[k].n].p = v[k].p;
        w = max(w, Dis(v[k].n - v[k].p));
      }
      ans = min(ans, (j - i + 1) * (n - w + 1));
    }
    a1[i] && (mn = i + n);
    for (int j = 0; j < n; j++) {
      b[i][j] && (mx[j] = i + n);
    }
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), Calc();
  return 0;
}

#include <iostream>
#include <vector>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const LL kMaxN = 5e5 + 1, kInf = 1e18;
struct V {
  LL f[2][2][2];  // 上传/无所谓 用过a/无所谓 用过b/无所谓
  vector<int> e;
} v[kMaxN];
int n, a, b;
LL g[2][2][2];  // 选了奇/偶个上传的

void Update(LL &x, LL y) { x = min(x, min(y, kInf)); }

void T(int f, int x) {
  v[x].f[0][0][0] = 0, fill(&v[x].f[0][0][1], &v[x].f[2][0][0], kInf);
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i), fill(&g[0][0][0], &g[2][0][0], kInf);
      for (int s1 = 1; s1 >= 0; s1--) {
        for (int t1 = 1; t1 >= 0; t1--) {
          for (int s2 = 1; s2 >= 0; s2--) {
            for (int t2 = 1; t2 >= 0; t2--) {
              Update(g[0][1][t1 | t2], v[x].f[0][s1][t1] + v[i].f[0][s2][t2] + a);
              Update(g[0][s1 | s2][1], v[x].f[0][s1][t1] + v[i].f[1][s2][t2]);
              Update(g[0][s1 | s2][1], v[x].f[1][s1][t1] + v[i].f[1][s2][t2] - b);
              Update(g[0][s1 | s2][t1 | t2], v[x].f[1][s1][t1] + v[i].f[0][s2][t2]);
              Update(g[1][1][1], v[x].f[1][s1][t1] + v[i].f[0][s2][t2] + a);
              Update(g[1][s1 | s2][1], v[x].f[0][s1][t1] + v[i].f[0][s2][t2] + b);
              Update(g[1][s1 | s2][1], v[x].f[0][s1][t1] + v[i].f[1][s2][t2]);
              Update(g[1][s1 | s2][1], v[x].f[1][s1][t1] + v[i].f[1][s2][t2]);
            }
          }
        }
      }
      for (int r = 1; r >= 0; r--) {
        for (int s = 1; s >= 0; s--) {
          for (int t = 1; t >= 0; t--) {
            Update(g[0][s][t], g[r][s][t]);
            Update(g[r][0][t], g[r][s][t]);
            Update(g[r][s][0], g[r][s][t]);
          }
        }
      }
      copy(&g[0][0][0], &g[2][0][0], &v[x].f[0][0][0]);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> a >> b;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  T(0, 1);
  cout << min(min(v[1].f[0][0][0], v[1].f[0][1][1] - max(a, b)), min(v[1].f[0][1][0] - a, v[1].f[0][0][1] - b));
  return 0;
}

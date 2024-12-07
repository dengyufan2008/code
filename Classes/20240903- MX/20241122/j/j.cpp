#include <fstream>
#include <queue>

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const int kMaxN = 2e5 + 1;
struct V {
  int d, w, c, ans;
  vector<int> o, i;
} v[kMaxN];
int n, m, b[kMaxN], w[kMaxN];
queue<int> q;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].w;
  }
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y, v[x].o.push_back(y), v[y].i.push_back(x);
  }
  for (int i = 1; i <= n; i++) {
    v[i].d = v[i].o.size();
    !v[i].d ? q.push(i) : void();
  }
  for (; !q.empty(); q.pop()) {
    int x = q.front();
    for (int i : v[x].i) {
      if (!--v[i].d) {
        q.push(i);
        int o = v[i].o.size();
        for (int i = 0; i <= o; i++) {
          b[i] = 0;
        }
        for (int j : v[i].o) {
          b[v[j].c] = j;
        }
        for (int j = 0; j <= o; j++) {
          if (!b[j]) {
            v[i].c = j;
            break;
          }
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    w[v[i].c] ^= v[i].w, v[i].ans = v[i].w;
  }
  for (int i = n; i >= 0; i--) {
    if (w[i]) {
      int g = 31 - __builtin_clz(w[i]);
      cout << "WIN\n";
      for (int j = 1; j <= n; j++) {
        if (v[j].c == i && (v[j].w >> g & 1)) {
          v[j].ans = v[j].w ^ w[i];
          for (int k : v[j].o) {
            b[v[k].c] = k;
          }
          for (int k = 0; k < i; k++) {
            v[b[k]].ans = v[b[k]].w ^ w[k];
          }
          break;
        }
      }
      for (int j = 1; j <= n; j++) {
        cout << v[j].ans << " \n"[j == n];
      }
      return 0;
    }
  }
  cout << "LOSE\n";
  return 0;
}

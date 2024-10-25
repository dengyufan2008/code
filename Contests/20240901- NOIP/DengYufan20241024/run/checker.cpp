#include <fstream>

using namespace std;

ifstream cin("run.in");
ifstream cout("run.out");
ifstream cans("run.ans");
ofstream cres("run.txt");

const bool kIgnoreOdd = 0, kIgnoreAnsPath = 0;
const int kMaxN = 3e5 + 1;
int t, u, n, m, k, _k, c;
bool b[kMaxN], bb[kMaxN];
pair<int, int> e[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> u;
  for (int o = 1; o <= t; o++) {
    cin >> n >> m, c = 0;
    for (int i = 1; i <= n; i++) {
      bb[i] = 0;
    }
    for (int i = 1, x, y; i <= m; i++) {
      cin >> x >> y, e[i] = {x, y}, b[i] = 0;
    }
    cout >> k, cans >> _k;
    if ((k == -1) != (_k == -1)) {
      cres << "Wrong State On Case " << o << ".\n";
      return 0;
    }
    if (k != -1) {
      for (int i = 1, s, t, x; i <= k; i++) {
        cout >> s >> t >> x, c += x;
        if (bb[s] || bb[t]) {
          cres << "Twice Usage On Case " << o << ", Vertice " << (bb[s] ? s : t) << ".\n";
          return 0;
        }
        bb[s] = bb[t] = 1;
        if (!kIgnoreOdd && u && x % 2) {
          cres << "Odd Number Of Edges On Case " << o << ", Path " << i << ".\n";
          return 0;
        }
        for (int j = 1, y; j <= x; j++) {
          cout >> y;
          if (b[y]) {
            cres << "Twice Usage On Case " << o << ", Edge " << y << ".\n";
            return 0;
          }
          b[y] = 1;
          if (e[y].first != s && e[y].second != s) {
            cres << "Not Continuous On Case " << o << ", Path " << i << ", Edge " << j << ".\n";
            return 0;
          }
          s ^= e[y].first ^ e[y].second;
        }
        if (s != t) {
          cres << "Not Continuous On Case " << o << ", Path " << i << ", Edge " << x + 1 << ".\n";
          return 0;
        }
      }
      if (!kIgnoreAnsPath) {
        for (int i = 1, x; i <= _k; i++) {
          cans >> x >> x >> x;
          for (int j = 1, y; j <= x; j++) {
            cans >> y;
          }
        }
      }
      if (c != m) {
        cres << "Some Edge Not Used On Case " << o << ".\n";
        return 0;
      }
    }
  }
  cres << "Accepted.\n";
  return 0;
}

#include <fstream>
#include <vector>

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1;
struct V {
  int c, t;
  vector<int> e;
} v[kMaxN];
int t, n, m, ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    m = ans = 0;
    for (int i = 1; i <= n; i++) {
      v[i].c = v[i].t = 0, v[i].e.clear();
    }
    cin >> n;
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    for (int i = 1; i <= n; i++) {
      if (v[i].e.size() > 1) {
        m++, v[i].c -= v[i].e.size() - 1;
        for (int j : v[i].e) {
          v[j].c++, v[j].t++;
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j : v[i].e) {
        v[j].c += v[i].t;
      }
      v[i].t = v[i].e.size() > 1;
      for (int j : v[i].e) {
        v[i].t += v[j].e.size() > 1;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (v[i].c == m) {
        bool o = 1;
        for (int j : v[i].e) {
          if (v[j].t - (v[i].e.size() > 1) - (v[j].e.size() == 2) > 1) {
            o = 0;
            break;
          }
        }
        if (o) {
          ans |= v[i].e.size() == 2;
        }
      }
    }
    cout << (ans ? "Yes\n" : "No\n");
  }
  return 0;
}

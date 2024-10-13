#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1e5 + 1;
struct V {
  int p, b;
  vector<int> e;
} v[kMaxN];
int t, n, c[kMaxN];
LL ans;
vector<int> l;

void T(int x, int d) {
  c[d]++;
  for (int i : v[x].e) {
    T(i, d ? d - 1 : l.size() - 1);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    for (int i = 1; i <= n; i++) {
      v[i].b = 0, v[i].e.clear();
    }
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> v[i].p, v[v[i].p].e.push_back(i);
    }
    ans = 1LL * n * (n - 1) / 2;
    for (int i = 1, x; i <= n; i++) {
      if (v[i].b) {
        continue;
      }
      for (int j = i;; j = v[j].p) {
        if (v[j].b) {
          x = j;
          break;
        } else {
          v[j].b = i;
        }
      }
      if (v[x].b != i) {
        continue;
      }
      l.clear(), v[x].b = -i, l.push_back(x);
      for (int j = v[x].p; j != x; j = v[j].p) {
        v[j].b = -i, l.push_back(j);
      }
      for (int j = 0; j < l.size(); j++) {
        c[j] = 1;
      }
      for (int j = 0; j < l.size(); j++) {
        for (int k : v[l[j]].e) {
          if (v[k].b != -i) {
            T(k, j ? j - 1 : l.size() - 1);
          }
        }
      }
      for (int j = 0; j < l.size(); j++) {
        ans -= 1LL * c[j] * (c[j] - 1) / 2;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}

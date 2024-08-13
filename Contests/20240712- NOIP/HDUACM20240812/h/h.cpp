#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");

const int kMaxN = 2e5 + 1;
struct V {
  int mn, r[2];
  vector<int> e;
} v[kMaxN];
int t, n, m;

void S(int x) {
  v[x].mn = x;
  for (int i : v[x].e) {
    S(i), v[x].mn = min(v[x].mn, v[i].mn);
  }
}

void T(int x, int o) {
  v[x].r[o] = ++m;
  for (int i : v[x].e) {
    T(i, o);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    for (int i = 1; i <= n; i++) {
      v[i].e.clear();
    }
    cin >> n;
    for (int i = 2, x; i <= n; i++) {
      cin >> x, v[x].e.push_back(i);
    }
    S(1);
    for (int i = 1; i <= n; i++) {
      sort(v[i].e.begin(), v[i].e.end(), [](int i, int j) {
        return v[i].mn > v[j].mn;
      });
    }
    m = 0, T(1, 0);
    for (int i = 1; i <= n; i++) {
      reverse(v[i].e.begin(), v[i].e.end());
    }
    m = 0, T(1, 1);
    for (int i = 1; i <= n; i++) {
      cout << n + 1 - v[i].r[0] << ' ' << n + 1 - v[i].r[1] << " \n"[i == n];
    }
  }
  return 0;
}

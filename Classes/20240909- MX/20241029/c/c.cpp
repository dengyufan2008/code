#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 3e5 + 1;
struct V {
  int l;
  vector<int> e;
} v[kMaxN];
int t, n, s;
vector<int> l;

void S(int f, int x) {
  v[x].l = 1;
  for (int &i : v[x].e) {
    if (i != f) {
      S(x, i), v[x].l = max(v[x].l, v[i].l + 1);
      if (v[x].e[0] == f || v[v[x].e[0]].l < v[i].l) {
        swap(v[x].e[0], i);
      }
    }
  }
}

void T(int f, int x, bool o) {
  o ? l.push_back(v[x].l) : void();
  if (v[x].e.size() > 1) {
    T(x, v[x].e[0], 0);
  }
  for (int i : v[x].e) {
    if (i != f && i != v[x].e[0]) {
      T(x, i, 1);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n, l.clear();
    for (int i = 1; i <= n; i++) {
      v[i].e.clear();
    }
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    n--, s = v[1].e.front(), S(1, s), T(1, s, 1);
    sort(l.begin(), l.end(), greater<int>());
    cout << n - l.front() << " \n"[n == 1];
    for (int i = 1, j = n - l.front(); i < n; i++) {
      j > 0 && (j -= l[i * 2 - 1]);
      j > 0 && (j -= l[i * 2]);
      cout << j << " \n"[i == n - 1];
    }
  }
  return 0;
}

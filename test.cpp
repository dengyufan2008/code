#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 2e5 + 2, kMaxM = 4e5 + 3;
struct V {
  int d, l, s;
  bool b;
  vector<pair<int, int>> e;
} v[kMaxM];
int n, m;
bool ans[kMaxN];

void S(int f, int x) {
  static int k = 0;
  v[x].d = v[x].l = ++k, v[x].b = 1;
  for (auto i : v[x].e) {
    if (!v[i.first].b) {
      S(i.second, i.first);
      v[x].l = min(v[x].l, v[i.first].l);
      v[x].s += v[i.first].s + 1;
    } else if (i.second != f && v[x].d > v[i.first].d) {
      v[x].l = min(v[x].l, v[i.first].d);
      v[x].s++;
    }
  }
}

void T(int f, int x) {
  v[x].b = 1;
  for (auto i : v[x].e) {
    if (!v[i.first].b) {
      T(i.second, i.first);
    } else if (i.second != f) {
      ans[i.second] = 1;
    }
  }
  ans[f] = v[x].d > v[x].l || (v[x].s & 1 ^ 1);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n, n = n << 1 | 1;
  for (int i = 1, x, y; i <= n; i++) {
    cin >> x >> y;
    v[x].e.push_back({y + n, i});
    v[y + n].e.push_back({x, i});
  }
  for (int i = 1; i <= n << 1; i++) {
    if (!v[i].b) {
      S(0, i);
      if (v[i].s & 1) {
        if (!m) {
          m = i;
        } else {
          for (int i = 1; i <= n; i++) {
            cout << "NG\n";
          }
          return 0;
        }
      }
    }
  }
  for (int i = 1; i <= n << 1; i++) {
    v[i].b = 0;
  }
  T(0, m);
  for (int i = 1; i <= n; i++) {
    cout << (ans[i] ? "OK\n" : "NG\n");
  }
  return 0;
}

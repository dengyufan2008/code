#include <algorithm>
#include <fstream>
#include <map>
#include <unordered_set>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("tree.in");
ofstream cout("tree.out");

const int kMaxN = 481, kMaxM = 4, kMod = 1e9 + 7;
struct A {
  int x, y;
} a[kMaxM];
struct V {
  int s;
  bool b;
};
int n, lg, m;
LL ans;
vector<int> b;
map<int, V> d;
unordered_set<int> w, p;

int Lg(int x) {
  int ans = 0;
  for (; x; x >>= 1) {
    ans++;
  }
  return ans;
}

int Lca(int x, int y) {
  x > y ? swap(x, y) : void();
  int dx = Lg(x), dy = Lg(y);
  for (; dx < dy; dy--, y >>= 1) {
  }
  for (; x != y; dx--, dy--, x >>= 1, y >>= 1) {
  }
  return x == y ? x : x >> 1;
}

int Size(int x) {
  int _lg = Lg(x);
  return (1 << lg - _lg + 1) - 1 - max((x + 1 << lg - _lg) - max(x << lg - _lg, n + 1), 0);
}

void S(int x, int s) {
  if (p.count(x)) {
    return;
  }
  p.insert(x), d[x].b |= !s;
  if (d.count(x >> 1) && !w.count(x)) {
    w.insert(x), S(x >> 1, s), w.erase(x);
  }
  if (d.count(x << 1) && !w.count(x << 1)) {
    w.insert(x << 1), S(x << 1, s), w.erase(x << 1);
  }
  if (d.count(x << 1 | 1) && !w.count(x << 1 | 1)) {
    w.insert(x << 1 | 1), S(x << 1 | 1, s), w.erase(x << 1 | 1);
  }
  for (int i = 0; i < m; i++) {
    if ((s >> i & 1) && (a[i].x == x || a[i].y == x)) {
      S(x ^ a[i].x ^ a[i].y, s ^ 1 << i);
    }
  }
  p.erase(x);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> a[i].x >> a[i].y;
  }
  lg = Lg(n), ans = 1LL * n * n % kMod;
  for (int s = 1; s < 1 << m; s++) {
    b.clear(), b.push_back(1);
    for (int i = 0; i < m; i++) {
      if (s >> i & 1) {
        b.push_back(a[i].x), b.push_back(a[i].y);
      }
    }
    d.clear();
    for (int i = 0; i < b.size(); i++) {
      for (int j = i + 1; j < b.size(); j++) {
        int x = Lca(b[i], b[j]);
        d[x] = {Size(x), 0};
        for (int k = b[i]; k != x; k >>= 1) {
          d[k] = {Size(k), 0};
        }
        for (int k = b[j]; k != x; k >>= 1) {
          d[k] = {Size(k), 0};
        }
      }
    }
    for (auto &i : d) {
      if (d.count(i.first << 1)) {
        i.second.s -= d[i.first << 1].s;
      }
      if (d.count(i.first << 1 | 1)) {
        i.second.s -= d[i.first << 1 | 1].s;
      }
    }
    for (auto i : d) {
      S(i.first, s);
      for (auto &j : d) {
        if (j.second.b) {
          ans = (ans + 1LL * i.second.s * j.second.s) % kMod;
        }
        j.second.b = 0;
      }
    }
  }
  cout << ans << '\n';
  return 0;
}

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const int kMaxN = 1e5 + 1;
struct A {
  int first, second;
  bool operator<(const A &a) const {
    return first < a.first || first == a.first && second < a.second;
  }
};
int n, m;
char s[kMaxN], t[kMaxN];
vector<A> f, g;

void CheckMin(int &x, int y) {
  x = min(x, y);
}

void Insert(int x, int y) {
  if (y <= 50) {
    if (!g.empty() && g.back().first == x) {
      CheckMin(g.back().second, y);
    } else {
      g.push_back({x, y});
    }
  }
}

void Unique() {
  f = g, g.clear(), sort(f.begin(), f.end());
  for (int i = 0, j = 0; i < f.size(); i = j) {
    for (; j < f.size() && f[i].first == f[j].first; j++) {
    }
    Insert(f[i].first, f[i].second);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> (s + 1) >> (t + 1);
  n = strlen(s + 1), m = strlen(t + 1);
  for (int i = 0; i <= m; i++) {
    Insert(i, i);
  }
  for (int o = 1; o <= n; o++) {
    f = g, g.clear();
    for (auto i : f) {
      Insert(i.first, i.second + 1);
      if (i.first < m) {
        Insert(i.first + 1, i.second + (t[i.first + 1] != s[o]));
      }
    }
    Unique();
    for (int i = 1; i < g.size(); i++) {
      g[i].second = min(g[i].second, g[i - 1].second + g[i].first - g[i - 1].first);
    }
    for (auto i = g.back(); i.first < m && i.second < 50; i = g.back()) {
      g.push_back({i.first + 1, i.second + 1});
    }
  }
  cout << (!g.empty() && g.back().first == m ? g.back().second : -1);
  return 0;
}

#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("empty.in");
ofstream cout("empty.out");

const int kMaxN = 5e5 + 1;
struct Trie {
  struct V {
    struct T {
      int x, y, p, t;
    } t;
    int d, c, b, e[26];
    vector<pair<int, int>> in, out;
  } v[kMaxN];
  int m, a[kMaxN];

  void Init() { m = 1, v[1] = v[0]; }

  void Insert(string &s) {
    int p = 1;
    for (int i = 0; i < s.size(); i++) {
      if (!v[p].e[s[i] - 'a']) {
        v[p].e[s[i] - 'a'] = ++m, v[m] = v[0];
      }
      p = v[p].e[s[i] - 'a'], v[p].d = i + 1, a[i] = p;
    }
  }
} trie1, trie2;
struct E {
  int x, y, w;
} e[kMaxN];
int o, n, m;
string s[kMaxN], t[kMaxN];

void Print1(int i, pair<int, int> j, pair<int, int> k) {
  cout << "YES\n";
  cout << trie1.v[k.first].t.x << ' ' << k.second << ' ';
  cout << trie1.v[k.first].t.y << ' ' << j.second << ' ';
  cout << trie1.v[i].d << ' ' << trie1.v[k.first].d << '\n';
}

void Print2(int i, pair<int, int> j, pair<int, int> k) {
  cout << "YES\n";
  cout << trie2.v[k.first].t.x << ' ' << k.second << ' ';
  cout << j.second << ' ' << trie2.v[k.first].t.y << ' ';
  cout << trie1.v[trie2.v[k.first].t.p].d << ' ' << trie1.v[j.first].d << '\n';
}

void Solve() {
  m = 0, trie1.Init(), trie2.Init();
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> s[i], t[i] = s[i], reverse(t[i].begin(), t[i].end());
    trie1.Insert(s[i]), trie2.Insert(t[i]);
    for (int j = 0; j + 1 < s[i].size(); j++) {
      trie1.v[trie1.a[j]].c++, trie2.v[trie2.a[s[i].size() - 2 - j]].c++;
      e[++m] = {trie1.a[j], trie2.a[s[i].size() - 2 - j], i};
    }
  }
  for (int i = 1; i <= m; i++) {
    if (trie1.v[e[i].x].c >= trie2.v[e[i].y].c) {
      trie1.v[e[i].x].out.push_back({e[i].y, e[i].w});
      trie2.v[e[i].y].in.push_back({e[i].x, e[i].w});
    } else {
      trie1.v[e[i].x].in.push_back({e[i].y, e[i].w});
      trie2.v[e[i].y].out.push_back({e[i].x, e[i].w});
    }
  }
  for (int i = 1; i <= trie1.m; i++) {
    for (auto j : trie1.v[i].out) {
      if (trie2.v[j.first].b < i) {
        trie2.v[j.first].b = i;
        for (auto k : trie2.v[j.first].out) {
          if (i != k.first) {
            if (trie1.v[k.first].t.t < i) {
              trie1.v[k.first].t = {j.second, k.second, j.first, i};
            } else {
              return Print1(i, j, k);
            }
          }
        }
        for (auto k : trie2.v[j.first].in) {
          if (i != k.first) {
            if (trie1.v[k.first].t.t < i) {
              trie1.v[k.first].t = {j.second, k.second, j.first, i};
            } else {
              return Print1(i, j, k);
            }
          }
        }
      }
    }
  }
  for (int i = 1; i <= trie2.m; i++) {
    for (auto j : trie2.v[i].out) {
      if (trie1.v[j.first].b < i) {
        trie1.v[j.first].b = i;
        for (auto k : trie1.v[j.first].out) {
          if (i != k.first) {
            if (trie2.v[k.first].t.t < i) {
              trie2.v[k.first].t = {j.second, k.second, j.first, i};
            } else {
              return Print2(i, j, k);
            }
          }
        }
        for (auto k : trie1.v[j.first].in) {
          if (i != k.first) {
            if (trie2.v[k.first].t.t < i) {
              trie2.v[k.first].t = {j.second, k.second, j.first, i};
            } else {
              return Print2(i, j, k);
            }
          }
        }
      }
    }
  }
  cout << "NO\n";
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    Solve();
  }
  return 0;
}

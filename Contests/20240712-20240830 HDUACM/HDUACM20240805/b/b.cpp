#include <fstream>
#include <vector>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 1e4 + 1;
struct V {
  bool b;
  int two, _two, three;
  vector<int> e;
} v[kMaxN];
int t, n, m, s, ans;

int S(int x) {
  int ans = v[x].e.size() > 1;
  v[x].b = 1;
  for (int i : v[x].e) {
    if (!v[i].b) {
      ans += S(i);
    }
  }
  return ans;
}

void T(int x) {
  v[x].b = 0;
  for (int i : v[x].e) {
    if (v[i].b) {
      T(i);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    s = 0, ans = 1;
    for (int i = 1; i <= n; i++) {
      v[i].b = v[i].two = v[i].three = 0, v[i].e.clear();
    }
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    for (int i = 1; i <= n; i++) {
      if (!v[i].b && S(i) > 1) {
        if (s) {
          ans = 0;
        } else {
          s = i;
        }
      }
    }
    if (!ans) {
      cout << "-1 \n";
      continue;
    } else if (!s) {
      for (int i = 1; i <= n; i++) {
        cout << i << ' ';
      }
      cout << '\n';
      continue;
    }
    ans = 0, T(s);
    for (int i = 1; i <= n; i++) {
      for (int j : v[i].e) {
        if (v[j].e.size() == 2) {
          v[i].two++;
        } else if (v[j].e.size() > 2) {
          v[i].three++;
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      if (!v[i].b) {
        bool o = 1;
        if (v[i].e.size() > 2) {
          for (int j : v[i].e) {
            v[j].three--;
          }
        }
        for (int j : v[i].e) {
          if (v[j].e.size() > 2) {
            if (v[j].three) {
              o = 0;
            }
            v[j]._two = v[j].two;
          } else if (v[j].e.size() == 2) {
            int x = i ^ v[j].e.front() ^ v[j].e.back();
            if (v[x].three) {
              o = 0;
            }
            v[x]._two = v[x].two;
          }
        }
        if (v[i].e.size() > 2) {
          for (int j : v[i].e) {
            v[j].three++;
          }
        }
        if (v[i].e.size() == 2) {
          for (int j : v[i].e) {
            if (v[j]._two) {
              v[j]._two--;
            }
          }
        }
        for (int j : v[i].e) {
          if (v[j].e.size() == 2) {
            int x = i ^ v[j].e.front() ^ v[j].e.back();
            if (v[x]._two) {
              v[x]._two--;
            }
          }
        }
        for (int j : v[i].e) {
          if (v[j].e.size() > 2) {
            if (v[j]._two) {
              o = v[j]._two = 0;
            }
          } else if (v[j].e.size() == 2) {
            int x = i ^ v[j].e.front() ^ v[j].e.back();
            if (v[x]._two) {
              o = v[x]._two = 0;
            }
          }
        }
        if (o) {
          ans = 1, cout << i << ' ';
        }
      }
    }
    if (ans) {
      cout << '\n';
    } else {
      cout << "-1 \n";
    }
  }
  return 0;
}

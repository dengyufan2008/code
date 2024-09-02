#include <fstream>
#include <queue>

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

const int kMaxN = 2e5 + 1;
struct V {
  int o, d, c, f, ans, dis[2];
  vector<int> e;
} v[kMaxN];
int t, n, m, k, d[kMaxN];

void CalcO(int o, int x) {
  if (!v[x].o) {
    v[x].o = o;
    for (int i : v[x].e) {
      CalcO(o, i);
    }
  }
}

bool IsTree() {
  int c = 0;
  for (int i = 1; i <= n; i++) {
    if (v[i].o == 1) {
      c += v[i].e.size(), c -= 2;
    }
  }
  return c < 0;
}

void CalcTreeD(int f, int x) {
  v[x].d = v[f].d + 1;
  for (int i : v[x].e) {
    if (i != f) {
      CalcTreeD(x, i);
    }
  }
}

void Dij(int x) {
  static priority_queue<pair<int, int>> q;
  for (int i = 1; i <= n; i++) {
    v[i].dis[0] = v[i].dis[1] = n;
  }
  v[x].dis[0] = 0;
  for (q.push({0, x << 1}); !q.empty();) {
    bool u = q.top().second & 1;
    x = q.top().second >> 1, q.pop();
    for (int i : v[x].e) {
      if (v[i].dis[u ^ 1] > v[x].dis[u] + 1) {
        v[i].dis[u ^ 1] = v[x].dis[u] + 1;
        q.push({-v[i].dis[u ^ 1], i << 1 | (u ^ 1)});
      }
    }
  }
}

void FindTree(int f, int x) {
  v[x].o = -2;
  for (int i : v[x].e) {
    if (i != f) {
      FindTree(x, i);
    }
  }
}

void CalcD() {
  for (int i = 1; i <= n; i++) {
    v[i].c = v[i].e.size();
    if (v[i].o == 1 && v[i].c == 1) {
      d[++k] = i;
    }
  }
  for (int l = 1; l <= k; l++) {
    int x = d[l];
    v[x].o = -1;
    for (int i : v[x].e) {
      if (v[i].c > 1) {
        v[x].f = i, v[i].c--;
        if (v[i].c == 1) {
          d[++k] = i;
        }
      }
    }
  }
  for (int i = k; i >= 1; i--) {
    int x = d[i];
    if (v[x].f) {
      v[x].d = v[v[x].f].d + 1;
    }
  }
}

void CalcF() {
  for (int i = k; i >= 1; i--) {
    int x = d[i];
    if (v[x].f && v[v[x].f].f) {
      v[x].f = v[v[x].f].f;
    }
  }
}

void CalcAns1() {
  int s = 1;
  for (; v[v[s].f].o == -1; s = v[s].f) {
  }
  Dij(v[s].f), FindTree(v[s].f, s), CalcF();
  for (int i = 2; i <= n; i++) {
    if (v[i].o == 1) {
      cout << (v[1].d > v[i].dis[v[1].d & 1 ^ 1] ? 'B' : 'D');
    } else if (v[i].o == -1) {
      int w = v[1].d - v[i].d;
      if (w + v[v[i].f].dis[w & 1] <= 0) {
        cout << 'A';
      } else if (w - v[v[i].f].dis[w & 1 ^ 1] > 0) {
        cout << 'B';
      } else {
        cout << 'D';
      }
    } else if (v[i].o == -2) {
      if (v[1].d <= v[i].d) {
        if (v[1].d + v[i].d & 1 ^ 1) {
          cout << 'A';
        } else if (v[1].d + v[v[1].f].dis[1] <= v[i].d) {
          cout << 'A';
        } else {
          cout << 'D';
        }
      } else {
        if (v[i].d + v[1].d & 1) {
          cout << 'B';
        } else if (v[i].d + v[v[i].f].dis[1] <= v[1].d) {
          cout << 'B';
        } else {
          cout << 'D';
        }
      }
    } else {
      cout << (v[i].e.empty() ? 'A' : 'D');
    }
  }
}

void CalcAns2() {
  Dij(1), CalcF();
  for (int i = 2; i <= n; i++) {
    if (v[i].o == 1) {
      cout << 'D';
    } else if (v[i].o == -1) {
      cout << (v[i].d >= v[v[i].f].dis[v[i].d & 1] ? 'A' : 'D');
    } else {
      cout << (v[i].e.empty() ? 'A' : 'D');
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    k = 0;
    for (int i = 1; i <= n; i++) {
      v[i].o = v[i].f = v[i].d = 0, v[i].e.clear();
    }
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    if (v[1].e.empty()) {
      cout << string(n - 1, 'B');
    } else {
      for (int i = 1; i <= n; i++) {
        CalcO(i, i);
      }
      if (IsTree()) {
        CalcTreeD(0, 1);
        for (int i = 2; i <= n; i++) {
          if (v[i].o == 1) {
            cout << (v[i].d & 1 ? 'A' : 'B');
          } else {
            cout << (v[i].e.empty() ? 'A' : 'D');
          }
        }
      } else {
        CalcD(), v[1].o == -1 ? CalcAns1() : CalcAns2();
      }
    }
    cout << '\n';
  }
  return 0;
}

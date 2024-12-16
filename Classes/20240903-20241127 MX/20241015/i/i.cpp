#include <fstream>

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 101;
struct V {
  int f;
  bool o;
} v[kMaxN * kMaxN / 2];
int n, r[kMaxN][kMaxN], p[kMaxN], q[kMaxN];
bool e[kMaxN][kMaxN];

int GetRoot(int x, bool &o) {
  if (v[x].f == x) {
    return x;
  }
  o ^= v[x].o, v[x].o ^= o;
  v[x].f = GetRoot(v[x].f, o);
  v[x].o ^= o;
  return v[x].f;
}

void Merge(int x, int y, bool o) {
  x = GetRoot(x, o), y = GetRoot(y, o);
  if (x != y) {
    v[x].f = y, v[x].o = o;
  } else if (o) {
    cout << "NO\n";
    exit(0);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      static int o = 0;
      cin >> e[i][j], r[i][j] = i < j ? v[o].f = ++o : 0;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      for (int k = j + 1; k <= n; k++) {
        int c = e[i][j] + e[i][k] + e[j][k];
        if (c == 1 || c == 2) {
          if (e[i][j] == e[i][k]) {
            Merge(r[i][j], r[i][k], 0);
          } else if (e[i][j] == e[j][k]) {
            Merge(r[i][j], r[j][k], 1);
          } else {
            Merge(r[i][k], r[j][k], 0);
          }
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      bool o = 0;
      GetRoot(r[i][j], o);
      p[o ? i : j]++, q[o ^ e[i][j] ^ 1 ? i : j]++;
    }
  }
  cout << "YES\n";
  for (int i = 1; i <= n; i++) {
    cout << ++p[i] << " \n"[i == n];
  }
  for (int i = 1; i <= n; i++) {
    cout << ++q[i] << " \n"[i == n];
  }
  return 0;
}

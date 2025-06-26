#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2e6 + 1, kMod = 998244353;
struct V {
  int u, c, e[27];
} v[kMaxN];
int n, m, k, r[kMaxN];
LL ans, f[kMaxN];

void Insert(int u, string s) {
  static int a[27];
  r[u] = ++m, v[m].u = u, v[m].c = 1;
  for (int i = 0; i < s.size(); i++) {
    int c = 1, p = r[u];
    a[1] = s[i] - 'a';
    for (int j = i + 1; j < s.size(); j++) {
      int x = 0;
      for (int o = 1; o <= c; o++) {
        if (a[o] == s[j] - 'a') {
          x = o;
          for (int oo = 1; oo < o; oo++) {
            swap(a[oo], a[o]);
          }
        }
      }
      if (!x) {
        a[++c] = s[j] - 'a';
        for (int o = 1; o < c; o++) {
          swap(a[o], a[c]);
        }
      }
      if (!v[p].e[x]) {
        v[p].e[x] = ++m, v[m].u = u, v[m].c = c;
      }
      p = v[p].e[x];
    }
  }
}

void Update(LL &x, LL y) { x = (x + y) % kMod; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    static string s;
    cin >> s, Insert(i, s);
  }
  ans = 1, f[1] = k;
  for (int i = 1; i <= m; i++) {
    Update(ans, f[i]);
    if (v[i].e[0]) {
      Update(f[v[i].e[0]], f[i] * (k - v[i].c));
    } else if (v[i].u < n) {
      Update(f[r[v[i].u + 1]], f[i] * (k - v[i].c));
    }
    for (int j = 1; j <= v[i].c; j++) {
      if (v[i].e[j]) {
        Update(f[v[i].e[j]], f[i]);
      } else if (v[i].u < n) {
        Update(f[r[v[i].u + 1]], f[i]);
      }
    }
  }
  cout << ans << '\n';
  return 0;
}

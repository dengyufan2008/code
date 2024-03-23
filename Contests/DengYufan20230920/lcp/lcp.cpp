#include <fstream>
#define LL long long

using namespace std;

ifstream cin("lcp.in");
ofstream cout("lcp.out");

const int kMaxN = 1e6 + 1, kMaxM = 3;
struct V {
  int d, c, s;
  pair<int, int> e[26];
} v[kMaxN * 3];
int n, m, k, w, o;
LL t, ans;
string s, a[kMaxN][kMaxM];

void S(int f, int x) {
  v[x].s = v[x].c;
  for (int i = 0; i < 26; i++) {
    if (v[x].e[i].first && v[x].e[i].second == o && v[x].e[i].first != f) {
      v[v[x].e[i].first].d = v[x].d + 1;
      S(x, v[x].e[i].first);
      v[x].s += v[v[x].e[i].first].s;
    }
  }
  t += (LL)v[x].s * v[x].c * (v[x].d / w);
  for (int i = 0; i < 26; i++) {
    if (v[x].e[i].first && v[x].e[i].second == o && v[x].e[i].first != f) {
      t += (LL)(v[x].s - v[v[x].e[i].first].s) * v[v[x].e[i].first].s * (v[x].d / w);
    }
  }
  v[x].c = 0;
}

void Insert(string s) {
  int p = 1;
  for (char c : s) {
    if (!v[p].e[c - 'a'].first || v[p].e[c - 'a'].second != o) {
      v[p].e[c - 'a'] = {++k, o};
    }
    p = v[p].e[c - 'a'].first;
  }
  v[p].c++;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  for (o = 1; o < (1 << m); o++) {
    k = 1, w = (o & 1) + (o >> 1 & 1) + (o >> 2 & 1);
    for (int i = 1, l; i <= n; i++) {
      l = kMaxN * 3, s = "";
      for (int j = 0; j < m; j++) {
        if (o >> j & 1) {
          l = min(l, (int)a[i][j].size());
        }
      }
      for (int k = 0; k < l; k++) {
        for (int j = 0; j < m; j++) {
          if (o >> j & 1) {
            s += a[i][j][k];
          }
        }
      }
      Insert(s);
    }
    t = 0, S(0, 1), ans += w & 1 ? t : -t;
  }
  cout << ans;
  return 0;
}

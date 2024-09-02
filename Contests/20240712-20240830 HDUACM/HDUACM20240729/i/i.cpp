#include <fstream>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 1e6 + 10, kMaxM = 715;
struct V {
  int e[10];
  bool b;
} v[kMaxM];
int o, n, m, ans, p[kMaxN][26], w[kMaxN];
bool f[kMaxM];
string s, t;

void Insert(string s) {
  static int k = 0;
  int i = 0;
  for (char c : s) {
    if (!v[i].e[c - '0']) {
      v[i].e[c - '0'] = ++k;
    }
    i = v[i].e[c - '0'];
  }
  v[i].b = 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 1; i <= 12; i++) {
    int w = i == 2 ? 29 : (i <= 7 ? 30 + i % 2 : 31 - i % 2);
    for (int j = 1; j <= w; j++) {
      s = "";
      s += char('0' + j % 10);
      s += char('0' + j / 10);
      s += char('0' + i % 10);
      s += char('0' + i / 10);
      Insert(s);
    }
  }
  cin >> o;
  while (o--) {
    cin >> n >> m >> s, s = '~' + s;
    fill(&p[m][0], &p[m][26], m);
    for (int i = m - 1; i >= 0; i--) {
      copy(&p[i + 1][0], &p[i + 1][26], &p[i][0]);
      if (s[i + 1] >= 'a' && s[i + 1] <= 'z') {
        p[i][s[i + 1] - 'a'] = i + 1;
      }
    }
    fill(&w[1], &w[m] + 1, 0);
    for (int i = 1; i <= n; i++) {
      int j = 0;
      cin >> t;
      for (char c : t) {
        j = p[j][c - 'a'];
      }
      j < m && (w[j + 1]++);
    }
    ans = 0, f[0] = 1, fill(&f[1], &f[kMaxM], 0);
    for (int i = m; i >= 1; i--) {
      if (s[i] >= '0' && s[i] <= '9') {
        for (int j = kMaxM - 1; j >= 0; j--) {
          f[v[j].e[s[i] - '0']] |= f[j];
        }
      }
      if (w[i]) {
        for (int j = 0; j < kMaxM; j++) {
          v[j].b && (f[j]) && (ans += w[i]);
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}

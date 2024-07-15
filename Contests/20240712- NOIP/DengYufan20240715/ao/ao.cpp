#include <fstream>
#include <unordered_map>
#define LL long long

using namespace std;

ifstream cin("ao.in");
ofstream cout("ao.out");

const int kMaxN = 2001;
int o, n, c, p, nt[kMaxN][2];
LL m, ans, s[kMaxN], t[kMaxN][2];
unordered_map<LL, LL> f[kMaxN];

void Update(int x, LL y, LL z) {
  if (f[x].count(y)) {
    f[x][y] = min(f[x][y], z);
  } else {
    f[x][y] = z;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o >> o;
  while (o--) {
    cin >> n >> c >> p >> m, p += c;
    for (int i = 1; i <= n; i++) {
      cin >> s[i], s[i] += s[i - 1], f[i].clear();
    }
    for (int i = 0; i <= n; i++) {
      nt[i][0] = nt[i][1] = i;
      for (int &j = nt[i][0]; j <= n && (s[j] - s[i]) % p <= c; j++) {
      }
      for (int &j = nt[i][1]; j <= n && (s[j] - s[i] + c) % p <= c; j++) {
      }
    }
    for (int i = 0; i < n; i++) {
      if (nt[i][0] < n) {
        t[i][0] = (s[nt[i][0]] - s[i]) % p - c;
        for (int j = nt[i][0]; nt[j][1] < n; j = nt[j][1]) {
          t[i][0] += (s[nt[j][1]] - s[j] + c) % p - c;
        }
      } else {
        t[i][0] = 0;
      }
      t[i][1] = 0;
      for (int j = i; nt[j][1] < n; j = nt[j][1]) {
        t[i][1] += (s[nt[j][1]] - s[j] + c) % p - c;
      }
    }
    Update(0, 0, 0);
    for (int i = 0; i < n; i++) {
      for (auto [o, w] : f[i]) {
        int j = nt[i][o % p > 0];
        if (j <= n) {
          LL r = o + s[j] - s[i];
          Update(j, r - r % p + c, w + r % p - c);
          Update(j, r - r % p + p, w);
        }
      }
    }
    ans = 1e18;
    for (int i = 0; i < n; i++) {
      for (auto [o, w] : f[i]) {
        LL v = t[i][o % p > 0];
        if (w + v <= m) {
          LL r = o + s[n] - s[i] - m + w;
          ans = min(ans, r + (r % p > c ? p - r % p : 0));
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}

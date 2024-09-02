#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("ao.in");
ofstream cout("ao.out");

const LL kMaxN = 2001, kMaxM = 1 << 13, kInf = 1e18;
int o, n, c, p, nt[kMaxN][2];
LL m, ans, s[kMaxN], t[kMaxN][2];

class Umap {
  short Hash(unsigned LL x) {
    return (x >> 2 ^ x << 4 ^ x >> 8 ^ x << 16 ^ x >> 32) & kMaxM - 1;
  }

 public:
  pair<LL, LL> v[kMaxM];
  vector<short> l;

  Umap() {
    l.clear();
    for (short i = 0; i < kMaxM; i++) {
      v[i] = {-1, kInf};
    }
  }

  void Clear() {
    l.clear();
    for (short i = 0; i < kMaxM; i++) {
      v[i] = {-1, kInf};
    }
  }

  LL &operator[](LL x) {
    short y = Hash(x);
    for (; v[y].first != x && v[y].first != -1; y = y + 1 & kMaxM - 1) {
    }
    if (v[y].first == -1) {
      v[y].first = x, l.push_back(y);
    }
    return v[y].second;
  }
} f[kMaxN];

void Update(LL &x, LL y) { x = min(x, y); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o >> o;
  while (o--) {
    cin >> n >> c >> p >> m, p += c;
    for (int i = 1; i <= n; i++) {
      cin >> s[i], s[i] += s[i - 1], f[i].Clear();
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
    Update(f[0][0], 0);
    for (int i = 0; i < n; i++) {
      for (int l : f[i].l) {
        LL o = f[i].v[l].first, w = f[i].v[l].second;
        int j = nt[i][o % p > 0];
        if (j <= n) {
          LL r = o + s[j] - s[i];
          Update(f[j][r - r % p + c], w + r % p - c);
          Update(f[j][r - r % p + p], w);
        }
      }
    }
    ans = 1e18;
    for (int i = 0; i < n; i++) {
      for (int l : f[i].l) {
        LL o = f[i].v[l].first, w = f[i].v[l].second;
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

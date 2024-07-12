#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("ellipse.in");
ofstream cout("ellipse.out");

const LL kMaxN = 1 << 22, kMod = 1e9 + 7, kInv2 = kMod + 1 >> 1;
LL o, n, a, b, c, d, e, f, xl, xr, yl, yr, ans, r[kMaxN], s[kMaxN], t[kMaxN];
vector<pair<LL, LL>> l[kMaxN];

LL Pow(LL x, LL y) {
  LL ans = 1;
  for (LL i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

bool F(LL x, LL y) {
  return a * (x - b) * (x - b) + c * (y - d) * (y - d) + e * (x - b) * (y - d) <= f;
}

bool Check(LL x, LL l, LL r, bool o) {  // 0:X 1:Y
  l -= o ? d : b, r -= o ? d : b, x -= o ? b : d;
  LL a0 = (o ? a : c) * x * x - f, a1 = e * x, a2 = o ? c : a;
  if (a1 * a1 - 4 * a0 * a2 < 0) {
    return 0;
  } else if (min(a2 * l * l + a1 * l + a0, a2 * r * r + a1 * r + a0) <= 0) {
    return 1;
  } else if (-a1 < l * a2 * 2 || -a1 > r * a2 * 2) {
    return 0;
  }
  return 1;
}

void Divide(LL x1, LL y1, LL c) {
  LL x2 = x1 + c - 1, y2 = y1 + c - 1;
  if (F(x1, y1) && F(x1, y2) && F(x2, y1) && F(x2, y2)) {
    l[c].push_back({x1, y1});
    return;
  } else if ((x1 > xl || x2 < xr || y1 > yl || y2 < yr) &&
             !Check(y1, x1, x2, 0) && !Check(y2, x1, x2, 0) &&
             !Check(x1, y1, y2, 1) && !Check(x2, y1, y2, 1)) {
    return;
  }
  LL x0 = x1 + x2 >> 1, y0 = y1 + y2 >> 1;
  Divide(x1, y1, c >> 1), Divide(x1, y0 + 1, c >> 1);
  Divide(x0 + 1, y1, c >> 1), Divide(x0 + 1, y0 + 1, c >> 1);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    cin >> a >> b >> c >> d >> e >> f;
    for (LL &i = xl = b; i >= 0 && Check(i, 0, kMaxN, 1); i--) {
    }
    for (LL &i = xr = b; i <= kMaxN && Check(i, 0, kMaxN, 1); i++) {
    }
    for (LL &i = yl = d; i >= 0 && Check(i, 0, kMaxN, 0); i--) {
    }
    for (LL &i = yr = d; i <= kMaxN && Check(i, 0, kMaxN, 0); i++) {
    }
    for (n = 1; n < max(xr, yr); n <<= 1) {
      l[n].clear(); 
    }
    Divide(0, 0, n);
    for (LL i = 0; i < n; i++) {
      s[i] = Pow(i, kMod - 2), r[i] = s[i] * s[i] % kMod, t[i] = 0;
    }
    for (LL i = 1; i < n; i <<= 1) {
      for (auto j : l[i]) {
        LL x = j.first, y = j.second;
        for (LL k = 0; k < i; k++) {
          t[(x ^ y) + k] = (t[(x ^ y) + k] + r[x + k] * s[y + k] % kMod) % kMod;
        }
      }
      for (LL j = 0; j < n; j += i + i) {
        for (LL k = j, x, y; k < j + i; k++) {
          x = r[k], y = r[k + i];
          r[k] = (x + y) % kMod, r[k + i] = (x - y + kMod) % kMod;
          x = s[k], y = s[k + i];
          s[k] = (x + y) % kMod, s[k + i] = (x - y + kMod) % kMod;
          x = t[k], y = t[k + i];
          t[k] = (x + y) % kMod, t[k + i] = (x - y + kMod) % kMod;
        }
      }
    }
    for (LL i = 1; i < n; i <<= 1) {
      for (LL j = 0; j < n; j += i + i) {
        for (LL k = j, x, y; k < j + i; k++) {
          x = t[k], y = t[k + i];
          t[k] = (x + y) % kMod * kInv2 % kMod;
          t[k + i] = (x - y + kMod) % kMod * kInv2 % kMod;
        }
      }
    }
    ans = 0;
    for (LL i = 0; i < n; i++) {
      ans = (ans + t[i] * Pow(i, 33) % kMod) % kMod;
    }
    cout << ans << '\n';
  }
  return 0;
}

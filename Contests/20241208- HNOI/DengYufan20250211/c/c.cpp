#include <iostream>
#include <unordered_map>
#include <vector>
#define LL long long
#define LLL __int128_t

using namespace std;

const int kMaxN = 502, kMaxM = 2e4 + 1, kMaxP = 121;
const LLL kInf = 2e36;
const int kBase = 715876003, kMod1 = 998244353, kMod2 = 1e9 + 7;
int n, m, k;
LL ans, pw1[kMaxM], pw2[kMaxM];
LLL a[kMaxN];
vector<pair<LL, int>> v[kMaxN];
unordered_map<LL, int> q;
vector<LLL> p;

template <typename T>
void Read(T &x) {
  x = 0;
  int c = getchar();
  while (c < 48 || c > 57) {
    c = getchar();
  }
  while (c > 47 && c < 58) {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  }
}

LLL Gcd(LLL x, LLL y) { return y ? Gcd(y, x % y) : x; }

LLL Pow(LLL x, int y) {
  LLL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      if (ans > kInf / x) {
        ans = kInf;
      } else {
        ans *= x;
      }
    }
    if (x > kInf / x) {
      x = kInf;
    } else {
      x *= x;
    }
  }
  return ans;
}

void CalcP() {
  static vector<LLL> o;
  for (int i = 1; i <= n; i++) {
    o.push_back(a[i]);
    while (!o.empty()) {
      LLL x = o.back();
      o.pop_back();
      for (LLL &i : p) {
        LLL g = Gcd(x, i);
        while (g > 1) {
          x /= g, o.push_back(i / g), i = g;
          g = Gcd(x, i);
        }
      }
      if (x > 1) {
        p.push_back(x);
      }
    }
  }
  for (LLL &i : p) {
    for (int j = kMaxP - 1; j >= 2; j--) {
      LLL l = 2, r = i;
      while (l <= r) {
        LLL mid = l + r >> 1;
        if (Pow(mid, j) <= i) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      if (Pow(r, j) == i) {
        i = r;
        break;
      }
    }
  }
}

void CalcV() {
  for (LLL i : p) {
    q[i] = ++m;
  }
  for (int i = 1; i <= n; i++) {
    LLL x = a[i];
    for (LLL j : p) {
      if (!(x % j)) {
        int c = 0;
        while (!(x % j)) {
          x /= j, c++;
        }
        c %= k;
        if (c) {
          v[i].push_back({q[j], c});
        }
      }
    }
  }
}

void CalcAns() {
  q.clear();
  for (int i = 1; i <= n; i++) {
    static int c[kMaxM];
    static LL h1[kMaxN], h2[kMaxN];
    static LL t1[kMaxN], t2[kMaxN];
    for (int j = 1; j <= m; j++) {
      c[j] = 0;
    }
    h1[i + 1] = h2[i + 1] = 0;
    for (int j = i; j >= 1; j--) {
      h1[j] = h1[j + 1], h2[j] = h2[j + 1];
      for (auto g : v[j]) {
        int o = g.first;
        h1[j] = (h1[j] - pw1[o] * c[o]) % kMod1;
        h2[j] = (h2[j] - pw2[o] * c[o]) % kMod2;
        c[o] = (c[o] + g.second) % k;
        h1[j] = (h1[j] + pw1[o] * c[o]) % kMod1;
        h2[j] = (h2[j] + pw2[o] * c[o]) % kMod2;
      }
      h1[j] = (h1[j] + kMod1) % kMod1, h2[j] = (h2[j] + kMod2) % kMod2;
    }
    for (int j = 1; j <= m; j++) {
      c[j] = 0;
    }
    t1[i - 1] = t2[i - 1] = 0;
    for (int j = i; j <= n; j++) {
      t1[j] = t1[j - 1], t2[j] = t2[j - 1];
      for (auto g : v[j]) {
        int o = g.first;
        if (c[o]) {
          t1[j] = (t1[j] - pw1[o] * (k - c[o])) % kMod1;
          t2[j] = (t2[j] - pw2[o] * (k - c[o])) % kMod2;
        }
        c[o] = (c[o] + g.second) % k;
        if (c[o]) {
          t1[j] = (t1[j] + pw1[o] * (k - c[o])) % kMod1;
          t2[j] = (t2[j] + pw2[o] * (k - c[o])) % kMod2;
        }
      }
      t1[j] = (t1[j] + kMod1) % kMod1, t2[j] = (t2[j] + kMod2) % kMod2;
    }
    for (int j = i; j <= n; j++) {
      if (q.count(t1[j] * kMod2 + t2[j])) {
        ans += q[t1[j] * kMod2 + t2[j]];
      }
    }
    for (int j = i; j >= 1; j--) {
      q[h1[j] * kMod2 + h2[j]]++;
    }
  }
}

int main() {
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  pw1[0] = pw2[0] = 1;
  for (int i = 1; i < kMaxM; i++) {
    pw1[i] = pw1[i - 1] * kBase % kMod1;
    pw2[i] = pw2[i - 1] * kBase % kMod2;
  }
  Read(n), Read(k);
  for (int i = 1; i <= n; i++) {
    Read(a[i]);
  }
  CalcP(), CalcV(), CalcAns();
  cout << ans << '\n';
  return 0;
}

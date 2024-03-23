#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const LL kMaxN = 1e5 + 1, kMod = 1e9 + 7, kInv2 = kMod + 1 >> 1;
struct V {
  LL l, r;
};
LL t, n, m, x, y, o[kMaxN];

LL Find(LL p, LL l, LL r, LL x) {
  if (l == r) {
    return p;
  }
  LL mid = l + r >> 1LL;
  return mid >= x ? Find(p << 1LL, l, mid, x) : Find(p << 1LL | 1LL, mid + 1LL, r, x);
}

LL Log(LL x) {
  LL w = 0LL;
  for (; x; x >>= 1LL) {
    w++;
  }
  return w;
}

V Calc(LL p) {
  LL w = Log(p), l = 1LL, r = n;
  for (LL i = w - 2LL; i >= 0LL; i--) {
    LL mid = l + r >> 1LL;
    if (p >> i & 1LL) {
      l = mid + 1LL;
    } else {
      r = mid;
    }
  }
  return {l, r};
}

LL Rev(LL t, LL p) {
  LL q = 0LL;
  for (LL i = 0LL; i < t; i++) {
    q |= (p >> i & 1LL) << t - i - 1LL;
  }
  return q;
}

LL Mul(LL s, LL p, LL q) {
  LL t = Log(m - 1LL), _q = Rev(t, q), ans = 0LL;
  for (LL i = 0LL; i < t; i++) {
    for (LL j = 0LL; j < i; j++) {
      if (p >> i & _q >> j & 1LL) {
        LL l = (p >> i << i) ^ 1LL << i, r = _q & ~(-1LL << j), w = o[i - j - 1LL];
        ans = (ans + (((s * 4LL + 1LL) % kMod + (l + r) * 4LL % kMod)) % kMod * w % kMod) % kMod;
        ans = (ans + (w - 1LL) * w % kMod * o[j + 2LL] % kMod) % kMod;
      }
    }
    if (p >> i & 1LL) {
      LL w = ((p >> i << i) ^ 1LL << i) | (_q & ~(-1LL << i));
      if (w <= p && Rev(t, w) <= q) {
        ans = (ans + (s * 4LL + 1LL) % kMod + w * 4LL % kMod) % kMod;
      }
    }
  }
  if (Rev(t, p) <= q) {
    ans = (ans + (s * 4LL + 1LL) % kMod + p * 4LL % kMod) % kMod;
  }
  return ans;
}

int main() {
  cin.tie(0LL), cout.tie(0LL);
  ios::sync_with_stdio(0LL);
  o[0LL] = 1LL;
  for (int i = 1LL; i < kMaxN; i++) {
    o[i] = o[i - 1LL] * 2LL % kMod;
  }
  cin >> t;
  while (t--) {
    cin >> n >> x >> y;
    for (m = 1LL; m <= n; m <<= 1LL) {
    }
    m >>= 1LL;
    LL p = Find(1LL, 1LL, n, x), q = Find(1LL, 1LL, n, y), ans = 0LL;
    if (n != m) {
      LL s = Find(1LL, 1LL, n, 1LL) >> 1LL;
      if (Log(p) == Log(s) + 1LL) {
        if (p & 1LL) {
          ans = (ans + p) % kMod;
        }
        if (Calc(p >>= 1LL).l < x) {
          p++;
        }
      }
      if (Log(q) == Log(s) + 1LL) {
        if (q & 1LL ^ 1LL) {
          ans = (ans + q) % kMod;
        }
        if (Calc(q >>= 1LL).r > y) {
          q--;
        }
      }
      if (p <= q) {
        ans = (ans + Mul(s, q - s, n - m - 1LL)) % kMod;
        if (p > s) {
          ans = (ans - Mul(s, p - s - 1LL, n - m - 1LL) + kMod) % kMod;
        }
      }
    }
    while (p && q && p <= q) {
      ans = (ans + ((p + q) % kMod) * ((q - p + 1LL) % kMod) % kMod * kInv2 % kMod) % kMod;
      if (Calc(p >>= 1LL).l < x) {
        p++;
      }
      if (Calc(q >>= 1LL).r > y) {
        q--;
      }
    }
    cout << ans << '\n';
  }
  return 0LL;
}

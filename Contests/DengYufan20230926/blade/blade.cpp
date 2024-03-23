#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
#define LL long long

namespace IO {
#define iL (1 << 20)
char ibuf[iL], *iS = ibuf + iL, *iT = ibuf + iL;
#define gc() ((iS == iT) ? (iT = (iS = ibuf) + fread(ibuf, 1, iL, stdin), iS == iT ? EOF : *iS++) : *iS++)
template <class T>
inline void read(T &x) {
  x = 0;
  LL f = 0;
  char ch = gc();
  for (; !isdigit(ch); f |= ch == '-', ch = gc()) {
  }
  for (; isdigit(ch); x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc()) {
  }
  x = (f == 1 ? ~x + 1 : x);
}
template <class T, class... Args>
inline void read(T &x, Args &...args) { read(x), read(args...); }
template <class T>
inline void readch(T &x) {
  char ch = gc();
  for (; !isalpha(ch); ch = gc()) {
  }
  x = ch;
}
char Out[iL], *iter = Out;
#define flush() fwrite(Out, 1, iter - Out, stdout), iter = Out
template <class T>
inline void write(T x, char ch = '\n') {
  T l, c[35];
  if (x < 0) *iter++ = '-', x = ~x + 1;
  for (l = 0; !l || x; c[l] = x % 10, l++, x /= 10) {
  }
  for (; l; --l, *iter++ = c[l] + '0') {
  }
  *iter++ = ch;
  flush();
}
template <class T, class... Args>
inline void write(T x, Args... args) { write(x, ' '), write(args...); }
}  // namespace IO

using namespace std;
using namespace IO;

const LL kMaxN = 2e5 + 1, kMod = 1e9 + 7;
struct V {
  LL f, s, p[2], d[2];
  vector<LL> g, w;
  vector<pair<LL, LL>> e;
} v[kMaxN];
LL t, n, m, k, q;
map<pair<LL, LL>, LL> s;

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

LL GetRoot(LL x) {
  return v[x].f == x ? x : v[x].f = GetRoot(v[x].f);
}

void CalcP(LL f, LL x, bool b) {
  if (!v[GetRoot(x)].p[b] || v[v[GetRoot(x)].p[b]].d[!b] < v[x].d[!b]) {
    v[GetRoot(x)].p[b] = x;
  }
  for (auto i : v[x].e) {
    if (i.first != f) {
      v[i.first].d[!b] = v[x].d[!b] + i.second;
      CalcP(x, i.first, b);
    }
  }
}

void CalcD(LL f, LL x) {
  v[GetRoot(x)].g.push_back(max(v[x].d[0], v[x].d[1]));
  for (auto i : v[x].e) {
    if (i.first != f) {
      v[i.first].d[1] = v[x].d[1] + i.second;
      CalcD(x, i.first);
    }
  }
}

LL Find(LL x, LL w, LL r) {
  LL l = 0;
  while (l <= r) {
    LL mid = l + r >> 1;
    if (v[x].g[mid] <= w) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return r;
}

int main() {
  freopen("blade.in", "r", stdin);
  freopen("blade.out", "w", stdout);
  read(t), read(t);
  while (t--) {
    s.clear(), fill(&v[1], &v[n] + 1, v[0]);
    read(n, m, q), k = sqrt(n);
    for (LL i = 1; i <= n; i++) {
      v[i].f = i, v[i].s = 1;
    }
    for (LL i = 1, x, y, z; i <= m; i++) {
      read(x, y, z);
      v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
      x = GetRoot(x), y = GetRoot(y);
      v[max(x, y)].f = min(x, y), v[min(x, y)].s += v[max(x, y)].s;
    }
    for (LL i = 1; i <= n; i++) {
      if (GetRoot(i) == i) {
        CalcP(0, i, 0), CalcP(0, v[i].p[0], 1);
        v[v[i].p[1]].d[1] = 0, CalcD(0, v[i].p[1]);
        sort(v[i].g.begin(), v[i].g.end()), v[i].w = v[i].g, v[i].w[0] %= kMod;
        for (LL j = 1; j < v[i].w.size(); j++) {
          v[i].w[j] = (v[i].w[j] % kMod + v[i].w[j - 1]) % kMod;
        }
      }
    }
    for (LL i = 1, x, y; i <= q; i++) {
      read(x, y), x = GetRoot(x), y = GetRoot(y);
      if (x == y) {
        cout << -1 << '\n';
      } else {
        auto p = s.find({min(x, y), max(x, y)});
        if (p != s.end()) {
          cout << p->second << '\n';
          continue;
        }
        if (v[x].s > v[y].s) {
          swap(x, y);
        }
        LL k = v[y].g.size() - 1, ans = 0, l = max(v[x].g.back(), v[y].g.back());
        for (LL j : v[x].g) {
          k = Find(y, l - j - 1, k);
          ans = (ans + l % kMod * (k + 1) % kMod +
                 v[y].w.back() - (k >= 0 ? v[y].w[k] : 0) +
                 (j + 1) % kMod * (v[y].g.size() - k - 1) % kMod + kMod) %
                kMod;
        }
        ans = ans * Pow(v[x].s * v[y].s % kMod, kMod - 2) % kMod;
        cout << ans << '\n';
        if (v[x].s > k && v[y].s > k) {
          s[{min(x, y), max(x, y)}] = ans;
        }
      }
    }
  }
  return 0;
}

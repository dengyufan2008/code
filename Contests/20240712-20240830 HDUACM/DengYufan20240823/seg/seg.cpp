#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("seg.in");
ofstream cout("seg.out");

const LL kMaxN = 2e5 + 1, kMod = 998244353, kInf = 5e13;
struct V {
  LL l, mid, r, w;
} x;
int n;
LL m, l, r, ans, a[kMaxN];
vector<V> v;

bool C(LL w) {
  LL f = 0, x = m;
  for (int i = 1; i <= n; i++) {
    f = max(f, 0LL) + a[i];
    if (f > w) {
      x -= f - w, f = w;
      if (x < 0) {
        return 0;
      }
    }
  }
  return 1;
}

LL Calc1() {
  LL l = -kInf, r = kInf;
  while (l <= r) {
    LL mid = (l + r) / 2;
    if (C(mid)) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return l;
}

LL Calc2() {
  LL f = 0, x = -kInf;
  for (int i = 1; i <= n; i++) {
    f = max(f, 0LL) + a[i], x = max(x, f);
  }
  return x;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  cin >> m;
  l = Calc1(), r = Calc2(), m = (m + 1) % kMod;
  ans = (l % kMod * m - r + kMod) % kMod;
  for (int i = 1; i <= n; i++) {
    a[i] += a[i - 1];
  }
  v.push_back({l, r, r, r}), x = v.back();
  for (int i = 1; i <= n; i++) {
    for (; !v.empty() && (x = v.back()).w <= a[i]; v.pop_back()) {
      LL w1 = a[i] - x.w, w2 = x.mid - x.l, len = x.r - x.l;
      w1 %= kMod, w2 %= kMod, len %= kMod;
      ans = (ans + w1 * len + w2 * (w2 + 1) / 2) % kMod;
    }
    if (!v.empty() && x.w - x.mid + x.l <= a[i]) {
      LL w = (a[i] - x.w + x.mid - x.l) % kMod;
      x.l = v.back().l = a[i] - x.w + x.mid;
      ans = (ans + w * (w + 1) / 2) % kMod;
    }
    if (v.empty()) {
      v.push_back({l, l, r, a[i]}), x = v.back();
    } else if (l < x.l) {
      v.push_back({l, l, x.l, a[i]}), x = v.back();
    }
    for (; !v.empty() && (x = v.back()).w - x.r >= a[i]; v.pop_back()) {
    }
    if (!v.empty() && x.w - x.mid >= a[i]) {
      x.l = v.back().l = l, x.mid = v.back().mid = x.w - a[i];
    } else if (v.empty()) {
      v.push_back({l, r, r, a[i] + r}), x = v.back();
    }
  }
  cout << ans << '\n';
  return 0;
}

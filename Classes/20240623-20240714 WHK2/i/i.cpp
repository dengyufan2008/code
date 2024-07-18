#include <fstream>
#define LL long long

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 6e5 + 1, kMod = 1e9 + 7;
int n, m, sa, sb, sq, ta, tb, tq, mu[kMaxN], prime[kMaxN];
LL ans, pw[kMaxN], fact[kMaxN], _fact[kMaxN];
bool b[kMaxN];
string s, t;

LL Mul(LL a, LL b) {
	LL c = a * b - (LL)((double)a * b / kMod + 0.1) * kMod;
	return c < 0 ? c + kMod : c;
}

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = Mul(ans, x);
    }
    x = Mul(x, x);
  }
  return ans;
}

LL C(int x, int y) {
  if (y < 0 || y > x) {
    return 0;
  }
  return Mul(fact[x], Mul(_fact[y], _fact[x - y]));
}

int Gcd(int x, int y) {
  return y ? Gcd(y, x % y) : x;
}

void Init() {
  for (int i = 0; i < s.size(); i++) {
    sa += s[i] == 'A', sb += s[i] == 'B';
  }
  for (int i = 0; i < t.size(); i++) {
    ta += t[i] == 'A', tb += t[i] == 'B';
  }
  sq = s.size() - sa - sb, tq = t.size() - ta - tb;
  pw[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    pw[i] = pw[i - 1] << 1, pw[i] >= kMod && (pw[i] -= kMod);
  }
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = Mul(fact[i - 1], i);
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = Mul(_fact[i], i);
  }
  b[1] = mu[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    if (!b[i]) {
      prime[++m] = i, mu[i] = -1;
    }
    for (int j = 1; j <= m && prime[j] * i < kMaxN; j++) {
      b[i * prime[j]] = 1;
      if (i % prime[j]) {
        mu[i * prime[j]] = -mu[i];
      } else {
        mu[i * prime[j]] = 0;
        break;
      }
    }
  }
}

void Calc1() {  // S = T
  if (s.size() != t.size()) {
    return;
  }
  for (int i = 0; i < s.size(); i++) {
    if (abs(s[i] - t[i]) == 1) {
      return;
    }
  }
  LL w = (pw[n + 1] - 2) * (pw[n + 1] - 2) % kMod;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '?' && t[i] == '?') {
      w <<= 1, w >= kMod && (w -= kMod);
    }
  }
  ans = (ans + w) % kMod;
}

void Calc2() {  // (a1, b1) = (a2, b2)
  if (s.size() != t.size()) {
    return;
  }
  int c = 0;
  LL w = 0, d = 0, f[kMaxN] = {};
  for (int i = 1; i <= n; i++) {
    for (int j = i, k = 1; j <= n; j += i, k++) {
      f[j] = (f[j] + pw[i] * mu[k]) % kMod;
    }
  }
  for (int i = 1; i <= n; i++) {
    w = (w + f[i] * (n / i) % kMod * (n / i)) % kMod;
  }
  for (int i = max(sa, ta); i + max(sb, tb) <= s.size(); i++) {
    d = (d + C(sq, i - sa) * C(tq, i - ta)) % kMod;
  }
  for (int i = 0; i < s.size(); i++) {
    if (abs(s[i] - t[i]) == 1) {
      ans = (ans + w * d) % kMod;
      return;
    } else if (s[i] == '?' && t[i] == '?') {
      c++;
    }
  }
  ans = (ans + w * (d - pw[c] + kMod)) % kMod;
}

void Calc3() {  // |A| : |B| = b2 - b1 : a1 - a2
  int l = sa + tb - (int)t.size(), r = (int)s.size() - sb - ta;
  for (int i = l; i <= r; i++) {
    int p = i, q = i + (int)t.size() - (int)s.size();
    p < 0 ? p = -p, q = -q : 0;
    if (p > 0 && q > 0) {
      LL w = pw[1LL * n * Gcd(p, q) / max(p, q) + 1] - 2;
      ans = (ans + w * C(sq + tq, tq + i - sa + ta)) % kMod;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s >> t >> n;
  Init(), Calc1(), Calc2(), Calc3();
  cout << ans << '\n';
  return 0;
}

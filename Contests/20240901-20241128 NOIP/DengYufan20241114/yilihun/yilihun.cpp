#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("yilihun.in");
ofstream cout("yilihun.out");

const int kMaxN = 20, kMod = 998244353;
int n, m;
LL d[1 << kMaxN];  // d[s]: 输入的序列中值为 s 的超集的有多少个
LL p[1 << kMaxN];  // p[s]: 从 s 转移到非 s 的数量的倒数
LL f[1 << kMaxN];  // f[s]: 转移到 s 的概率
LL t[1 << kMaxN];
LL ans[kMaxN];

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

void Init() {
  char c;
  cin >> m >> n;
  for (int i = 1, s = 0; i <= m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> c, c == '1' && (s |= 1 << j);
    }
    p[s]++, p[s ^ (1 << n) - 1]++;
    d[s]++, s = 0;
  }
  for (int i = 0; i < n; i++) {
    for (int s = 1 << i; s < 1 << n; s = s + 1 | 1 << i) {
      p[s ^ 1 << i] += p[s], d[s ^ 1 << i] += d[s];
    }
  }
  p[0] = 0;
  for (int s = 1; s < 1 << n; s++) {
    p[s] = Pow(m - p[s]);
  }
}

void Dp() {
  f[(1 << n) - 1] = 1;
  for (int i = n - 1; i >= 0; i--) {  // popcount>i -> popcount=i
    for (int s = 0; s < 1 << n; s++) {
      if (__builtin_popcount(s) > i) {
        t[s] = f[s] * p[s] % kMod;
      }
    }
    for (int j = 0; j < n; j++) {
      for (int s = 1 << j; s < 1 << n; s = s + 1 | 1 << j) {
        (t[s ^ 1 << j] += t[s]) >= kMod && (t[s ^ 1 << j] -= kMod);
      }
    }
    for (int s = 0; s < 1 << n; s++) {
      t[s] = t[s] * d[s] % kMod;
    }
    for (int j = 0; j < n; j++) {
      for (int s = 1 << j; s < 1 << n; s = s + 1 | 1 << j) {
        (t[s ^ 1 << j] -= t[s]) < 0 && (t[s ^ 1 << j] += kMod);
      }
    }
    for (int s = 0; s < 1 << n; s++) {
      if (__builtin_popcount(s) == i) {
        f[s] = t[s];
      }
      t[s] = 0;
    }
  }
}

void CalcAns() {
  for (int s = 0; s < 1 << n; s++) {
    if (p[s]) {
      continue;
    }
    for (int i = 0; i < n; i++) {
      if (s >> i & 1) {
        ans[i] = (ans[i] + f[s]) % kMod;
      }
    }
  }
  LL h = 1;
  for (int i = 2; i <= m; i++) {
    h = h * i % kMod;
  }
  for (int i = 0; i < n; i++) {
    ans[i] = ans[i] * h % kMod;
    cout << ans[i] << '\n';
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Dp(), CalcAns();
  return 0;
}

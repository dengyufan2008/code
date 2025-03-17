#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN2 = 282842713, kMaxN3 = 430887, kMaxN4 = 16818;
LL l, r;
bool b[kMaxN3];  // 是否含有平方因子
bool c[kMaxN4];  // 是否含有立方因子

void Init() {
  for (int i = 2; i * i < kMaxN3; i++) {
    int x = i * i;
    for (int j = x; j < kMaxN3; j += x) {
      b[j] = 1;
    }
  }
  for (int i = 2; i * i * i < kMaxN4; i++) {
    int x = i * i * i;
    for (int j = x; j < kMaxN4; j += x) {
      c[j] = 1;
    }
  }
}

LL Sqrt(LL x) {
  LL l = 0, r = kMaxN2 - 1;
  while (l <= r) {
    LL mid = l + r >> 1;
    if (mid * mid <= x) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return r;
}

LL Cubt(LL x) {
  LL l = 0, r = kMaxN3 - 1;
  while (l <= r) {
    LL mid = l + r >> 1;
    if (mid * mid * mid <= x) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return r;
}

// 计算能被表示成 a*b^2 的数的个数
namespace Calc2 {
LL Solve(LL n) {
  LL ans = 0;
  for (int i = 1; i < kMaxN3; i++) {
    if (!b[i]) {
      ans += max(Sqrt(n / i) - i, 0LL);
    }
  }
  return ans;
}
}  // namespace Calc2

// 计算能被表示成 a*b^3 但不能被表示成 a*b^2 的数的个数
namespace Calc3 {
int mu[kMaxN4];
vector<int> d[kMaxN4];  // 非平方因子
vector<int> s[kMaxN4];  // s[i][j]: <= ij 的 i 的倍数里有多少个数没有平方因子

int Gcd(int x, int y) { return y ? Gcd(y, x % y) : x; }

void Init() {
  static bool o[kMaxN4];
  static vector<int> prime;
  mu[1] = 1;
  for (int i = 2; i < kMaxN4; i++) {
    if (!o[i]) {
      prime.push_back(i), mu[i] = -1;
    }
    for (int j : prime) {
      if (i * j >= kMaxN4) {
        break;
      }
      o[i * j] = 1;
      if (!(i % j)) {
        break;
      } else {
        mu[i * j] = -mu[i];
      }
    }
  }
  for (int i = 1; i < kMaxN4; i++) {
    if (!b[i]) {
      for (int j = i; j < kMaxN4; j += i) {
        d[j].push_back(i);
      }
      s[i].push_back(0);
      for (int j = i; j < kMaxN3; j += i) {
        int x = s[i].back() + !b[j];
        s[i].push_back(x);
      }
    }
  }
}

LL Solve(LL n) {
  LL ans = 0;
  for (int i = 1; i < kMaxN4; i++) {
    if (c[i]) {
      continue;
    }
    for (int j = Cubt(i); j >= 1; j--) {
      int g = Gcd(i, j * j), _i = i / g;
      if (b[_i]) {
        continue;
      }
      LL mn = i * g / (j * j);
      LL mx = Cubt(n / i) * g / (j * j);
      if (mn < mx) {
        for (int k : d[_i]) {
          ans += mu[k] * (s[k][mx / k] - s[k][mn / k]);
        }
      }
    }
  }
  return ans;
}
}  // namespace Calc3

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> l >> r;
  Init(), Calc3::Init();
  LL ans1 = Calc2::Solve(r) - Calc2::Solve(l - 1);
  LL ans2 = Calc3::Solve(r) - Calc3::Solve(l - 1);
  cout << ans1 + ans2 << '\n';
  return 0;
}

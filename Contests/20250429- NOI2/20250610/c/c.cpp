#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 401, kMod = 998244353;
int a, b, c, x, y, z;
LL ans, f[kMaxN][kMaxN];
LL fact[kMaxN], _fact[kMaxN];

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  x %= kMod;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

LL C(int x, int y) {
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

void Update(LL &x, LL y) { x = (x + y) % kMod; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }

  cin >> a >> b >> c >> x >> y >> z;
  if (x % a || y % b || z % c) {
    cout << 0 << '\n';
    return 0;
  }

  x /= a, y /= b, z /= c;

  // 容斥求存在平整的切面的情况

  Update(ans, Pow(Pow(b, z) * c + Pow(c, y) * b - b * c, x) * a);
  Update(ans, Pow(Pow(a, z) * c + Pow(c, x) * a - a * c, y) * b);
  Update(ans, Pow(Pow(a, y) * b + Pow(b, x) * a - a * b, z) * c);

  Update(ans, -Pow(a, y * z) * b * c);
  Update(ans, -Pow(b, x * z) * a * c);
  Update(ans, -Pow(c, x * y) * a * b);

  Update(ans, a * b * c);

  if (a == 1 || b == 1 || c == 1) {  // 小卡常, 省去 8 倍常数
    cout << (ans + kMod) % kMod << '\n';
    return 0;
  }

  // 任意维度都不存在平整切面, 容斥求恰好有完整的 i 行和完整的 j 列存在平整切面

  for (int i = 1; i < x; i++) {
    for (int j = 1; j < y; j++) {
      f[i][j] = C(x, i) * C(y, j) % kMod * (Pow(c, (x - i) * (y - j)) - 1) % kMod;
    }
  }

  for (int i = 1; i < x; i++) {
    for (int j = y - 1; j >= 1; j--) {
      for (int k = y - 1; k > j; k--) {
        Update(f[i][j], -f[i][k] * C(k, j));
      }
    }
  }
  for (int j = 1; j < y; j++) {
    for (int i = x - 1; i >= 1; i--) {
      for (int k = x - 1; k > i; k--) {
        Update(f[i][j], -f[k][j] * C(k, i));
      }
    }
  }

  // 将行和列滑动, 使得确实不存在平整切面

  for (int i = 1; i < x; i++) {
    for (int j = 1; j < y; j++) {
      LL w = 0;

      Update(w, Pow(Pow(a, j) + Pow(b, i) - 1, z));
      Update(w, -(Pow(a, j * z) + Pow(b, i * z)));
      Update(w, 1);

      Update(ans, f[i][j] * w % kMod * a * b * c);
    }
  }

  cout << (ans + kMod) % kMod << '\n';
  return 0;
}

#include <fstream>
#define LL long long

using namespace std;

ifstream cin("biophy.in");
ofstream cout("biophy.out");

const int kMaxN = 5001, kMod = 1e9 + 7;
int n, a[kMaxN], h[kMaxN * 2][kMaxN];
LL s[kMaxN], t[kMaxN], d[kMaxN * 2];

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

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i < n; i++) {
    cin >> a[i];
  }
  s[0] = 1;
  for (int i = 1; i < n; i++) {
    s[i] = s[i - 1] * a[i] % kMod;
  }
  t[n - 1] = Pow(s[n - 1]);
  for (int i = n - 1; i >= 1; i--) {
    t[i - 1] = t[i] * a[i] % kMod;
  }
  for (int i = 2; i < n * 2; i++) {
    for (int j = i - n + 1; j <= (i - 1) / 2; j++) {
      d[i] = (d[i] + s[j] * s[i - j]) % kMod;
    }
  }
  for (int i = 1; i <= n * 2 - 2; i++) {
    for (int j = 1; j * 2 < i; j++) {
      h[i][j] = (h[i][j - 1] + s[j] * s[i - j]) % kMod;
    }
  }
  for (int i = 1; i <= n * 2 - 2; i++) {
    LL ans = 0;
    if (i & 1 ^ 1) {
      int _i = i / 2 - 1;
      for (int j = 1; j <= n - _i; j++) {
        ans = (ans + s[j + _i] * s[j + _i] % kMod * (a[j] - 1) % kMod * t[j]) % kMod;
      }
    }
    ans = ans * (kMod + 1 >> 1) % kMod;
    for (int j = i; j < n; j++) {
      ans = (ans + s[j]) % kMod;
    }
    if (i <= n) {
      for (int j = i; j < n * 2 - i; j += 2) {
        ans = (ans + 1LL * (h[j][(j - 1) / 2] - h[j][(j - i) / 2] + kMod) * (a[(j - i + 2) / 2] - 1) % kMod * t[(j - i + 2) / 2]) % kMod;
      }
      for (int j = n * 2 - i; j < n * 2; j += 2) {
        ans = (ans + d[j] * (a[(j - i + 2) / 2] - 1) % kMod * t[(j - i + 2) / 2]) % kMod;
      }
    } else {
      for (int j = i; j < n * 2; j += 2) {
        ans = (ans + d[j] * (a[(j - i + 2) / 2] - 1) % kMod * t[(j - i + 2) / 2]) % kMod;
      }
    }
    cout << ans << " \n"[i == n * 2 - 2];
  }
  return 0;
}

#include <fstream>
#define LL long long

using namespace std;

ifstream cin("ainsoph.in");
ofstream cout("ainsoph.out");

const int kMaxN = 1e7 + 1, kMod = 1e9 + 9;
int n, m;
LL a[kMaxN], b[kMaxN], s[kMaxN], t[kMaxN];

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
  int u, w, x, y, z;
  cin >> n >> m >> u;
  if (u) {
    cin >> w >> x >> y >> z, a[1] = z;
    for (int i = 2; i <= n; i++) {
      a[i] = ((a[i - 1] * w + x) ^ y) % kMod;
    }
  } else {
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
  }
}

void Calc() {
  LL ans = 0;
  s[0] = 1;
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] * (a[i] + 1) % kMod;
  }
  t[n] = Pow(s[n]);
  for (int i = n; i >= 1; i--) {
    t[i - 1] = t[i] * (a[i] + 1) % kMod;
  }
  for (int i = 1; i <= n; i++) {
    b[i] = (b[i - 1] + a[i] * a[i] % kMod * t[i] % kMod * s[i - 1]) % kMod;
  }
  for (int i = 1; i <= n; i++) {
    int j = min(i + m - 1, n);
    ans = (ans + (a[i] + b[j] - b[i] + kMod) * a[i] % kMod * s[j] % kMod * t[i]) % kMod;
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Calc();
  return 0;
}

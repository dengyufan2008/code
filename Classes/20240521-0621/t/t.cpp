#include <fstream>
#define LL long long

using namespace std;

ifstream cin("t.in");
ofstream cout("t.out");

const int kMaxN = 2e5 + 1, kMod = 998244353;
int n, k, a[kMaxN];

void Init() {
  int s = 0;
  char c;
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> c;
    a[i] = c == 'L' ? -1 : 1;
    s += a[i];
  }
  if (s < 0) {
    for (int i = 1; i <= n; i++) {
      a[i] = -a[i];
    }
    for (int i = 1, j = n; i < j; i++, j--) {
      swap(a[i], a[j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    a[i] += a[i - 1];
  }
}

LL CalcL() {
  int mx = 0, l = 0;
  for (int i = 1; i <= n; i++) {
    mx = max(mx, a[i]), l += a[i] < a[i - 1];
  }
  if (mx == 0) {
    return 0;
  }
  LL ans = (k - 1LL) * l;
  for (int i = 1, s = 0; i <= n; i++) {
    if (s || a[i] > 0) {
      s = 1, ans += a[i] < a[i - 1];
    }
  }
  return ans;
}

LL CalcR() {
  int c[kMaxN << 1] = {};
  LL ans = 0;
  for (int i = 1; i <= n; i++) {
    c[a[i] + kMaxN] += a[i] > a[i - 1];
  }
  for (int i = 1; i < kMaxN << 1; i++) {
    c[i] += c[i - 1];
  }
  for (int i = 1; i <= k; i++) {
    int s = min(1LL * i * a[n], 1LL * n);
    ans += c[n + kMaxN] - c[s + kMaxN];
  }
  return ans << 1;
}

LL Calc() {
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += a[i] >= (a[i] > a[i - 1]);
  }
  return 1LL * ans * k;
}

int main() {
  cin.tie(0), cout.tie(0);
  Init();
  if (a[n]) {
    cout << (CalcL() + CalcR()) % kMod << '\n';
  } else {
    cout << Calc() % kMod << '\n';
  }
  return 0;
}

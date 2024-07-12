#include <fstream>
#define LL long long

using namespace std;

ifstream cin("sleep.in");
ofstream cout("sleep.out");

const int kMaxN = 3e5 + 1;
int n, m, s[2][2], a[kMaxN];
LL c, ans;

int R(int x) {
  if (x < 1) {
    x += n;
  } else if (x > n) {
    x -= n;
  }
  return x;
}

int M(int x) {
  if (n & 1) {
    return (s[0][a[x] ^ 1] + s[1][a[x] ^ 1]) * 3;
  } else {
    return s[x & 1][a[x] ^ 1] * 4 + s[x & 1 ^ 1][a[x] ^ 1] * 2 - (a[R(x + n / 2)] == (a[x] ^ 1)) * 2;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  fill(&a[1], &a[n] + 1, -1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    ans += M(i);
    s[i & 1][a[i]]++;
  }
  if (n % 3 == 0) {
    for (int i = 1; i <= n / 3; i++) {
      c += (a[i] ^ 1) == a[i + n / 3] || (a[i] ^ 1) == a[i + n / 3 * 2] || (a[i + n / 3] ^ 1) == a[i + n / 3 * 2];
    }
  }
  cout << 1LL * n * (n - 1 >> 1) - !(n % 3) * n / 3 * 2 - (ans / 2 - c * 2) << '\n';
  for (int i = 1, x; i <= m; i++) {
    cin >> x;
    if (n % 3 == 0) {
      c -= (a[x] ^ 1) == a[R(x + n / 3)] || (a[x] ^ 1) == a[R(x + n / 3 * 2)] || (a[R(x + n / 3)] ^ 1) == a[R(x + n / 3 * 2)];
    }
    s[x & 1][a[x]]--;
    ans -= M(x);
    a[x] ^= 1;
    ans += M(x);
    s[x & 1][a[x]]++;
    if (n % 3 == 0) {
      c += (a[x] ^ 1) == a[R(x + n / 3)] || (a[x] ^ 1) == a[R(x + n / 3 * 2)] || (a[R(x + n / 3)] ^ 1) == a[R(x + n / 3 * 2)];
    }
    cout << 1LL * n * (n - 1 >> 1) - !(n % 3) * n / 3 * 2 - (ans / 2 - c * 2) << '\n';
  }
  return 0;
}

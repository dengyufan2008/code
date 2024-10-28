#include <fstream>
#define LL long long

using namespace std;

ifstream cin("wind.in");
ofstream cout("wind.out");

const LL kMaxN = 1e5 + 2, kInf = 1e18;
struct A {
  LL x, y;
} a[kMaxN], s[kMaxN];
int t, n;
LL m, x, y, ans;

void Solve(LL &l, LL &r, LL k, LL b) {
  if (k > 0) {
    if (b >= 0) {
      r = min(r, b / k);
    } else {
      r = min(r, (b - k + 1) / k);
    }
  } else if (k < 0) {
    if (b >= 0) {
      l = max(l, (-b) / (-k));
    } else {
      l = max(l, (-b - k - 1) / (-k));
    }
  } else if (b < 0) {
    l = kInf, r = -kInf;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> x >> y;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].x >> a[i].y;
    }
    if (!x && !y) {
      cout << 0 << '\n';
      continue;
    }
    ans = kInf, s[n + 1] = {0, 0};
    for (int i = n; i >= 1; i--) {
      s[i].x = s[i + 1].x + a[i].x;
      s[i].y = s[i + 1].y + a[i].y;
    }
    for (int i = 1; i <= n; i++) {
      LL l = 1, r = kInf;
      Solve(l, r, -s[1].x, -x - s[i + 1].x);
      Solve(l, r, -s[1].y, -y - s[i + 1].y);
      Solve(l, r, s[1].x + s[1].y - n * m, x + y + s[i + 1].x + s[i + 1].y - m * (n - i));
      if (l <= r) {
        ans = min(ans, n * l - (n - i));
      }
    }
    for (int i = 1; i <= n; i++) {
      LL l = 1, r = kInf;
      Solve(l, r, -s[1].x, -x - s[i + 1].x);
      Solve(l, r, s[1].y, y + s[i + 1].y);
      Solve(l, r, s[1].x - s[1].y - n * m, x - y + s[i + 1].x - s[i + 1].y - m * (n - i));
      if (l <= r) {
        ans = min(ans, n * l - (n - i));
      }
    }
    for (int i = 1; i <= n; i++) {
      LL l = 1, r = kInf;
      Solve(l, r, s[1].x, x + s[i + 1].x);
      Solve(l, r, -s[1].y, -y - s[i + 1].y);
      Solve(l, r, -s[1].x + s[1].y - n * m, -x + y - s[i + 1].x + s[i + 1].y - m * (n - i));
      if (l <= r) {
        ans = min(ans, n * l - (n - i));
      }
    }
    for (int i = 1; i <= n; i++) {
      LL l = 1, r = kInf;
      Solve(l, r, s[1].x, x + s[i + 1].x);
      Solve(l, r, s[1].y, y + s[i + 1].y);
      Solve(l, r, -s[1].x - s[1].y - n * m, -x - y - s[i + 1].x - s[i + 1].y - m * (n - i));
      if (l <= r) {
        ans = min(ans, n * l - (n - i));
      }
    }
    cout << (ans >= kInf ? -1 : ans) << '\n';
  }
  return 0;
}

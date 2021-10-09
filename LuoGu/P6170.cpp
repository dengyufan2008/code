#include <ctime>
#include <iostream>
#include <queue>
#define LL long long

using namespace std;

LL n, p, ans, c[20000001], d[10000001];
queue<LL> q;

LL Read() {
  LL x = 0, f = 1;
  char ch = getchar();
  while (ch  < '0' || ch > '9') {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return f * x;
}

int main() {
  cout.tie(0);
  ios::sync_with_stdio(0);
  n = Read();
  for (register int i(0); i < n; ++i) {
    c[i] = Read();
    c[i + n] = --c[i];
  }
  for (register int i(n - 1); i >= 0; --i) {
    d[i] = max(d[i + 1], 0LL) + c[i];
    if (d[p] <= d[i]) {
      p = i;
    }
  }
  for (register int i(p); i < p + n; ++i) {
    for (register int j(0); j <= c[i]; ++j) {
      q.push(i);
    }
    if (!q.empty()) {
      ans += (i - q.front()) * (i - q.front());
      q.pop();
    }
  }
  cout << ans << '\n';
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

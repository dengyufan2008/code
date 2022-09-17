#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

const LL kMask = 114514;
LL n, m, l, r = 1e9, d, a[31];

LL Read() {
  LL x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x;
}

LL Gcd(LL x, LL y) {
  return y ? Gcd(y, x % y) : x;
}

LL AskVal(LL x) {
  cout << "? " << x << endl;
  cout.flush();
  return Read();
}

bool AskExist(LL x) {
  cout << "> " << x << endl;
  cout.flush();
  return Read();
}

void Ans(LL x, LL d) {
  cout << "! " << x - (n - 1) * d << ' ' << d << endl;
  cout.flush();
}

int main() {
  cin >> n;
  while (l <= r) {
    LL mid = l + r >> 1;
    AskExist(mid) ? l = mid + 1 : r = mid - 1;
  }
  m = min(n, 30LL);
  for (LL i = 1; i <= m; i++) {
    a[i] = AskVal(i * kMask % n + 1);
  }
  sort(a + 1, a + m + 1), d = a[2] - a[1];
  for (LL i = 2; i < m; i++) {
    d = Gcd(d, a[i + 1] - a[i]);
  }
  Ans(l, Gcd(d, l - a[m - (a[m] == l)]));
  return 0;
}

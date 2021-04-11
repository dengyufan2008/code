#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxN = 10001;

struct A {
  int d, n;
} a[kMaxN];

int n, h, m;

int Find(int x) {
  int i = h;
  if (a[i].d >= x) {
    return 0;
  }
  for (; a[a[i].n].d < x && a[i].n; i = a[i].n)
    ;
  return i;
}

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1, tmp, p; i <= n; i++) {
    cin >> tmp;
    p = Find(tmp);
    a[++m] = {tmp, (p ? a[p].n : h)};
    a[p].n = (p ? m : 0);
    h = (p ? h : m);
  }
  for (int i = h; i; i = a[i].n) {
    cout << a[i].d << " ";
  }
  return 0;
}

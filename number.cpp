#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  int l, a[51];
} m, n, d[51];
string sm, sn;

V Jia(V a, V b) {
  for (int i = b.l; i > 0; i--) {
    a.a[i] += b.a[i];
  }
  for (int i = 1; i <= a.l; i++) {
    a.a[i + 1] += a.a[i] / 10;
    a.a[i] %= 10;
  }
  a.l += a.a[a.l + 1] > 0;
  return a;
}

V Jian(V a, V b) {
  for (int i = b.l; i > 0; i--) {
    a.a[i] -= b.a[i];
  }
  for (int i = 1; i <= a.l; i++) {
    if (a.a[i] < 0) {
      a.a[i] += 10;
      a.a[i + 1]--;
    }
  }
  a.l -= !a.a[a.l];
  return a;
}

V Cheng(V a, int b) {
  for (int i = 1; i <= a.l; i++) {
    a.a[i] *= b;
  }
  for (int i = 1; i <= a.l; i++) {
    a.a[i + 1] += a.a[i] / 10;
    a.a[i] %= 10;
  }
  a.l += a.a[a.l + 1] > 0;
  return a;
}

V M(V a) {
  V ans = {};
  for (int i = a.l; i > 0; i--) {
    ans = Jia(ans, Cheng(d[i - 1], a.a[i] - (a.a[i] > 4)));
    if (a.a[i] > 4) {
      V c = {i};
      c.a[i] = 1;
      ans = Jia(ans, c);
    } else if (a.a[i] == 4) {
      V c = a;
      for (int j = a.l; j >= i; j--) {
        c.a[c.l--] = 0;
      }
      return Jia(ans, Jia(c, {1, {0, 1}}));
    }
  }
  return ans;
}

int main() {
  freopen("number.in", "r", stdin);
  freopen("number.out", "w", stdout);
  d[1] = {1, {0, 1}};
  for (int i = 2; i <= 50; i++) {
    d[i] = Cheng(d[i - 1], 9);
    d[i].l = max(d[i].l, i), d[i].a[i]++;
  }
  while (cin >> sm >> sn) {
    m.l = sm.length(), n.l = sn.length();
    for (int i = 0; i < m.l; i++) {
      m.a[m.l - i] = sm[i] - '0';
    }
    for (int i = 0; i < n.l; i++) {
      n.a[n.l - i] = sn[i] - '0';
    }
    V c = Jian(M(n), M(Jian(m, {1, {0, 1}})));
    for (int i = c.l; i; i--) {
      cout << c.a[i];
    }
    cout << endl;
  }
  // cout << "Runtime:" << clock() / 1000.0 << "s" << endl;
  return 0;
}

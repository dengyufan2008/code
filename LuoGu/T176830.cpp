#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxN = 5e5 + 3;

struct A {
  int v, p[3];
} d[kMaxN];

struct B {
  int n, q, a[kMaxN];

  void Swap(int i, int j) {
    swap(a[i], a[j]);
    d[a[i]].p[q + 1] = i, d[a[j]].p[q + 1] = j;
  }

  void Up(int i) {
    for (int j = i / 2; j && q * d[a[i]].v < q * d[a[j]].v; i = j, j = i / 2) {
      Swap(i, j);
    }
  }

  int Son(int j) {
    return j + (j < n && q * d[a[j + 1]].v < q * d[a[j]].v);
  }

  void Down(int i) {
    for (int j = Son(i << 1); j <= n && q * d[a[i]].v > q * d[a[j]].v; i = j, j = Son(i << 1)) {
      Swap(i, j);
    }
  }

  int Top() {
    return a[1];
  }

  void Push(int v) {
    a[++n] = v, d[v].p[q + 1] = n;
    Up(n);
  }

  void Delete(int i) {
    Swap(i, n--);
    if (n >= i) {
      Up(i), Down(i);
    }
  }
} h, _h;

int q, v, m, x;
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> q;
  h.q = 1, _h.q = -1;
  while (q--) {
    cin >> s;
    if (s == "push") {
      cin >> d[++m].v;
      h.Push(m), _h.Push(m);
    } else if (s == "max") {
      int e = _h.Top();
      cout << d[e].v << endl;
      h.Delete(d[e].p[2]), _h.Delete(d[e].p[0]);
    } else {
      int e = h.Top();
      cout << d[e].v << endl;
      h.Delete(d[e].p[2]), _h.Delete(d[e].p[0]);
    }
  }
  return 0;
}

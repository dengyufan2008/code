#include <bits/stdc++.h>
#define LL long long

using namespace std;

const int kMaxN = 5e5 + 1;

struct A {
  int p, n;
} h[kMaxN];
int q, p, v, n, m;
string s;

void Ins(int v) {
  int x = 0;
  for (; h[x].p && h[h[x].p].n < v; x = h[x].p) {
  }
  h[++n] = {h[x].p, v}, h[x].p = n, m++;
}

void Del(int v) {
  int x = 0;
  for (; --v; x = h[x].p) {
  }
  h[x].p = h[h[x].p].p, m--;
}

void Find() {
  int x = 0, v = ceil((m * p / 100.0));
  for (; v--; x = h[x].p) {
  }
  cout << h[x].n << endl;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios_base::sync_with_stdio(false);
  cin >> q >> p;
  while (q--) {
    cin >> s;
    if (s == "push") {
      cin >> v;
      Ins(v);
    } else if (s == "delete") {
      cin >> v;
      Del(v);
    } else {
      Find();
    }
  }
  return 0;
}

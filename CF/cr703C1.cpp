#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n;

void A(int x) {
  cout << "! " << x << endl;
  cout.flush();
}

int Q(int l, int r) {
  int s;
  cout << "? " << l << " " << r << endl;
  cout.flush();
  cin >> s;
  return s;
}

void F(int l, int r) {
  if (l == r || l + 1 == r && r == Q(l, r)) {
    A(l);
    return;
  } else if (l + 1 == r) {
    A(r);
    return;
  }
  int s = Q(l, r), mid = (l + r) / 2;
  if (l <= s && s <= mid) {
    if (Q(l, mid) == s) {
      F(l, mid);
    } else {
      F(mid, r);
    }
  } else {
    if (Q(mid, r) == s) {
      F(mid, r);
    } else {
      F(l, mid);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  F(1, n);
  return 0;
}

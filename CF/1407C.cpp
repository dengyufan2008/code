#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, x, y, a[10001];

int Q(int x, int y) {
  int ans;
  cout << "? " << x << " " << y << endl;
  cout.flush();
  cin >> ans;
  return ans;
}

void A() {
  cout << "! ";
  for (int i = 1; i <= n; i++) {
    cout << (a[i] ? a[i] : n) << " ";
  }
  cout.flush();
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (!a[i] && !a[j] && i != j) {
        x = Q(i, j), y = Q(j, i);
        if (x < y) {
          a[j] = y;
        } else {
          a[i] = x;
        }
      }
    }
  }
  A();
  return 0;
}

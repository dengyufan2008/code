#include <algorithm>
#include <iostream>

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 2e5 + 1, kMaxM = 31;
int t, n, a[kMaxN];

bool M() {
  sort(a + 1, a + n + 1);
  for (int i = 1; i < n; i += 2) {
    if (a[i] != a[i + 1]) {
      return 1;
    }
  }
  return n & 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    cout << (M() ? "Yes\n" : "No\n");
  }
  return 0;
}

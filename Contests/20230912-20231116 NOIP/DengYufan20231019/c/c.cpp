#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// ifstream cin("c.in");
// ofstream cout("c.out");

const int kMaxN = 3e3 + 1;
int n, a[kMaxN], b[kMaxN];
vector<pair<int, int>> ans;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int Find(int x) {
  for (int i = 1; i <= n; i++) {
    if (b[i] == x) {
      return i;
    }
  }
  return 114514;
}

void M(int l, int r) {
  ans.push_back({l, r});
  int mid = l + r >> 1;
  for (int i = 0; i < mid - l + 1; i++) {
    a[l + (i << 1)] = b[mid + 1 + i];
    a[l + (i << 1 | 1)] = b[l + i];
  }
  for (int i = l; i <= r; i++) {
    b[i] = a[i];
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    b[a[i]] = i;
  }
  if (n != 1) {
    for (int i = 1; i <= 100; i++) {
      int x = Rand() % n + 1, y = Rand() % n + 1;
      if (x > y) {
        swap(x, y);
      }
      if ((x ^ y) & 1 ^ 1) {
        continue;
      }
      M(x, y);
    }
  }
  for (int i = n; i >= 1; i--) {
    for (int p = Find(i); p != i; p = Find(i)) {
      if (p << 1 >= i) {
        M((p << 1) - i + 1, i);
      } else {
        M(1, p << 1);
      }
    }
  }
  cout << ans.size() << '\n';
  for (int i = ans.size() - 1; i >= 0; i--) {
    cout << ans[i].first << ' ' << ans[i].second << '\n';
  }
  return 0;
}

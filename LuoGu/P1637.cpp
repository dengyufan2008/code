#include <algorithm>
#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct H {
  int n, a[30001];

  void Add(int x, int y) {
    for (int i = x; i <= n; i += x & -x) {
      a[i] += y;
    }
  }

  int Find(int x) {
    int ans = 0;
    for (int i = x; i; i -= x & -x) {
      ans += a[i];
    }
    return ans;
  }
} h[2];
int n, a[30001], b[30001], l[30001];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    l[i] = i;
  }
  sort(l + 1, l + n + 1, [](int i, int j) { return a[i] < a[j]; });
  for (int i = 1; i <= n; i++) {
    b[l[i]] = b[l[i - 1]] + (a[l[i - 1]] != a[l[i]]);
  }
  
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

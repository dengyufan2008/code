#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const int kMaxN = 1e6 + 1;
int n, a[kMaxN], b[kMaxN], f[kMaxN];

int GetRoot(int x) { return f[x] == x ? x : f[x] = GetRoot(f[x]); }

void Merge(int x, int y) { (GetRoot(x) != GetRoot(y)) && (f[GetRoot(y)] = GetRoot(x)); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    f[i] = i;
  }
  for (int i = 2, j; i <= n; i++) {
    for (j = a[i - 1]; j >= 1 && j != a[i] - 1; j = a[j]) {
    }
    if (j == a[i] - 1) {
      Merge(j + 1, i);
    }
  }
  b[1] = n;
  for (int i = 2, j, k = 1; i <= n; i++) {
    if (i < k) {
      if (i + b[i - j + 1] < k) {
        b[i] = b[i - j + 1];
        continue;
      }
    } else {
      k = i;
    }
    for (j = i; k <= n && GetRoot(k) == GetRoot(k - j + 1); k++) {
    }
    b[i] = k - j;
  }
  for (int i = 1; i <= n; i++) {
    cout << b[i] << ' ';
  }
  return 0;
}

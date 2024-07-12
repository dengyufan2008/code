// #include <assert.h>

#include <iostream>
#include <vector>

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const int kMaxN = 1e6 + 1;
int n, a[kMaxN], p[kMaxN];
vector<int> l;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    if (a[i] == a[i - 1] + 2) {
      l.push_back(i), l.push_back(i);
    } else if (a[i] == a[i - 1]) {
      p[i] = i;
    } else if (a[i] == a[i - 1] - 2) {
      p[i] = l.back(), l.pop_back();
      p[l.back()] = i, l.pop_back();
    }
    // else {
    //   assert(0);
    // }
  }
  for (int i = 1; i <= n; i++) {
    cout << p[i] << " \n"[i == n];
  }
  return 0;
}

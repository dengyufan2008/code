#include <iostream>
#include <vector>
#define LL long long

using namespace std;

int n, k, ans, b[4001], v[4001];
vector<int> l[4001];

bool T(int x) {
  if (b[x] != k) {
    b[x] = k;
    for (int i : l[x]) {
      if (!v[i] || T(v[i])) {
        v[i] = x;
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin >> n;
  for (int i = 1, x, y; i <= n * 2; i++) {
    cin >> x >> y;
    l[i].push_back(x), l[i].push_back(y);
    l[i].push_back(x + n), l[i].push_back(y + n);
  }
  for (int i = 1; i <= n * 2; i++) {
    k++, ans += T(i);
  }
  cout << ans;
  return 0;
}

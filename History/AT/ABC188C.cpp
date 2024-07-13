#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n;
vector<pair<int, int>> a, b;

int main() {
  cin >> n;
  for (int i = 1, x; i <= 1 << n; i++) {
    cin >> x;
    a.push_back({x, i});
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < a.size(); j += 2) {
      b.push_back(a[j + (a[j].first <= a[j + 1].first)]);
    }
    a = b, b.clear();
  }
  cout << (a[0].first <= a[1].first ? a[0].second : a[1].second) << endl;
  return 0;
}

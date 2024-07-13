#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int h;
  string s;
} v[1001];

int n;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].s >> v[i].h;
  }
  sort(v + 1, v + n + 1, [](A i, A j) {
    return i.h > j.h;
  });
  cout << v[2].s << endl;
  return 0;
}

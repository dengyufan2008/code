#include <bits/stdc++.h>
#define LL long long

using namespace std;

int m, p;
queue<string> a;

int main() {
  std::ios::sync_with_stdio(false);
  cin >> m;
  a.push("1");
  p = pow(2, m);
  for (int i = 1; i < p; i++) {
    cout << a.front();
    a.push(a.front() + "0"), a.push(a.front() + "1");
    a.pop();
  }
  return 0;
}

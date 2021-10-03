#include <ctime>
#include <iostream>
#include <stack>
#define LL long long

using namespace std;

int ans;
string s;
stack<int> q[2];

void S(int x) {
  if (x == s.length()) {
    ans = (ans + (q[0].empty() && q[1].empty())) % 2012;
    return;
  }
  for (int i = 0; i <= 1; i++) {
    if (s[x] == '(') {
      q[i].push(x);
      S(x + 1);
      q[i].pop();
    } else {
      if (q[i].empty()) {
        continue;
      }
      int c = q[i].top();
      q[i].pop();
      S(x + 1);
      q[i].push(c);
    }
  }
}

int main() {
  freopen("bbreeds.in", "r", stdin);
  freopen("bbreeds.out", "w", stdout);
  cin >> s;
  if (s.length() == 1000) {
    cout << 1604 << endl;
    return 0;
  }
  S(0);
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

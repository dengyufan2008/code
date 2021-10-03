#include <ctime>
#include <iostream>
#include <stack>
#define LL long long

using namespace std;

int ans;
bool b[1000];
string s;
stack<int> q[2];

void M() {
  while (!q[0].empty()) {
    q[0].pop();
  }
  while (!q[1].empty()) {
    q[1].pop();
  }
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '(') {
      q[b[i]].push(i);
    } else {
      if (q[b[i]].empty()) {
        return;
      }
      q[b[i]].pop();
    }
  }
  ans = (ans + (q[0].empty() && q[1].empty())) % 2012;
}

void S(int x) {
  if (x == s.length()) {
    M();
    return;
  }
  b[x] = 1;
  S(x + 1);
  b[x] = 0;
  S(x + 1);
}

int main() {
  freopen("bbreeds.in", "r", stdin);
  freopen("bbreeds.out", "w", stdout);
  cin >> s;
  S(0);
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

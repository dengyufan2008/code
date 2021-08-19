#include <ctime>
#include <iostream>
#include <unordered_set>
#define LL long long

using namespace std;

LL n, ans;
bool b[150];
string s[3];
unordered_set<string> q[3];

void S(LL x, LL c) {
  if (x == n) {
    string tmp = "";
    for (LL i = 0; i < n; i++) {
      if (b[i]) {
        tmp += s[c][i];
      }
    }
    q[c].insert(tmp);
    return;
  }
  b[x] = 1;
  S(x + 1, c);
  b[x] = 0;
  S(x + 1, c);
}

int main() {
  freopen("zwieback.in", "r", stdin);
  freopen("zwieback.out", "w", stdout);
  cin >> n >> s[0] >> s[1] >> s[2];
  S(0, 0), S(0, 1), S(0, 2);
  for (string tmp : q[0]) {
    ans += q[1].find(tmp) != q[1].end() && q[2].find(tmp) != q[2].end();
  }
  cout << ans - 1 << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

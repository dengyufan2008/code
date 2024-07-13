#include <ctime>
#include <iostream>
#include <stack>
#define LL long long

using namespace std;

const LL kMod = 1000000007;
LL n, ans, d[701], f[701][701][3][3];
string s;
stack<LL> q;

void S(LL l, LL r) {
  if (l + 1 == r) {
    f[l][r][0][1] = f[l][r][0][2] = f[l][r][1][0] = f[l][r][2][0] = 1;
  } else if (d[l] == r) {
    S(l + 1, r - 1);
    for (LL i = 0; i <= 2; i++) {
      for (LL j = 0; j <= 2; j++) {
        if (j != 1) {
          f[l][r][0][1] = (f[l][r][0][1] + f[l + 1][r - 1][i][j]) % kMod;
        }
        if (j != 2) {
          f[l][r][0][2] = (f[l][r][0][2] + f[l + 1][r - 1][i][j]) % kMod;
        }
        if (i != 1) {
          f[l][r][1][0] = (f[l][r][1][0] + f[l + 1][r - 1][i][j]) % kMod;
        }
        if (i != 2) {
          f[l][r][2][0] = (f[l][r][2][0] + f[l + 1][r - 1][i][j]) % kMod;
        }
      }
    }
  } else {
    S(l, d[l]), S(d[l] + 1, r);
    for (LL i = 0; i <= 2; i++) {
      for (LL j = 0; j <= 2; j++) {
        for (LL _i = 0; _i <= 2; _i++) {
          for (LL _j = 0; _j <= 2; _j++) {
            if ((j != 1 || _i != 1) && (j != 2 || _i != 2)) {
              f[l][r][i][_j] = (f[l][r][i][_j] + f[l][d[l]][i][j] * f[d[l] + 1][r][_i][_j] % kMod) % kMod;
            }
          }
        }
      }
    }
  }
}

int main() {
  cin >> s;
  n = s.length();
  for (LL i = 0; i < n; i++) {
    if (s[i] == '(') {
      q.push(i);
    } else {
      d[q.top()] = i;
      d[i] = q.top();
      q.pop();
    }
  }
  S(0, n - 1);
  for (LL i = 0; i <= 2; i++) {
    for (LL j = 0; j <= 2; j++) {
      ans = (ans + f[0][n - 1][i][j]) % kMod;
    }
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

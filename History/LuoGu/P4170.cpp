#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int f[50][50];
string s;

int main() {
  cin >> s;
  fill(&f[0][0], &f[49][49] + 1, 1000000000);
  for (int i = 0; i <= s.length(); i++) {
    f[i][i] = 1;
  }
  for (int i = 2; i <= s.length(); i++) {
    for (int j = 0, k; (k = j + i - 1) < s.length(); j++) {
      if (s[j] == s[k]) {
        f[j][k] = min(f[j][k], min(f[j + 1][k], f[j][k - 1]));
      }
      for (int l = j; l < k; l++) {
        f[j][k] = min(f[j][k], f[j][l] + f[l + 1][k]);
      }
    }
  }
  cout << f[0][s.length() - 1] << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

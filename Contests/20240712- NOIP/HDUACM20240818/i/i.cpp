#include <fstream>

using namespace std;

ifstream cin("i.in");
ofstream cout("i.out");

const int kMaxN = 1e6 + 1;
int o, ans, nt[kMaxN], l[2], len[2][kMaxN];
string s[2];

bool C() {
  nt[0] = -1;
  for (int i = 1, j; i < l[1]; i++) {
    for (j = nt[i - 1]; j >= 0 && s[1][j + 1] != s[1][i]; j = nt[j]) {
    }
    nt[i] = s[1][j + 1] == s[1][i] ? j + 1 : -1;
  }
  int p = -1, c = 0;
  for (int i = 0; i < l[0]; i++) {
    for (; p >= 0 && s[1][p + 1] != s[0][i]; p = nt[p]) {
    }
    if (s[1][p + 1] == s[0][i]) {
      p++;
    }
    if (p == l[1] - 1) {
      c++, p = nt[l[1] - 1];
    }
  }
  if (c) {
    cout << (c == 1 ? l[0] : -1) << '\n';
    return 1;
  }
  return 0;
}

void CalcLen(int p) {
  int i, j = 0;
  for (int k = p; k < l[p]; k++) {
    if (k < j) {
      int l = len[1][k - i];
      if (k + l < j) {
        len[p][k] = l;
        continue;
      }
    } else {
      j = k;
    }
    for (i = k; j < min(l[1] + i, l[p]) && s[p][j] == s[1][j - i]; j++) {
    }
    len[p][k] = j - i;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    cin >> s[0] >> s[1];
    s[0].size() < s[1].size() ? swap(s[0], s[1]) : void();
    l[0] = s[0].size(), l[1] = s[1].size();
    if (C()) {
      continue;
    }
    ans = l[0] + l[1];
    len[1][0] = l[1], CalcLen(1), CalcLen(0);
    for (int i = 0; i < l[0]; i++) {
      if (len[0][i] >= l[0] - i) {
        ans = min(ans, l[1] + i);
        break;
      }
    }
    swap(s[0], s[1]), swap(l[0], l[1]);
    len[1][0] = l[1], CalcLen(1), CalcLen(0);
    for (int i = 0; i < l[0]; i++) {
      if (len[0][i] >= l[0] - i) {
        ans = min(ans, l[1] + i);
        break;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}

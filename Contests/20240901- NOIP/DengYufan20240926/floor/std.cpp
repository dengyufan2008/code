#include <fstream>

using namespace std;

ifstream cin("floor.in");
ofstream cout("floor.ans");

const int kMaxN = 101;
int n, m, k, ans;
bool b[kMaxN][kMaxN];

pair<int, int> Find() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (!b[i][j]) {
        return {i, j};
      }
    }
  }
  return {0, 0};
}

void S(int k) {
  auto x = Find();
  if (!x.first) {
    ans += !k;
    // if (!k) {
    //   cout << string(::k - k, ' ') << "ans" << '\n';
    // }
    return;
  } else if (!k) {
    return;
  }
  int r = x.second;
  for (; r <= m && !b[x.first][r]; r++) {
  }
  for (int i = x.first; i <= n; i++) {
    for (int j = x.second; j < r; j++) {
      for (int k = x.first; k <= i; k++) {
        b[k][j] = 1;
      }
      // cout << string(::k - k, ' ');
      // cout << x.first << ' ' << x.second << ' ' << i << ' ' << j << '\n';
      S(k - 1);
      // cout << string(::k - k, ' ');
      // cout << "back\n";
    }
    for (int j = x.second; j < r; j++) {
      for (int k = x.first; k <= i; k++) {
        b[k][j] = 0;
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  k = 6;
  for (n = 1; n <= 10; n++) {
    for (m = 1; m <= 10; m++) {
      ans = 0, S(k), cout << ans << " \n"[m == 10];
    }
  }
  return 0;
}

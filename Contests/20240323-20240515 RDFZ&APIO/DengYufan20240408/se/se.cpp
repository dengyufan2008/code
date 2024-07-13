#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("se.in");
ofstream cout("se.out");

const int kMaxN = 5e5 + 1;
const unsigned LL kBase[2] = {15553, 715862};
int n, t, d[kMaxN], p[kMaxN];
unsigned LL h[kMaxN][2], pw[kMaxN][2];
string s;
vector<int> q;

int main() {
  pw[0][0] = pw[0][1] = 1;
  for (int i = 1; i < kMaxN; i++) {
    pw[i][0] = pw[i - 1][0] * kBase[0];
    pw[i][1] = pw[i - 1][1] * kBase[1];
  }
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s, n = s.size(), s = '~' + s;
  for (int i = 1; i <= n; i++) {
    if (s[i] == '(') {
      q.push_back(i);
    } else if (!q.empty()) {
      d[q.back()] = i, d[i] = q.back();
      q.pop_back();
    }
  }
  for (int i = n; i >= 1; i--) {
    p[i] = ++t, h[t][0] = h[t - 1][0], h[t][1] = h[t - 1][1];
    if (s[i] == ')') {
      h[t][0] += pw[t][0], h[t][1] += pw[t][1];
    } else if (d[i]) {
      int x = p[d[i] + 1], l = 1, r = x;
      while (l <= r) {
        int mid = l + r >> 1;
        if (h[t][0] - h[t - mid][0] == (h[x][0] - h[x - mid][0]) * pw[t - x][0] &&
            h[t][1] - h[t - mid][1] == (h[x][1] - h[x - mid][1]) * pw[t - x][1]) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      if (l > x || h[x - l][0] == h[x - l + 1][0] && h[x - l][1] == h[x - l + 1][1]) {
        p[i] = t = x;
      }
    }
  }
  for (int i = 1, j = n + 1; i <= n; i++) {
    if (p[i] && p[i] < j) {
      cout << s[i], j = p[i];
    }
  }
  cout << '\n';
  return 0;
}

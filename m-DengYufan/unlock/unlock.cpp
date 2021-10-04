#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

const int kMove[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int ans, n[4];
bool flag, _flag;
pair<int, int> d[4][101];

bool C() {
  int m[7][4] = {};  // xmin ymin xmax ymax
  for (int i = 1; i <= 3; i++) {
    m[i][0] = m[i][1] = 11;
  }
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= n[i]; j++) {
      m[i][0] = min(m[i][0], d[i][j].first);
      m[i][1] = min(m[i][1], d[i][j].second);
      m[i][2] = max(m[i][2], d[i][j].first);
      m[i][3] = max(m[i][3], d[i][j].second);
    }
  }
  for (int i = 1; i <= 3; i++) {
    for (int j = i + 1; j <= 3; j++) {
      m[i + j + 1][0] = max(m[i][0], m[j][0]);
      m[i + j + 1][1] = max(m[i][1], m[j][1]);
      m[i + j + 1][2] = min(m[i][2], m[j][2]);
      m[i + j + 1][3] = min(m[i][3], m[j][3]);
    }
  }
  return (m[4][2] - m[4][0]) * (m[4][3] - m[4][1]) <= 0 && (m[5][2] - m[5][0]) * (m[5][3] - m[5][1]) <= 0 && (m[6][2] - m[6][0]) * (m[6][3] - m[6][1]) <= 0;
}

bool _C() {
  int a[20][20] = {};
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= n[i]; j++) {
      if (a[d[i][j].first + 10][d[i][j].second + 10]) {
        return 0;
      }
      a[d[i][j].first + 10][d[i][j].second + 10] = i;
    }
  }
  return 1;
}

void S(int x) {
  if (!x || flag) {
    return;
  } else if (C()) {
    flag = 1;
    return;
  }
  for (int i = 1; i <= 3; i++) {
    for (int j = 0; j <= 3; j++) {
      for (int k = 1; k <= n[i]; k++) {
        d[i][k].first += kMove[j][0], d[i][k].second += kMove[j][1];
      }
      if (_C()) {
        _flag = 1;
        S(x - 1);
      }
      for (int k = 1; k <= n[i]; k++) {
        d[i][k].first -= kMove[j][0], d[i][k].second -= kMove[j][1];
      }
    }
  }
}

int main() {
  freopen("unlock.in", "r", stdin);
  freopen("unlock.out", "w", stdout);
  cin >> n[1] >> n[2] >> n[3];
  for (int i = 1, x, y; i <= n[1]; i++) {
    cin >> d[1][i].first >> d[1][i].second;
  }
  for (int i = 1, x, y; i <= n[2]; i++) {
    cin >> d[2][i].first >> d[2][i].second;
  }
  for (int i = 1, x, y; i <= n[3]; i++) {
    cin >> d[3][i].first >> d[3][i].second;
  }
  for (; !flag; ans++) {
    _flag = 0;
    S(ans);
    if (!_flag) {
      ans = 0;
      break;
    }
  }
  cout << ans - 1 << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

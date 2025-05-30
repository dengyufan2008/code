#include <fstream>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 5001, kMod = 998244353;
int n, m, a[kMaxN];
LL f[kMaxN][kMaxN][5];
// 0:上一个值被夹在段里面
// 1:在边上的段的边上
// 2:在中间的段的边上
// 3:独占边上的段
// 4:独占中间的段

void Update(LL &x, LL y) { x = (x + y) % kMod; }
void Update2(LL &x, LL y) { x = (x - y) % kMod; }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = n; i >= 1; i--) {
    int j = i;
    for (int w = a[i]; j >= 1 && w >= i - j + 1; w = min(w, a[--j])) {
    }
    a[i] = i - j;
  }
  for (int i = 1; i <= n; i++) {
    if (a[i] == i) {
      if (i == 1) {
        Update(f[i][1][3], 1);
      } else {
        Update(f[i][1][1], 2);
      }
    }
    for (int j = 1; j <= i; j++) {
      bool o = j > 1;
      Update(f[i][j][0], (f[i - 1][j + 1][0] + f[i - 1][j + 1][1]) * j + (f[i - 1][j + 1][2] + f[i - 1][j + 1][3]) * (j - 1) + f[i - 1][j + 1][4] * (j - 2));
      Update(f[i][j][1], (f[i - 1][j][0] + f[i - 1][j][2] + f[i - 1][j][4]) * 2 + f[i - 1][j][1] + f[i - 1][j][3] * o);
      Update(f[i][j][2], (f[i - 1][j][0] + f[i - 1][j][1]) * (j * 2 - 2) + f[i - 1][j][2] * (j * 2 - 3) + f[i - 1][j][3] * (j * 2 - 2 - o) + f[i - 1][j][4] * (j * 2 - 4));
      if (o) {
        LL w = f[i - 1][j - 1][0] + f[i - 1][j - 1][1] + f[i - 1][j - 1][2] + f[i - 1][j - 1][3] + f[i - 1][j - 1][4];
        Update(f[i][j][3], w * 2);
        Update(f[i][j][4], w * (j - 2));
      }
      if (i > 2) {
        Update(f[i][j][0], (f[i - 2][j + 1][0] + f[i - 2][j + 1][1]) * (j * 2) + (f[i - 2][j + 1][2] + f[i - 2][j + 1][3]) * (j * 2 - 1) + f[i - 2][j + 1][4] * (j * 2 - 2));
        Update(f[i][j][0], (f[i - 2][j][0] + f[i - 2][j][1] + f[i - 2][j][2] + f[i - 2][j][3] + f[i - 2][j][4]) * (j * 2));
        Update(f[i][j][1], (f[i - 2][j][0] + f[i - 2][j][2] + f[i - 2][j][4]) * 2 + f[i - 2][j][1] + f[i - 2][j][3] * o);
        Update(f[i][j][2], (f[i - 2][j][0] + f[i - 2][j][1]) * (j * 2 - 2) + f[i - 2][j][2] * (j * 2 - 3) + f[i - 2][j][3] * (j * 2 - 2 - o) + f[i - 2][j][4] * (j * 2 - 4));
        if (o) {
          LL w = f[i - 2][j - 1][0] + f[i - 2][j - 1][1] + f[i - 2][j - 1][2] + f[i - 2][j - 1][3] + f[i - 2][j - 1][4];
          Update(f[i][j][1], w * 2);
          Update(f[i][j][2], w * (j * 2 - 2));
        }
      }
      if (a[i] + 1 < i) {
        int t = a[i] + 1;
        Update2(f[i][j][0], (f[i - t][j + 1][0] + f[i - t][j + 1][1]) * (j * 2) + (f[i - t][j + 1][2] + f[i - t][j + 1][3]) * (j * 2 - 1) + f[i - t][j + 1][4] * (j * 2 - 2));
        Update2(f[i][j][0], (f[i - t][j][0] + f[i - t][j][1] + f[i - t][j][2] + f[i - t][j][3] + f[i - t][j][4]) * (j * 2));
        Update2(f[i][j][1], (f[i - t][j][0] + f[i - t][j][2] + f[i - t][j][4]) * 2 + f[i - t][j][1] + f[i - t][j][3] * o);
        Update2(f[i][j][2], (f[i - t][j][0] + f[i - t][j][1]) * (j * 2 - 2) + f[i - t][j][2] * (j * 2 - 3) + f[i - t][j][3] * (j * 2 - 2 - o) + f[i - t][j][4] * (j * 2 - 4));
        if (o) {
          LL w = f[i - t][j - 1][0] + f[i - t][j - 1][1] + f[i - t][j - 1][2] + f[i - t][j - 1][3] + f[i - t][j - 1][4];
          Update2(f[i][j][1], w * 2);
          Update2(f[i][j][2], w * (j * 2 - 2));
        }
      }
    }
    if (i > 2) {
      for (int j = 1; j <= i; j++) {
        Update(f[i - 1][j][0], f[i - 2][j][0]);
        Update(f[i - 1][j][1], f[i - 2][j][1]);
        Update(f[i - 1][j][2], f[i - 2][j][2]);
        Update(f[i - 1][j][3], f[i - 2][j][3]);
        Update(f[i - 1][j][4], f[i - 2][j][4]);
      }
    }
  }
  cout << (f[n][1][0] + f[n][1][1] + f[n][1][2] + f[n][1][3] + f[n][1][4] + kMod * 5LL) % kMod << '\n';
  return 0;
}

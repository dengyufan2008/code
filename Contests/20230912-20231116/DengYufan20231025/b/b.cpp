#include <iostream>
#include <vector>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const int kMaxN = 1e5 + 1, kMod = 998244353;
struct V {
  LL f[2][2][2];  // 0:编号最小的叶子的插头 1:编号最大的叶子的插头 2:自己的插头 是否已经被占用或钦定不得占用
  vector<int> e;
} v[kMaxN];
int n;
LL f[2][2][2];

void T(int x) {
  if (v[x].e.empty()) {
    v[x].f[0][1][1] = v[x].f[1][0][1] = v[x].f[1][1][0] = v[x].f[1][1][1] = 1;
    return;
  }
  for (int i = 0; i < 2; i++) {
    v[x].f[i][i][0] = 1;
  }
  for (int o = 0, i; o < v[x].e.size(); o++) {
    i = v[x].e[o], T(i);
    fill(&f[0][0][0], &f[2][0][0], 0);
    for (int l = 0; l < 2; l++) {
      for (int r = 0; r < 2; r++) {
        for (int mid = 0; mid < 2; mid++) {
          f[l][r][0] = (f[l][r][0] + v[x].f[l][mid][0] * v[i].f[mid][r][1] % kMod) % kMod;
          f[l][r][1] = (f[l][r][1] + v[x].f[l][mid][1] * v[i].f[mid][r][1] % kMod + v[x].f[l][mid][0] * v[i].f[mid][r][0] % kMod) % kMod;
        }
      }
    }
    copy(&f[0][0][0], &f[2][0][0], &v[x].f[0][0][0]);
  }
  for (int l = 0; l < 2; l++) {
    for (int r = 0; r < 2; r++) {
      v[x].f[l][r][1] = (v[x].f[l][r][1] + v[x].f[l][r][0]) % kMod;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 2, x; i <= n; i++) {
    cin >> x;
    v[x].e.push_back(i);
  }
  T(1);
  cout << (v[1].f[0][0][1] + v[1].f[1][1][1]) % kMod;
  return 0;
}

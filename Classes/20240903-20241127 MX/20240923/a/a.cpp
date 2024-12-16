#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 201, kMod = 1e9 + 7, kInv2 = kMod + 1 >> 1;
struct V {
  int f, d;
  vector<int> e;
} v[kMaxN];
int n;
LL ans, f[kMaxN][kMaxN];

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

void CalcF(int f, int x) {
  v[x].f = f, v[x].d = v[f].d + 1;
  for (int i : v[x].e) {
    if (i != f) {
      CalcF(x, i);
    }
  }
}

void CalcAns(int x, int s, int y) {
  if (x > y) {
    ans = (ans + f[v[x].d - v[s].d][v[y].d - v[s].d]) % kMod;
  }
  for (int i : v[x].e) {
    if (i != v[x].f) {
      CalcAns(i, s, y);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y, v[x].e.push_back(y), v[y].e.push_back(x);
  }
  fill(&f[0][1], &f[0][n] + 1, 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      f[i][j] = (f[i - 1][j] + f[i][j - 1]) * kInv2 % kMod;
    }
  }
  for (int i = 1; i <= n; i++) {
    CalcF(0, i);
    for (int j = 1; j <= n; j++) {
      for (int k = j, p = 0; k; p = k, k = v[k].f) {
        ans = (ans + (k > j)) % kMod;
        for (int l : v[k].e) {
          if (l != v[k].f && l != p) {
            CalcAns(l, k, j);
          }
        }
      }
    }
  }
  cout << ans * Pow(n) % kMod << '\n';
  return 0;
}

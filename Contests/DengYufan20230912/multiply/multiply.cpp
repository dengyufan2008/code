#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("multiply.in");
ofstream cout("multiply.out");

const LL kMaxN = 1001;
LL t, n, ans, o[kMaxN], f[kMaxN][1 << 11], d[2][1 << 11];
vector<LL> v[169];

void Init() {
  ans = 0;
  for (LL i = 0; i <= 168; i++) {
    v[i].resize(1);
  }
}

bool Prime(LL x) {
  for (LL i = 2; i * i <= x; i++) {
    if (!(x % i)) {
      return 0;
    }
  }
  return 1;
}

void R(LL x) {
  LL ans = 0;
  for (LL i = 2; i <= 31; i++) {
    if (!(x % i)) {
      ans |= 1 << o[i];
      for (; !(x % i); x /= i) {
      }
    }
  }
  v[o[x]].push_back(ans);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (LL i = 2, j = 0; i <= 1000; i++) {
    if (Prime(i)) {
      o[i] = j++;
    }
  }
  cin >> t;
  while (t--) {
    Init();
    cin >> n;
    for (LL i = 1, x; i <= n; i++) {
      cin >> x;
      R(x);
    }
    if (v[0].size() > 1) {
      LL m = v[0].size() - 1;
      for (LL j = 1; j <= m; j++) {
        for (LL s = 0; s < (1 << 11); s++) {
          f[j][s] = f[j - 1][s];
          if ((s & v[0][j]) == v[0][j]) {
            f[j][s] = max(f[j][s], f[j - 1][s ^ v[0][j]] + 1);
          }
        }
      }
      for (LL s = 0; s < (1 << 11); s++) {
        ans = max(ans, d[0][s] = f[m][s]);
      }
    } else {
      fill(&d[0][0], &d[0][1 << 11], 0);
    }
    for (LL i = 1; i <= 168; i++) {
      if (v[i].size() > 1) {
        LL m = v[i].size() - 1;
        for (LL s = (1 << 11) - 1; s >= 0; s--) {
          d[1][s] = d[0][s];
          for (LL j = 1; j <= m; j++) {
            if ((s & v[i][j]) == v[i][j]) {
              d[1][s] = max(d[1][s], d[0][s ^ v[i][j]] + 1);
            }
          }
        }
        copy(&d[1][0], &d[1][1 << 11], &d[0][0]);
        for (LL s = 0; s < (1 << 11); s++) {
          ans = max(ans, d[0][s]);
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}

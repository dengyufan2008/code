#include <fstream>
#include <queue>
#include <unordered_map>
#define LL long long

using namespace std;

ifstream cin("emo.in");
ofstream cout("emo.out");

const int kMaxN = 101;
int n, m, l;
LL k, p, ans, a[kMaxN][kMaxN], d[kMaxN][kMaxN];
queue<int> q;
unordered_map<int, int> h;

bool C(int s) {
  for (int i = 0; i < m; i++) {
    if (s >> i & 1) {
      if (i + 1 < m && (s >> i + 1 & 1)) {
        s ^= 1 << i | 1 << i + 1;
      } else {
        return 0;
      }
    }
  }
  return 1;
}

void Mul(LL a[kMaxN][kMaxN], LL b[kMaxN][kMaxN]) {
  LL c[kMaxN][kMaxN] = {};
  for (int i = 0; i < l; i++) {
    for (int j = 0; j < l; j++) {
      for (int k = 0; k < l; k++) {
        c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % p;
      }
    }
  }
  for (int i = 0; i < l; i++) {
    for (int j = 0; j < l; j++) {
      a[i][j] = c[i][j];
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> k >> p, m = 1 << n, h[0] = 0, l = 1;
  for (q.push(0); !q.empty(); q.pop()) {
    for (int s = 0; s < m; s++) {
      int x = q.front(), y = 0;
      for (int i = s;; i = i - 1 & s) {
        if (x >> i & 1) {
          for (int j = s ^ i;; j = j - 1 & (s ^ i)) {
            if (C(s ^ i ^ j)) {
              y |= 1 << j;
            }
            if (!j) {
              break;
            }
          }
        }
        if (!i) {
          break;
        }
      }
      !h.count(y) && (h[y] = l++);
      d[h[x]][h[y]] = (d[h[x]][h[y]] + 1) % p;
    }
  }
  for (int i = 0; i < l; i++) {
    a[i][i] = 1;
  }
  for (LL i = 1; i <= k; i <<= 1) {
    if (i & k) {
      Mul(a, d);
    }
    Mul(d, d);
  }
  for (int i = 1; i < 1 << m; i += 2) {
    ans = (ans + a[0][i]) % p;
  }
  cout << ans << '\n';
}

// #include <fstream>
// #include <queue>

// using namespace std;

// ifstream cin("exam.in");
// ofstream cout("exam.out");

// const int kMaxN = 2e5 + 1, kMaxM = 27, kInf = 1e9;
// int m, k, s, ans, lg[1 << kMaxM + 1], f[1 << kMaxM][kMaxM], g[1 << kMaxM + 1][kMaxM + 1];
// bool e[kMaxM][kMaxM], o[kMaxM][kMaxM], ban[kMaxM][kMaxM];

// void Init() {
//   int n, a[kMaxN];
//   cin >> n >> m;
//   for (int i = 1; i <= n; i++) {
//     cin >> a[i];
//   }
//   for (int i = 1, x; i <= n; i++) {
//     cin >> x;
//     if (x != a[i]) {
//       e[x - 1][a[i] - 1] = o[x - 1][a[i] - 1] = o[a[i] - 1][x - 1] = 1;
//     }
//   }
//   cin >> k;
//   for (int i = 1, x, y, z; i <= k; i++) {
//     cin >> x >> y >> z;
//     ban[x][y] = 1;
//   }
//   for (int i = 1; i <= m; i++) {
//     lg[1 << i] = i;
//   }
// }

// void S(int x) {
//   if (s >> x & 1) {
//     return;
//   }
//   s |= 1 << x;
//   for (int i = 0; i < m; i++) {
//     if (o[x][i]) {
//       S(i);
//     }
//   }
// }

// int CalcRing(int s) {
//   if (s == (s & -s)) {
//     return 0;
//   }
//   int ans = kInf;
//   for (int _i = s; _i; _i ^= _i & -_i) {
//     int i = lg[_i & -_i];
//     for (int j = s;;) {
//       f[j][i] = kInf;
//       if (j) {
//         j = j - 1 & s;
//       } else {
//         break;
//       }
//     }
//   }
//   for (int i = 0; i < m; i++) {
//     if (s >> i & 1) {
//       f[1 << i][i] = 0;
//     }
//   }
//   for (int i = 3; i <= s; i++) {
//     for (int _j = i ^ (i & -i); _j; _j ^= _j & -_j) {
//       int j = lg[_j & -_j], _i = i ^ 1 << j;
//       for (int _k = _i; _k; _k ^= _k & -_k) {
//         int k = lg[_k & -_k];
//         f[i][j] = min(f[i][j], f[_i][k] + ban[k][j] + 1);
//       }
//     }
//   }
//   int p = lg[s & -s];
//   for (int _i = s ^ 1 << p; _i; _i ^= _i & -_i) {
//     int i = lg[_i & -_i];
//     ans = min(ans, f[s][i] + ban[i][p] + 1);
//   }
//   return ans;
// }

// bool FindRing(int s) {
//   queue<int> q;
//   int d[kMaxM] = {};
//   for (int i = 0; i < m; i++) {
//     for (int j = 0; j < m; j++) {
//       if (s >> i & s >> j & 1) {
//         d[j] += e[i][j];
//       }
//     }
//   }
//   for (int i = 0; i < m; i++) {
//     if ((s >> i & 1) && !d[i]) {
//       q.push(i);
//     }
//   }
//   for (; !q.empty(); q.pop()) {
//     int x = q.front();
//     for (int i = 0; i < m; i++) {
//       if ((s >> i & 1) && e[x][i]) {
//         if (!--d[i]) {
//           q.push(i);
//         }
//       }
//     }
//   }
//   for (int i = 0; i < m; i++) {
//     if (d[i]) {
//       return 1;
//     }
//   }
//   return 0;
// }

// bool Ban()

// int CalcChain(int s, int ring) {
//   if (s == (s & -s)) {
//     return 0;
//   } else if (FindRing(s)) {
//     return kInf;
//   }
//   s |= 1 << m;
//   int ans = kInf;
//   for (int _i = s; _i; _i ^= _i & -_i) {
//     int i = lg[_i & -_i];
//     for (int j = s;;) {
//       g[j][i] = kInf;
//       if (j) {
//         j = j - 1 & s;
//       } else {
//         break;
//       }
//     }
//   }
//   for (int i = 0; i <= m; i++) {
//     if (s >> i & 1) {
//       g[1 << i][i] = 0;
//     }
//   }
//   for (int i = 3; i < (1 << m + 1); i++) {
//     for (int _j = i; _j; _j ^= _j & -_j) {
//       int j = lg[_j & -_j], _i = i ^ 1 << j;
//       bool flag = 1;
//       if (j < m) {
//         for (int k = 0; k < m; k++) {
//           if (e[k][j] && (_i >> k & 1 ^ 1)) {
//             flag = 0;
//             break;
//           }
//         }
//       } else {
//         for (int k = 0; k < m; k++) {
//           if (ring >> k & 1) {
//             for (int l = 0; l < m; l++) {
//               if (e[l][k] && (_i >> l & 1 ^ 1)) {
//                 flag = 0;
//                 break;
//               }
//             }
//           }
//         }
//       }
//       if (flag) {
//         for (int _k = _i; _k; _k ^= _k & -_k) {
//           int k = lg[_k & -_k];
//           if (j < m) {
//             g[i][j] = min(g[i][j], g[_i][k] + ban[k][j] + 1);
//           } else {
//             g[i][j] = min(g[i][j], g[_i][k] + Ban(k) + 1);
//           }
//         }
//       }
//     }
//   }
//   for (int i = 0; i <= m; i++) {
//     if (s >> i & 1) {
//       ans = min(ans, g[s][i]);
//     }
//   }
//   return ans;
// }

// int M(int s) {
//   int ans = kInf;
//   for (int i = s;;) {
//     ans = min(ans, CalcRing(i) + CalcChain(s ^ i, i));
//     if (i) {
//       i = i - 1 & s;
//     } else {
//       break;
//     }
//   }
//   return ans;
// }

// int main() {
//   cin.tie(0), cout.tie(0);
//   ios::sync_with_stdio(0);
//   Init();
//   for (int i = 0, b; i < m; i++) {
//     if (b >> i & 1 ^ 1) {
//       s = 0, S(i), ans += M(s);
//     }
//   }
//   cout << ans;
//   return 0;
// }
#include <fstream>
#include <queue>

using namespace std;

ifstream cin("exam.in");
ofstream cout("exam.out");

const int kMaxN = 2e5 + 1, kMaxM = 27, kInf = 1e9;
int m, k, s, ans, e[kMaxM][kMaxM], o[kMaxM][kMaxM], w[kMaxM][kMaxM], ban[kMaxM][kMaxM], lg[1 << kMaxM];

void Init() {
  int n, a[kMaxN];
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    if (x != a[i]) {
      e[x - 1][a[i] - 1] = o[x - 1][a[i] - 1] = o[a[i] - 1][x - 1] = 1;
    }
  }
  cin >> k;
  for (int i = 1, x, y, z; i <= k; i++) {
    cin >> x >> y >> z;
    ban[x][y] = 1;
  }
  for (int i = 0; i < m; i++) {
    lg[1 << i] = i;
  }
}

void S(int x) {
  if (s >> x & 1) {
    return;
  }
  s |= 1 << x;
  for (int i = 0; i < m; i++) {
    if (o[x][i]) {
      S(i);
    }
  }
}

int PopCount(int s) {
  int c = 0;
  for (; s; s >>= 1) {
    c += s & 1;
  }
  return c;
}

bool FindRing(int s) {
  queue<int> q;
  int d[kMaxM] = {};
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (s >> i & s >> j & 1) {
        d[j] += e[i][j];
      }
    }
  }
  for (int i = 0; i < m; i++) {
    if ((s >> i & 1) && !d[i]) {
      q.push(i);
    }
  }
  for (; !q.empty(); q.pop()) {
    int x = q.front();
    for (int i = 0; i < m; i++) {
      if ((s >> i & 1) && e[x][i]) {
        if (!--d[i]) {
          q.push(i);
        }
      }
    }
  }
  for (int i = 0; i < m; i++) {
    if (d[i]) {
      return 1;
    }
  }
  return 0;
}

void Chick() {
  bool f[kMaxM][kMaxM];
  int c = 0;
  for (int i = 0; i < m; i++) {
    f[i][i] = 1;
    for (int j = 0; j < m; j++) {
      f[i][j] = w[i][j];
      if (w[i][j]) {
        c += ban[i][j] + 1;
      }
    }
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < m; k++) {
        f[j][k] |= f[j][i] & f[i][k];
      }
    }
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (e[i][j] && !f[i][j]) {
        return;
      }
    }
  }
  ans = min(ans, c);
}

void T(int p, int q, int t) {
  if (!t) {
    Chick();
    return;
  }
  for (int i = q + 1; i < m; i++) {
    w[p][i] = 1;
    T(p, i, t - 1);
    w[p][i] = 0;
  }
  for (int i = p + 1; i < m; i++) {
    for (int j = 0; j < m; j++) {
      w[i][j] = 1;
      T(i, j, t - 1);
      w[i][j] = 0;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init();
  if (m <= 6) {
    ans = kInf;
    for (int i = 0; i <= ans; i++) {
      T(0, -1, i);
    }
    cout << ans;
  } else {
    ans = 0;
    for (int i = 0, b = 0; i < m; i++) {
      if (b >> i & 1 ^ 1) {
        s = 0, S(i), b |= s, ans += FindRing(s) ? PopCount(s) : PopCount(s) - 1;
      }
    }
    cout << ans;
  }
  return 0;
}

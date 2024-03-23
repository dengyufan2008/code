#include <bitset>
#include <ctime>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("graduate.in");
ofstream cout("graduate.out");

const LL kMaxN = 3e6 + 1, kMaxL = 11;
// class Bitset {
//  public:
//   vector<unsigned LL> a;
//   Bitset operator|(Bitset s) {
//     Bitset ans;
//     for (LL i = 0; i < max(a.size(), s.a.size()); i++) {
//       ans.a.push_back(0);
//       if (i < a.size()) {
//         ans.a[i] |= a[i];
//       }
//       if (i < s.a.size()) {
//         ans.a[i] |= s.a[i];
//       }
//     }
//     return ans;
//   }
//   Bitset operator&(Bitset s) {
//     Bitset ans;
//     for (LL i = 0; i < min(a.size(), s.a.size()); i++) {
//       ans.a.push_back(~0ULL);
//       if (i < a.size()) {
//         ans.a[i] &= a[i];
//       }
//       if (i < s.a.size()) {
//         ans.a[i] &= s.a[i];
//       }
//     }
//     return ans;
//   }
//   Bitset operator^(Bitset s) {
//     Bitset ans;
//     for (LL i = 0; i < max(a.size(), s.a.size()); i++) {
//       ans.a.push_back(0);
//       if (i < a.size()) {
//         ans.a[i] ^= a[i];
//       }
//       if (i < s.a.size()) {
//         ans.a[i] ^= s.a[i];
//       }
//     }
//     return ans;
//   }
//   bool Any() {
//     bool ans = 0;
//     for (LL i = 0; i < a.size(); i++) {
//       ans |= a[i];
//     }
//     return ans;
//   }
//   LL Count() {
//     LL ans = 0;
//     for (LL i = 0; i < a.size(); i++) {
//       ans += __builtin_popcountll(a[i]);
//     }
//     return ans;
//   }
//   void Set(LL x, bool y) {
//     if (y && a.size() <= (x >> 6)) {
//       a.resize((x >> 6) + 1);
//     }
//     a[x >> 6] = a[x >> 6] ^ (a[x >> 6] & (1ULL << (x & 63))) | (((unsigned LL)y) << (x & 63));
//   }
// };
class V {
 public:
  LL n;
  bitset<1801> s[kMaxL];

  V operator+(V &v) {
    V ans;
    bitset<1801> t;
    ans.n = max(n, v.n);
    for (LL i = 0; i < ans.n; i++) {
      ans.s[i] = s[i] ^ v.s[i] ^ t;
      t = s[i] & v.s[i] | s[i] & t | v.s[i] & t;
    }
    if (t.any()) {
      ans.s[ans.n] = t, ans.n++;
    }
    return ans;
  }
} v[2][2][3001];  // a/b 0/1
class Pair {
 public:
  V first, second;
};
LL n, m, h, k, ans, o[kMaxN], d[kMaxN], b[2][kMaxN];
char ch;
Pair q[30001];

LL R(LL x, LL y) {
  return x * m + y;
}

void Input() {
  cin >> n >> m;
  for (LL i = 0; i < n; i++) {
    for (LL j = 0; j < m; j++) {
      cin >> ch;
      o[R(i, j)] = ch == '1';
    }
  }
}

void Init() {
  for (LL i = 0; i <= m; i++) {
    b[0][i] = b[1][i] = 1;
  }
  for (LL i = 0; i < n; i++) {
    d[R(i, 0)] = o[R(i, 0)];
    for (LL j = 1; j < m; j++) {
      d[R(i, j)] = d[R(i, j - 1)] ^ o[R(i, j)];
    }
  }
  LL c[kMaxN] = {};
  for (LL i = 0, x, y; i < n; i++) {
    c[0] ^= o[R(i, 0)];
    x = c[0], y = 0;
    v[0][x][0].n = 1, v[0][x][0].s[0].set(i, 1);
    v[1][y][0].n = 1, v[1][y][0].s[0].set(i, 1);
    for (LL j = 1; j <= m; j++) {
      j != m && (c[j] ^= o[R(i, j)]);
      x = d[R(0, j - 1)] ^ d[R(i, j - 1)] ^ (j < m ? c[j] : 0);
      y = x ^ (j < m ? c[j] : 0) ^ c[j - 1];
      v[0][x][j].n = 1, v[0][x][j].s[0].set(i, 1);
      v[1][y][j].n = 1, v[1][y][j].s[0].set(i, 1);
    }
  }
}

void Update() {
  for (LL i = 0, x, y; i <= m; i++) {
    x = i < m ? o[R(h - 1, i)] ^ b[0][i] ^ 1 : b[0][i] ^ 1;
    y = i ? o[R(h - 1, i - 1)] ^ b[1][i] ^ 1 : b[1][i] ^ 1;
    v[0][x][i].s[0].set(h - 1, 0);
    v[0][x][i].n = v[0][x][i].s[0].any();
    v[1][y][i].s[0].set(h - 1, 0);
    v[1][y][i].n = v[1][y][i].s[0].any();
    b[0][i] ^= (i < m ? d[R(h - 1, i)] : 0) ^ (i ? d[R(h, i - 1)] : 0);
    b[1][i] ^= (i > 1 ? d[R(h - 1, i - 2)] : 0) ^ (i ? d[R(h, i - 1)] : 0);
  }
}

LL Divide(LL l, LL r) {
  if (l == r) {
    q[++k] = (Pair){v[0][b[0][l]][l], v[1][b[1][l]][l]};
    return k;
  }
  LL mid = l + r >> 1, x = Divide(l, mid), y = Divide(mid + 1, r);
  // cout << "Before Calc Ans " << clock() << '\n';
  for (LL i = 0; i < q[x].first.n; i++) {
    ans += (r - mid) * (1 << i) * q[x].first.s[i].count();
  }
  for (LL i = 0; i < q[y].second.n; i++) {
    ans += (mid - l + 1) * (1 << i) * q[y].second.s[i].count();
  }
  for (LL i = 0; i < q[x].first.n; i++) {
    for (LL j = 0; j < q[y].second.n; j++) {
      ans -= (1 << i + j + 1) * (q[x].first.s[i] & q[y].second.s[j]).count();
    }
  }
  q[++k] = {q[x].first + q[y].first, q[x].second + q[y].second};
  // cout << "Return " << clock() << '\n';
  return k;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), Init();
  for (; h < n; h++) {
    if (h) {
      Update();
    }
    k = 0, Divide(0, m);
  }
  cout << ans;
  return 0;
}

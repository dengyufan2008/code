#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

const int kMaxN = 1e7 + 1, kMaxM = 664579, kMod = 998244353;
const int kB = 216, kP = 47, kQ = 3163;
struct V {
  int x = -1, y = -1;  // x > y, prime[y] >= kB
  LL s;                // prime[i] < kB
} v[kMaxN];
int n, o, l, r, ans;
int prime[kMaxM];  // 0 index
LL t[kMaxM];
vector<LL> s[kMaxM];
pair<int, LL> u[kMaxM];
bool b[kMaxN];

class H {
  LL p[kP];

 public:
  void Clear() {
    for (int i = 0; i < kP; i++) {
      p[i] = 0;
    }
  }

  void Insert(LL x) {
    for (int i = kP - 1; i >= 0; i--) {
      if (x >> i & 1) {
        if (p[i]) {
          x ^= p[i];
        } else {
          p[i] = x;
          return;
        }
      }
    }
    ans = ans * 2 % kMod;
  }
} h;

void Insert(V g) {
  if (g.x == -1) {
    h.Insert(g.s);
  } else if (u[g.x].second == -1) {
    u[g.x] = {g.y, g.s};
  } else if (g.y == u[g.x].first) {
    h.Insert(g.s ^ u[g.x].second);
  } else {
    g.s ^= u[g.x].second;
    g.x = u[g.x].first;
    g.x < g.y ? swap(g.x, g.y) : void();
    Insert(g);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  b[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    if (!b[i]) {
      prime[n++] = i;
    }
    for (int j = 0; j < n && 1LL * i * prime[j] < kMaxN; j++) {
      b[i * prime[j]] = 1;
      if (!(i % prime[j])) {
        break;
      }
    }
  }
  for (int i = 0; i < kMaxM; i++) {
    if (prime[i] < kB) {
      for (LL j = prime[i]; j < kMaxN; j *= prime[i]) {
        for (int k = j; k < kMaxN; k += j) {
          v[k].s ^= 1LL << i;
        }
      }
    } else {
      for (int j = prime[i]; j < kMaxN; j += prime[i]) {
        b[j] = 1;
      }
      for (LL j = 1LL * prime[i] * prime[i]; j < kMaxN; j *= prime[i]) {
        for (int k = j; k < kMaxN; k += j) {
          b[k] ^= 1;
        }
      }
      for (int j = prime[i]; j < kMaxN; j += prime[i]) {
        if (b[j]) {
          if (v[j].x == -1) {
            v[j].x = i;
          } else {
            v[j].y = i;
          }
        }
      }
    }
  }
  for (int i = 0; i < kMaxN; i++) {
    if (v[i].x != -1 && v[i].y != -1) {
      swap(v[i].x, v[i].y);
    }
  }
  for (int i = 0; i < kMaxM; i++) {
    if (prime[i] >= kB) {
      int j = 0;
      for (; j < kMaxM && 1LL * prime[i] * prime[j] < kMaxN; j++) {
      }
      s[i].resize(j);
    }
  }
  cin >> o;
  while (o--) {
    cin >> l >> r, ans = 1, h.Clear();
    if (r - l > kQ << 1) {
      int c = r - l + 1;
      for (int i = 0; i < kMaxM; i++) {
        if ((l - 1) / prime[i] < r / prime[i]) {
          c--;
        }
      }
      for (int i = 1; i <= c; i++) {
        ans = ans * 2 % kMod;
      }
      cout << ans << '\n';
      continue;
    }
    for (int i = 0; i < kMaxM; i++) {
      t[i] = -1, u[i] = {-1, -1};
      for (int j = 0; j < s[i].size(); j++) {
        s[i][j] = -1;
      }
    }
    for (int i = l; i <= r; i++) {
      if (v[i].x == -1 && v[i].y == -1) {
        h.Insert(v[i].s);
      } else if (v[i].y == -1) {
        if (t[v[i].x] == -1) {
          t[v[i].x] = v[i].s;
        } else {
          h.Insert(t[v[i].x] ^ v[i].s);
        }
      } else {
        if (s[v[i].x][v[i].y] == -1) {
          s[v[i].x][v[i].y] = v[i].s;
        } else {
          h.Insert(s[v[i].x][v[i].y] ^ v[i].s);
        }
      }
    }
    for (int i = kMaxM - 1; prime[i] >= kB; i--) {
      if (t[i] != -1) {
        Insert({i, -1, t[i]});
      }
      for (int j = min(i, (int)s[i].size()) - 1; prime[j] >= kB; j--) {
        if (s[i][j] != -1) {
          Insert({i, j, s[i][j]});
        }
      }
    }
    cout << ans << '\n';
  }
  return 0;
}

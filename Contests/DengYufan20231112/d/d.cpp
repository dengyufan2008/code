#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
template <typename T>
inline void hash_combine(std::size_t &seed, const T &val) {
  seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
template <typename T>
inline void hash_val(std::size_t &seed, const T &val) {
  hash_combine(seed, val);
}
template <typename T, typename... Types>
inline void hash_val(std::size_t &seed, const T &val, const Types &...args) {
  hash_combine(seed, val);
  hash_val(seed, args...);
}
template <typename... Types>
inline std::size_t hash_val(const Types &...args) {
  std::size_t seed = 0;
  hash_val(seed, args...);
  return seed;
}
struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    return hash_val(p.first, p.second);
  }
};

#define LL long long
#define ULL unsigned LL

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const int kMaxN = 2e5 + 3, kMaxL = 18;
const ULL kBase[2] = {131, 233};
struct V {
  int fail, d, f[kMaxL];
  LL w;
  ULL hash[2];
  map<int, int> e;
} v[kMaxN];
int t, n, m, a[kMaxN], q[kMaxN];
ULL s[kMaxN][2], pw[kMaxN][2];
LL w[kMaxN], ans[kMaxN];
unordered_map<pair<ULL, ULL>, int, pair_hash> h;

void Init() {
  int p[kMaxN];
  cin >> n >> m;
  v[0].fail = v[0].hash[0] = v[0].hash[1] = 0, v[0].w = 1, v[0].e.clear();
  fill(&v[1], &v[n] + 1, v[0]), v[0].w = 0, h.clear();
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
  }
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    v[p[i]].e[x] = i;
  }
  for (int i = 1; i <= m; i++) {
    cin >> a[i];
    s[i][0] = s[i - 1][0] * kBase[0] + a[i];
    s[i][1] = s[i - 1][1] * kBase[1] + a[i];
  }
}

void CalcFail() {
  h[{0, 0}] = 0, q[1] = 0;
  for (int s = 1, t = 1; s <= t; s++) {
    int x = q[s], y, z;
    for (auto i : v[x].e) {
      y = i.second, v[y].d = v[x].d + 1, v[y].f[0] = x, q[++t] = y;
      v[y].hash[0] = v[x].hash[0] * kBase[0] + i.first;
      v[y].hash[1] = v[x].hash[1] * kBase[1] + i.first;
      h[{v[y].hash[0], v[y].hash[1]}] = y;
      for (int j = 1; j < kMaxL; j++) {
        v[y].f[j] = v[v[y].f[j - 1]].f[j - 1];
      }
      if (x) {
        for (z = v[x].fail; z && !v[z].e.count(i.first); z = v[z].fail) {
        }
        if (v[z].e.count(i.first)) {
          v[y].fail = v[z].e[i.first];
        }
      }
    }
  }
}

int Fail(int &x) {
  int l = 1, r = m;
  while (l <= r) {
    int mid = l + r >> 1;
    if (h.count({v[x].hash[0] * pw[mid][0] + s[mid][0], v[x].hash[1] * pw[mid][1] + s[mid][1]})) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  x = h[{v[x].hash[0] * pw[r][0] + s[r][0], v[x].hash[1] * pw[r][1] + s[r][1]}];
  swap(x, r);
  return v[r].fail;
}

int Father(int x, int d) {
  for (int i = kMaxL - 1; i >= 0; i--) {
    if (d & 1 << i) {
      x = v[x].f[i];
    }
  }
  return x;
}

void Mark(int x, LL k) { w[1] -= k, w[x + 1] += k; }

void Add1(int x, LL k) { ans[1] += k, ans[2] -= k, ans[x + 1] -= k, ans[x + 2] += k; }

void Add2(int x, LL k, LL w) { Add1(x, k * w), ans[1] += w, ans[x + 1] -= w, ans[x + 1] -= x * w, ans[x + 2] += x * w; }

void CalcW() {
  for (int o = n + 1; o >= 2; o--) {
    int i = q[o], d = i, j = Fail(d);
    if (v[j].d >= d) {
      int t = Father(j, d);
      v[t].w += v[i].w, Add1(d, v[i].w * (v[i].d - v[t].d));
    } else {
      v[0].w += v[i].w, Mark(d, v[i].w), Add2(d, v[i].d, v[i].w);
    }
  }
  w[1] += v[0].w;
  for (int i = 1; i <= m; i++) {
    w[i] += w[i - 1];
  }
  for (int o = 0; o < 2; o++) {
    for (int i = 1; i <= m; i++) {
      ans[i] += ans[i - 1];
    }
  }
}

void CalcAns() {
  for (int i = 0, j = 1; j <= m; j++) {
    for (; i && !v[i].e.count(a[j]); i = v[i].fail) {
    }
    if (v[i].e.count(a[j])) {
      i = v[i].e[a[j]], ans[j] += w[j] * v[i].d;
    }
    cout << ans[j] << " \n"[j == m];
    w[j] = ans[j] = 0;
  }
  w[m + 1] = w[m + 2] = ans[m + 1] = ans[m + 2] = 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  pw[0][0] = pw[0][1] = 1;
  for (int i = 1; i < kMaxN; i++) {
    pw[i][0] = pw[i - 1][0] * kBase[0];
    pw[i][1] = pw[i - 1][1] * kBase[1];
  }
  cin >> t;
  while (t--) {
    Init(), CalcFail(), CalcW(), CalcAns();
  }
  return 0;
}

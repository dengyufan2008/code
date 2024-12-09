#include <fstream>
#include <functional>
#include <unordered_map>
#define LL long long
// from boost (functional/hash):
// see http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html template
template <typename T>
inline void hash_combine(std::size_t &seed, const T &val) {
  seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
// auxiliary generic functions to create a hash value using a seed
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

using namespace std;

ifstream cin("anfang.in");
ofstream cout("anfang.out");

const int kMaxN = 1e5 + 1, kMaxM = 9e6 + 1, kMaxV = 60;
struct V {
  int c, s[2];
  bool b1, b2;
} v[kMaxM];
int n, m, s, t;
LL k, a[kMaxN];
pair<int, LL> q[kMaxN];
unordered_map<int, int> ans1;
unordered_map<pair<int, int>, int, pair_hash> ans2;

void Update(int &x, int y) { x = max(x, y); }

void Add(int &p, LL w, int c, int d) {
  !p && (p = ++t), v[p].c += c, v[p].b1 = v[p].b2 = 0;
  if (d >= 0) {
    Add(v[p].s[w >> d & 1], w, c, d - 1);
  }
}

int Calc2(int p, int q, int d);

int Calc1(int p, int d) {
  if (d < 0) {
    return v[p].c;
  } else if (!p) {
    return 0;
  } else if (v[p].b1 && ans1.count(p)) {
    return ans1[p];
  }
  v[p].b1 = 1;
  int ans = 0;
  if (k >> d & 1) {
    ans = Calc2(v[p].s[0], v[p].s[1], d - 1);
  } else {
    ans = max(Calc1(v[p].s[0], d - 1), Calc1(v[p].s[1], d - 1));
  }
  return ans1[p] = ans;
}

int Calc2(int p, int q, int d) {
  if (d < 0 || !p || !q) {
    return v[p].c + v[q].c;
  } else if (v[p].b2 && v[q].b2 && ans2.count({p, q})) {
    return ans2[{p, q}];
  }
  v[p].b2 = v[q].b2 = 1;
  int ans = max(v[p].c, v[q].c);
  if (k >> d & 1) {
    Update(ans, Calc2(v[p].s[0], v[q].s[1], d - 1) + Calc2(v[p].s[1], v[q].s[0], d - 1));
  } else {
    Update(ans, Calc2(v[p].s[0], v[q].s[0], d - 1));
    Update(ans, Calc2(v[p].s[1], v[q].s[1], d - 1));
  }
  return ans2[{p, q}] = ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> k, k--;
  if (k < 0) {
    for (int i = 0; i <= m; i++) {
      cout << 1 << '\n';
    }
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i], Add(s, a[i], 1, kMaxV - 1);
  }
  for (int i = 1; i <= m; i++) {
    cin >> q[i].first >> q[i].second;
    Add(s, q[i].second, 0, kMaxV - 1);
  }
  cout << Calc1(s, kMaxV - 1) << '\n';
  for (int i = 1; i <= m; i++) {
    LL x = q[i].first, y = q[i].second;
    Add(s, a[x], -1, kMaxV - 1);
    Add(s, y, 1, kMaxV - 1);
    cout << Calc1(s, kMaxV - 1) << '\n';
    a[x] = y;
  }
  return 0;
}

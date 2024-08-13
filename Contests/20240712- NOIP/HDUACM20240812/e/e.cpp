#include <functional>
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

#include <fstream>
#include <unordered_map>
#define LL long long

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

int t;
LL l, r, k;
unordered_map<pair<LL, LL>, LL, pair_hash> s;

LL F(LL n, LL k) {
  if (n == 0 || k < 0) {
    return 0;
  } else if (s.count({n, k})) {
    return s[{n, k}];
  }
  return s[{n, k}] = F(n - 1 >> 1, k - 1) + F(n >> 1, k) + 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> l >> r >> k;
    cout << F(r - l + 1, k) << '\n';
  }
  return 0;
}

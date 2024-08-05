#include <algorithm>
#include <fstream>
#include <set>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");

const int kMaxN = 3e5 + 1;
const LL kBase1 = 100003, kMod1 = 998244353, kInv1 = 758712824;
const LL kBase2 = 100019, kMod2 = 1e9 + 7, kInv2 = 371229469;
struct H {
  LL hash1, hash2;
  H() : hash1(0), hash2(0) {}
  H(LL _hash1, LL _hash2) : hash1(_hash1), hash2(_hash2) {}
  const bool operator<(const H x) const {
    return hash1 < x.hash1 || hash1 == x.hash1 && hash2 < x.hash2;
  }
  H operator+(H x) {
    return {(hash1 + x.hash1) % kMod1, (hash2 + x.hash2) % kMod2};
  }
  H operator*(H x) {
    return {hash1 * x.hash1 % kMod1, hash2 * x.hash2 % kMod2};
  }
};
struct W1 {
  LL mul, add, inv;
  W1 operator*(W1 x) {
    return {mul * x.mul % kMod1, (add * x.mul + x.add) % kMod1, inv * x.inv % kMod1};
  }
};
struct W2 {
  LL mul, add, inv;
  W2 operator*(W2 x) {
    return {mul * x.mul % kMod2, (add * x.mul + x.add) % kMod2, inv * x.inv % kMod2};
  }
};
int t, n, m;
pair<int, int> a[kMaxN], b[kMaxN];
pair<W1, W2> w[kMaxN];
set<H> s[kMaxN];
vector<H> v;
vector<int> ans;

void S(int x, LL w1, LL w2, LL s1, LL s2) {
  if (!b[x].first && !b[x].second) {
    return v.push_back({s1, s2});
  }
  w1 = w1 * kBase1 % kMod1, w2 = w2 * kBase2 % kMod2;
  if (b[x].first) {
    S(b[x].first, w1, w2, (s1 - w1 + kMod1) % kMod1, (s2 - w2 + kMod2) % kMod2);
  }
  if (b[x].second) {
    S(b[x].second, w1, w2, (s1 + w1) % kMod1, (s2 + w2) % kMod2);
  }
}

void T(int x) {
  int l = a[x].first, r = a[x].second;
  if (l && r) {
    T(l), T(r);
    if (s[l].size() < s[r].size()) {
      s[x].swap(s[r]);
      w[x].first = w[r].first * (W1){kBase1, 1, kInv1};
      w[x].second = w[r].second * (W2){kBase2, 1, kInv2};
      for (H i : s[l]) {
        i = i * (H){w[l].first.mul, w[l].second.mul} + (H){w[l].first.add, w[l].second.add};
        i = i * (H){kBase1, kBase2} + (H){kMod1 - 1, kMod2 - 1};
        i = (i + (H){kMod1 - w[x].first.add, kMod2 - w[x].second.add}) * (H){w[x].first.inv, w[x].second.inv};
        s[x].insert(i);
      }
      s[l].clear();
    } else {
      s[x].swap(s[l]);
      w[x].first = w[l].first * (W1){kBase1, kMod1 - 1, kInv1};
      w[x].second = w[l].second * (W2){kBase2, kMod2 - 1, kInv2};
      for (H i : s[r]) {
        i = i * (H){w[r].first.mul, w[r].second.mul} + (H){w[r].first.add, w[r].second.add};
        i = i * (H){kBase1, kBase2} + (H){1, 1};
        i = (i + (H){kMod1 - w[x].first.add, kMod2 - w[x].second.add}) * (H){w[x].first.inv, w[x].second.inv};
        s[x].insert(i);
      }
      s[r].clear();
    }
  } else if (l) {
    T(l), s[x].swap(s[l]);
    w[x].first = w[l].first * (W1){kBase1, kMod1 - 1, kInv1};
    w[x].second = w[l].second * (W2){kBase2, kMod2 - 1, kInv2};
  } else if (r) {
    T(r), s[x].swap(s[r]);
    w[x].first = w[r].first * (W1){kBase1, 1, kInv1};
    w[x].second = w[r].second * (W2){kBase2, 1, kInv2};
  }
  s[x].insert({(kMod1 - w[x].first.add) * w[x].first.inv % kMod1,
               (kMod2 - w[x].second.add) * w[x].second.inv % kMod2});
  bool o = 1;
  for (H i : v) {
    i = (i + (H){kMod1 - w[x].first.add, kMod2 - w[x].second.add}) * (H){w[x].first.inv, w[x].second.inv};
    if (!s[x].count(i)) {
      o = 0;
    }
  }
  o ? ans.push_back(x) : void();
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    v.clear(), ans.clear();
    for (int i = 1; i <= n; i++) {
      w[i] = {{1, 0, 1}, {1, 0, 1}}, s[i].clear();
    }
    for (int i = 1; i <= n; i++) {
      cin >> a[i].first >> a[i].second;
      a[i].first && (a[i].first++);
      a[i].second && (a[i].second++);
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
      cin >> b[i].first >> b[i].second;
      b[i].first && (b[i].first++);
      b[i].second && (b[i].second++);
    }
    S(1, kInv1, kInv2, 0, 0), T(1);
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int i : ans) {
      cout << i - 1 << ' ';
    }
    cout << '\n';
  }
  return 0;
}

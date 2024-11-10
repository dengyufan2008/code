#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const int kMaxN = 5e5 + 1, kMaxM = 801;
struct E {
  int a, b, w;
} e[kMaxN];
int n, m, c[kMaxM][kMaxM];
LL f[kMaxM][kMaxM];
vector<int> l1, l2, p1, p2;
unordered_map<int, int> s1, s2;
vector<pair<LL, int>> ans;

int Gcd(int x, int y) { return y ? Gcd(y, x % y) : x; }

void Init(int x, vector<int> &l, unordered_map<int, int> &s, vector<int> &p) {
  for (int i = 1; i * i <= x; i++) {
    if (!(x % i)) {
      l.push_back(i);
      if (i * i < x) {
        l.push_back(x / i);
      }
    }
  }
  sort(l.begin(), l.end());
  for (int i = 0; i < l.size(); i++) {
    s[l[i]] = i;
  }
  for (int i = 2; i * i <= x; i++) {
    if (!(x % i)) {
      p.push_back(i);
      for (; !(x % i); x /= i) {
      }
    }
  }
  if (x > 1) {
    p.push_back(x);
  }
}

template <typename T>
void Suf(T a[kMaxM][kMaxM]) {
  for (int i : p1) {
    for (int j : l1) {
      if (j % i) {
        LL k = j;
        for (; !(e[1].a % k); k *= i) {
        }
        for (k /= i; k > j; k /= i) {
          int x = s1[k / i], y = s1[k];
          for (int l = 0; l < l2.size(); l++) {
            a[x][l] += a[y][l];
          }
        }
      }
    }
  }
  for (int i : p2) {
    for (int j : l2) {
      if (j % i) {
        LL k = j;
        for (; !(e[1].b % k); k *= i) {
        }
        for (k /= i; k > j; k /= i) {
          int x = s2[k / i], y = s2[k];
          for (int l = 0; l < l1.size(); l++) {
            a[l][x] += a[l][y];
          }
        }
      }
    }
  }
}

void CalcAns(int w) {
  l1.clear(), s1.clear(), p1.clear();
  l2.clear(), s2.clear(), p2.clear();
  Init(e[1].a, l1, s1, p1), Init(e[1].b, l2, s2, p2);
  for (int i = 0; i < l1.size(); i++) {
    for (int j = 0; j < l2.size(); j++) {
      c[i][j] = f[i][j] = 0;
    }
  }
  for (int i = 2; i <= n; i++) {
    int gcd = Gcd(e[i].a, e[i].b);
    int x1 = s1[Gcd(e[i].a, e[1].a)], x2 = s2[Gcd(e[i].b, e[1].b)];
    int y1 = s1[Gcd(e[i].b, e[1].a)], y2 = s2[Gcd(e[i].a, e[1].b)];
    int z1 = s1[Gcd(gcd, e[1].a)], z2 = s2[Gcd(gcd, e[1].b)];
    c[x1][x2]++, c[y1][y2]++, c[z1][z2]--;
    f[y1][y2] += e[i].w, f[z1][z2] -= e[i].w;
  }
  Suf(c), Suf(f);
  for (int i = 0; i < l1.size(); i++) {
    for (int j = 0; j < l2.size(); j++) {
      if (c[i][j] == n - 1) {
        ans.push_back({f[i][j] + w, l1[i] + l2[j]});
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].a;
  }
  for (int i = 1; i <= n; i++) {
    cin >> e[i].b;
  }
  for (int i = 1; i <= n; i++) {
    cin >> e[i].w;
  }
  CalcAns(0), swap(e[1].a, e[1].b), CalcAns(e[1].w);
  sort(ans.begin(), ans.end());
  for (auto &i : ans) {
    static int w = 0;
    w = i.second = max(w, i.second);
  }
  for (int i = 1; i <= m; i++) {
    static LL x;
    cin >> x;
    auto p = lower_bound(ans.begin(), ans.end(), make_pair(x + 1, 0));
    cout << (--p)->second << " \n"[i == m];
  }
  return 0;
}

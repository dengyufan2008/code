#include <fstream>
#include <map>
#include <set>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

LL t, n, m;
bool invalid;
set<LL> s0, s1;
map<LL, LL> s2;

void Insert(LL x, LL y) {
  if (s2.count(y)) {
    if (s2[y] != x) {
      invalid = 1;
    }
  } else {
    auto p = s2.lower_bound(y);
    if (p != s2.end() && (abs(p->second - x) > p->first - y || (p->second - x + p->first - y & 1))) {
      invalid = 1;
    } else if (p != s2.begin()) {
      p--;
      if (abs(x - p->second) > y - p->first || (x - p->second + y - p->first & 1)) {
        invalid = 1;
      } else {
        s2[y] = x;
      }
    } else {
      s2[y] = x;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    invalid = 0, s0.clear(), s1.clear(), s2.clear(), s0.insert(0);
    cin >> n >> m;
    for (LL i = 1, o, x, y; i <= m; i++) {
      cin >> o;
      if (o == 0) {
        cin >> x >> y;
        if (!invalid) {
          if (x == 1) {
            if (s2.empty() || s2.begin()->first > y) {
              y & 1 ? s1.insert(y) : s0.insert(y);
            } else {
              Insert(x, y);
            }
          } else {
            while (!s0.empty() && *(--s0.end()) >= y) {
              Insert(1, *(--s0.end())), s0.erase(--s0.end());
            }
            while (!s1.empty() && *(--s1.end()) >= y) {
              Insert(1, *(--s1.end())), s1.erase(--s1.end());
            }
            Insert(x, y);
          }
        }
      } else if (o == 1) {
        if (invalid) {
          cout << "bad\n";
        } else if (!s0.empty() && !s1.empty()) {
          LL p = min(*(--s0.end()), *(--s1.end())) + 1;
          if (!s2.empty() && ((p + 1) & 1) != ((s2.begin()->first + s2.begin()->second) & 1)) {
            p = max(*(--s0.end()), *(--s1.end()));
            if (((p + 1) & 1) != ((s2.begin()->first + s2.begin()->second) & 1)) {
              p++;
            }
          }
          if (!s2.empty() && (s2.begin()->first - max(p, max(*(--s0.end()), *(--s1.end())))) < (s2.begin()->second - 1)) {
            cout << "bad\n";
          } else {
            cout << p << '\n';
          }
        } else if (!s0.empty()) {
          if (!s2.empty() && ((s2.begin()->first + s2.begin()->second) & 1) != 1) {
            LL p = *(--s0.end()) + 1;
            if (s2.begin()->first - p < s2.begin()->second - 1) {
              cout << "bad\n";
            } else {
              cout << p << '\n';
            }
          } else {
            if (!s2.empty() && s2.begin()->first - *(--s0.end()) < s2.begin()->second - 1) {
              cout << "bad\n";
            } else {
              cout << 0 << '\n';
            }
          }
        } else if (!s1.empty()) {
          if (!s2.empty() && ((s2.begin()->first + s2.begin()->second) & 1) != 0) {
            LL p = *(--s1.end()) + 1;
            if (s2.begin()->first - p < s2.begin()->second - 1) {
              cout << "bad\n";
            } else {
              cout << p << '\n';
            }
          } else {
            if (!s2.empty() && s2.begin()->first - *(--s1.end()) < s2.begin()->second - 1) {
              cout << "bad\n";
            } else {
              cout << 1 << '\n';
            }
          }
        } else {
          LL p = (s2.begin()->first + s2.begin()->second) & 1 ^ 1;
          if (s2.begin()->first - p < s2.begin()->second - 1) {
            cout << "bad\n";
          } else {
            cout << p << '\n';
          }
        }
      } else {
        if (invalid) {
          cout << "bad\n";
        } else if (s2.empty()) {
          cout << "inf\n";
        } else {
          LL p = s2.begin()->first - s2.begin()->second + 1;
          if (p < 0 || !s0.empty() && p < *(--s0.end()) || !s1.empty() && p < *(--s1.end())) {
            cout << "bad\n";
          } else {
            cout << p << '\n';
          }
        }
      }
    }
  }
  return 0;
}

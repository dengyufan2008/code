#include <iostream>
#include <vector>

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const int kMaxN = 51;
struct V {
  int f, d;
  vector<int> i, o;
} v[kMaxN];
int n, a, b, ans0, ans1, ans2;
char ch[kMaxN][kMaxN];

int GetRoot(int x) {
  return v[x].f == x ? x : v[x].f = GetRoot(v[x].f);
}

bool W(int x, int y, int av, int bv) {
  return GetRoot(x) != GetRoot(y) || av == bv;
}

bool P(int x) {
  x = GetRoot(x);
  for (int i : v[x].i) {
    if (v[i].d <= v[x].d) {
      return 0;
    }
  }
  for (int i : v[x].o) {
    if (v[i].d >= v[x].d) {
      return 0;
    }
  }
  return 1;
}

bool C(int x, int y, int av, int bv, int cv, int dv) {
  for (int i = 1; i <= n; i++) {
    if (i == GetRoot(i)) {
      if (v[i].i.empty()) {
        v[i].d = 3;
      } else if (v[i].o.empty()) {
        v[i].d = 1;
      } else {
        v[i].d = 2;
      }
    }
  }
  v[GetRoot(a)].d = av, v[GetRoot(b)].d = bv;
  v[GetRoot(x)].d = cv, v[GetRoot(y)].d = dv;
  return W(a, b, av, bv) && W(a, x, av, cv) &&
         W(a, y, av, dv) && W(b, x, bv, cv) &&
         W(b, y, bv, dv) && W(x, y, cv, dv) &&
         P(a) && P(b) && P(x) && P(y);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    v[i].f = i;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> ch[i][j];
      if (ch[i][j] == '=' && GetRoot(i) != GetRoot(j)) {
        v[GetRoot(i)].f = GetRoot(j);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (ch[i][j] == '+') {
        v[GetRoot(i)].o.push_back(GetRoot(j));
        v[GetRoot(j)].i.push_back(GetRoot(i));
      }
    }
  }
  cin >> a >> b;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (a != i && a != j && b != i && b != j) {
        bool b0 = 1, b1 = 1, b2 = 1;
        for (int av = 1; av <= 3; av++) {
          for (int bv = 1; bv <= 3; bv++) {
            for (int cv = 1; cv <= 3; cv++) {
              for (int dv = 1; dv <= 3; dv++) {
                if (C(i, j, av, bv, cv, dv)) {
                  if (av + bv > cv + dv) {
                    b1 = b2 = 0;
                  } else if (av + bv == cv + dv) {
                    b0 = b2 = 0;
                  } else {
                    b0 = b1 = 0;
                  }
                }
              }
            }
          }
        }
        ans0 += b0 & !b1 & !b2, ans1 += !b0 & b1 & !b2, ans2 += !b0 & !b1 & b2;
      }
    }
  }
  cout << ans0 << '\n'
       << ans1 << '\n'
       << ans2 << '\n';
  return 0;
}

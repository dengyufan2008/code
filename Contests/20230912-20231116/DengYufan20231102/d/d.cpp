#include <iostream>

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const int kMaxN = 41;
int n, a[kMaxN], d[kMaxN], ans[kMaxN * kMaxN];
bool b[kMaxN], p[kMaxN];

bool C(int l, int r) {
  fill(&p[l], &p[r] + 1, 0);
  for (int i = l; i <= r; i++) {
    p[d[i]] = 1;
  }
  for (int i = l; i <= r; i++) {
    if (!p[i]) {
      return 0;
    }
  }
  return 1;
}

void S(int x) {
  if (x > n) {
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= a[i]; j++) {
        if (C(i, j)) {
          return;
        }
      }
    }
    int c = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = i; j <= n; j++) {
        c += C(i, j);
      }
    }
    ans[c]++;
    return;
  }
  for (int i = 1; i <= n; i++) {
    if (!b[i]) {
      b[i] = 1, d[x] = i;
      S(x + 1);
      b[i] = 0;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  S(1);
  for (int i = 1; i <= n * (n + 1) / 2; i++) {
    cout << ans[i] << ' ';
  }
  return 0;
}

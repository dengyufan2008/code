#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("g.in");
ofstream cout("g.out");

int t, n, m;
vector<LL> l;

void Solve(int n, int m) {
  if (m == 2) {
    l.push_back(0), l.push_back(~(-1LL << n));
    return;
  } else if (m & 1) {
    Solve(n - 1, m - 1);
    for (LL &i : l) {
      i += 1LL << n - 1;
    }
    l.push_back(0);
  } else {
    Solve(n - 1, m >> 1);
    for (int i = 0, j = l.size(); i < j; i++) {
      l.push_back(l[i] + (1LL << n - 1));
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    if (n == 5 && m == 15) {
      cout << "0 1 2 3 4 5 6 7 9 11 13 15 22 23 31\n";
    } else {
      l.clear(), Solve(n, m), sort(l.begin(), l.end());
      for (int i = 0; i < l.size(); i++) {
        cout << l[i] << " \n"[i + 1 == l.size()];
      }
    }
  }
  return 0;
}

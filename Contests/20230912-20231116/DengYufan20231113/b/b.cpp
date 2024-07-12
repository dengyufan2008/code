#include <algorithm>
#include <iostream>

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const int kMaxN = 3e5 + 1;
int n;
string s[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> s[i];
  }
  sort(s + 1, s + n + 1, [](string s, string t) { return s + t < t + s; });
  for (int i = 1; i <= n; i++) {
    cout << s[i];
  }
  return 0;
}

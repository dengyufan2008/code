#include <iostream>
#include <vector>

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

int ans;
string s, t;
vector<int> p[26];

int Find(int x, int y) {
  int l = 0, r = p[x].size() - 1;
  while (l <= r) {
    int mid = l + r >> 1;
    if (p[x][mid] <= y) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return l;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s >> t;
  for (int i = 0; i < s.size(); i++) {
    p[s[i] - 'a'].push_back(i);
  }
  for (char i : t) {
    if (p[i - 'a'].empty()) {
      cout << -1;
      return 0;
    }
  }
  ans++;
  for (int i = 0, l = -1; i < t.size();) {
    int c = Find(t[i] - 'a', l);
    if (c < p[t[i] - 'a'].size()) {
      l = p[t[i] - 'a'][c], i++;
    } else {
      l = -1, ans++;
    }
  }
  cout << ans;
  return 0;
}

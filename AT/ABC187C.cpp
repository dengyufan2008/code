#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n;
string tmp;
vector<string> v;
set<string> s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> tmp;
    if (tmp[0] == '!') {
      s.insert(tmp.substr(1));
    } else {
      v.push_back(tmp);
    }
  }
  for (int i = 0; i < v.size(); i++) {
    if (s.find(v[i]) != s.end()) {
      cout << v[i] << endl;
      return 0;
    }
  }
  cout << "satisfiable\n";
  return 0;
}

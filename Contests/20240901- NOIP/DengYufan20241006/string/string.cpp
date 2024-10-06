#include <fstream>
#define LL long long

using namespace std;

ifstream cin("string.in");
ofstream cout("string.out");

int n, d[26];
LL ans;
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> s, ans = n--;
  for (int i = n; i >= 0; i--) {
    ans += n - i - d[s[i] - 'a']++;
  }
  cout << ans << '\n';
  return 0;
}

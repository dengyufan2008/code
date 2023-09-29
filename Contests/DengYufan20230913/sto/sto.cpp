#include <fstream>
#define LL long long

using namespace std;

ifstream cin("sto.in");
ofstream cout("sto.out");

LL t, n;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    cout << (n % 6 ? "NO\n" : "YES\n");
  }
  return 0;
}

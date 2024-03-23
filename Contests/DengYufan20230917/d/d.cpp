#include <fstream>

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 2e5 + 1;
int n, q;
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> q >> s;
  s = '~' + s;
  for (int i = 1, l1, r1, l2, r2; i <= q; i++) {
    cin >> l1 >> r1 >> l2 >> r2;
  }
  return 0;
}

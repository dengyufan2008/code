#include <fstream>

using namespace std;

ifstream cin("village.in");
ofstream cout("village.out");

int n, m1, m2;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m1 >> m2;
  for (int i = 1; i <= m2; i++) {
    cout << 0 << '\n';
  }
  return 0;
}

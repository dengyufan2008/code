#include <fstream>

using namespace std;

ifstream cin("silksong.in");
ofstream cout("silksong.out");

const int kMaxN = 1 << 16;
int n, x, y;
pair<int, int> a[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> x >> y;
  for (int i = 0; i < 1 << n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  cout << "SILKSONG\n";
  return 0;
}

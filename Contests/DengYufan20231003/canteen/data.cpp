#include <chrono>
#include <fstream>
#include <random>

using namespace std;

ifstream cin("CON");
ofstream cout("canteen.in");

const int kN = 10, kM = 10, kV = 10;
bool b[kV][kV];
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kN << ' ' << kM << ' ' << kV - 1 << '\n';
  cout << "0 0 0 " << kV - 1 << '\n';
  cout << "0 0 " << kV - 1 << " 0\n";
  cout << "0 " << kV - 1 << ' ' << kV - 1 << ' ' << kV - 1 << '\n';
  cout << kV - 1 << " 0 " << kV - 1 << ' ' << kV - 1 << '\n';
  for (int i = 5; i <= kN; i++) {
    if (Rand() % 2) {
      int x = Rand() % kV, y1 = Rand() % kV, y2 = Rand() % kV;
      cout << x << ' ' << min(y1, y2) << ' ' << x << ' ' << max(y1, y2) << '\n';
      for (int i = min(y1, y2); i <= max(y1, y2); i++) {
        b[x][i] = 1;
      }
    } else {
      int x1 = Rand() % kV, x2 = Rand() % kV, y = Rand() % kV;
      cout << min(x1, x2) << ' ' << y << ' ' << max(x1, x2) << ' ' << y << '\n';
      for (int i = min(x1, x2); i <= max(x1, x2); i++) {
        b[i][y] = 1;
      }
    }
  }
  for (int i = 1; i <= kM; i++) {
    int x = Rand() % (kV - 2) + 1, y = Rand() % (kV - 2) + 1;
    while (b[x][y]) {
      x = Rand() % (kV - 2) + 1, y = Rand() % (kV - 2) + 1;
    }
    cout << x << ' ' << y << '\n';
  }
  return 0;
}

#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

ifstream cin("CON");
ofstream cout("c.in");

const long double kPi = acos(-1.0), kR = 5e8;
const int kN = 1e6;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kN << '\n';
  for (int i = 0; i < kN; i++) {
    cout << fixed << setprecision(0) << kR + cos(kPi / (long double)kN * (long double)i) * kR << ' ' << kR + sin(kPi / (long double)kN * (long double)i) * kR << '\n';
  }
  return 0;
}

#include <chrono>
#include <fstream>
#include <random>

using namespace std;

ifstream cin("CON");
ofstream cout("dseq.in");

const int kMaxN = 5000, kMaxM = 5000, kMaxV1 = 4000, kMaxV2 = 1e9;
const bool kType = 0;  // operator 1
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cout << kMaxN << ' ' << kMaxM << '\n';
  for (int i = 1; i <= kMaxN; i++) {
    cout << Rand() % kMaxV2 + 1 << " \n"[i == kMaxN];
  }
  for (int i = 1; i <= kMaxM; i++) {
    int l = Rand() % kMaxN + 1, r = Rand() % kMaxN + 1;
    l > r ? swap(l, r) : (void)0;
    if (kType && !(Rand() % 3)) {
      cout << 1 << ' ' << l << ' ' << r << ' ' << Rand() % kMaxV1 + 1 << '\n';
    } else if (!(Rand() % 2)) {
      cout << 2 << ' ' << l << ' ' << r << ' ' << Rand() % kMaxV2 + 1 << '\n';
    } else {
      cout << 3 << ' ' << l << ' ' << r << '\n';
    }
  }
  return 0;
}

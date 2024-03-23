#include <chrono>
#include <fstream>
#include <random>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("CON");
ofstream cout("d.in");

const LL kN = 12000, kQ = 10000, kInf = 1e9;
const string kS[8] = {"or", "and", "xor", "ori", "andi", "xori", "repeat", "end"},
             kT[4] = {"ax", "bx", "cx", "dx"};
LL c, t, a[kN + 1], b[kN + 1];
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (LL i = 1; i <= kN; i++) {
    a[i] = Rand() % 6;
  }
  c = Rand() % kN + 1, c -= c & 1;
  for (LL i = 1; i <= c; i++) {
    LL x = Rand() % kN + 1;
    while (a[x] >= 6) {
      x = Rand() % kN + 1;
    }
    a[x] = 6;
  }
  vector<pair<LL, LL>> w;
  for (LL i = 1, j = 0, k = 0; i <= kN; i++) {
    if (a[i] == 6) {
      if ((j + 1 << 1) <= c && (j == k || Rand() & 1)) {
        w.push_back({i, t}), j++;
      } else {
        auto x = w.back();
        b[x.first] = b[i] = Rand() % 254 + 2;
        if (t != kInf && t + (t - x.second) * (b[i] - 1) > kInf) {
          t = kInf;
        } else {
          t += (t - x.second) * (b[i] - 1);
        }
        a[i] = 7, k++;
        w.pop_back();
      }
    } else if (t != kInf) {
      t++;
    }
  }
  t = min(t, kInf);
  cout << kN << ' ' << kQ << '\n';
  for (LL i = 1; i <= kN; i++) {
    cout << kS[a[i]] << ' ';
    if (a[i] < 3) {
      cout << kT[Rand() % 4] << ' ' << kT[Rand() % 4] << '\n';
    } else if (a[i] < 6) {
      cout << kT[Rand() % 4] << ' ' << Rand() % 256 << '\n';
    } else if (a[i] < 7) {
      cout << b[i] << '\n';
    } else {
      cout << '\n';
    }
  }
  for (LL i = 1; i <= kQ; i++) {
    cout << (LL)(Rand() >> 1) % kInf % (t + 1) << ' ' << Rand() % 256 << ' ' << Rand() % 256 << ' ' << Rand() % 256 << ' ' << Rand() % 256 << '\n';
  }
  return 0;
}

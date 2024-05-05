#include <fstream>
#define ULL unsigned long long

using namespace std;

ifstream cin("string.in");
ofstream cout("string.out");

const int kMaxN = 10001;
int n, a[kMaxN], d[kMaxN];
class S {
  static const int kMaxM = (1 << 25) - 1;
  int c;
  ULL d[kMaxM + 1];

 public:
  void Insert(ULL w) {
    int i = ((w << 17) ^ (w >> 24) ^ (w << 9)) & kMaxM;
    for (; d[i]; i = i + 1 & kMaxM) {
      if (d[i] == w) {
        return;
      }
    }
    c++, d[i] = w;
  }

  int Size() { return c; }
} s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    ULL w = 0;
    fill(&d[1], &d[n] + 1, 0);
    for (int j = i, k = 0; j <= n; j++) {
      !d[a[j]] && (d[a[j]] = ++k);
      w = ((w << 7) ^ (w << 1) ^ (w >> 5)) + d[a[j]];
      s.Insert(w);
    }
  }
  cout << s.Size() << '\n';
  return 0;
}

#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int d[3];
char ch;
pair<int, int> a[4];

int main() {
  for (int i = 0; i < 4; i++) {
    cin >> ch >> a[i].first >> ch >> a[i].second >> ch;
  }
  for (int i = 0; i < 3; i++) {
    int c = (a[(i + 1) % 3].first - a[i].first) * (a[3].second - a[i].second) - (a[3].first - a[i].first) * (a[(i + 1) % 3].second - a[i].second);
    d[c ? (c < 0 ? 0 : 2) : 1]++;
  }
  if (d[1] == 2) {
    cout << 4;
  } else if (d[1] == 1 && (d[0] == 2 || !d[0])) {
    cout << 3;
  } else {
    cout << (d[0] == 3 || d[2] == 3 ? 1 : 2);
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

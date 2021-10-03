#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n;
pair<int, int> a[102];

int main() {
  // freopen("delivery.in", "r", stdin);
  // freopen("delivery.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  a[++n] = a[1];
  for (int i = 1; i <= n; i++) {  // from i to i + 1
    
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

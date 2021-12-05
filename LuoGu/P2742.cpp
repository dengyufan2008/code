#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n;
pair<int, int> a[100001];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

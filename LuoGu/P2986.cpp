#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int c;
  vector<pair<int, int>> e;
} v[100001];
int n;

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].c;
  }
  for (int i = 1, x, y, z; i < n; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
  
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  vector<int> e;
} v[1000000];
int n, m, d;

int main() {
  // freopen("dfsshu.in", "r", stdin);
  // freopen("dfsshu.out", "w", stdout);
  cin >> n >> m >> d;
  for (int i = 0, u; i < n; i++) {
    cin >> u;
    v[i].e.push_back(u), v[u].e.push_back(i);
  }
  
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}

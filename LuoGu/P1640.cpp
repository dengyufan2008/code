#include <iostream>
#include <vector>
#define LL long long

using namespace std;

int n, k, b[1000001], v[1000001], t[10001];
vector<int> l[10001];

bool T(int x) {
	if (b[x] != k) {
		b[x] = k;
		for (int i : l[x]) {
			if (!v[i] || T(v[i])) {
        t[v[i]]--, t[v[i] = x]++;
				return 1;
			}
		}
	}
	return 0;
}

int main() {
	cin >> n;
	for (int i = 1, x, y; i <= n; i++) {
		cin >> x >> y;
    l[x].push_back(i), l[y].push_back(i);
	}
	for (int i = 1; i <= 10000; i++) {
		k++, T(i);
	}
	for (int i = 1; i <= 10000; i++) {
		if (!t[i]) {
			cout << i - 1;
			return 0;
		}
	}
  cout << 10000;
  return 0;
}

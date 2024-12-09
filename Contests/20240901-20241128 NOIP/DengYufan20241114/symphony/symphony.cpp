#include <fstream>
#include <vector>

using namespace std;

ifstream cin("symphony.in");
ofstream cout("symphony.out");

const int kMaxN = 128;
int n, high[kMaxN];
vector<pair<int, int>> q1, q2, step;
vector<vector<pair<int, int>>> ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  high[1] = 1;
  for (int i = 2; i < kMaxN; i++) {
    high[i] = high[i >> 1] << 1;
  }
  cin >> n;
  for (int i = 0; i < n; i++) {
    q1.emplace_back(i, i);
  }
  for (; q1.size() > 1;) {
    static vector<pair<int, int>> o;

    for (int i = 1; i < q1.size(); i += 2) {
      o.emplace_back(q1[i - 1].first, q1[i].second);
    }
    if (q1.size() & 1) {
      o.emplace_back(q1.back().first, q1.back().second);
    }
    q1.swap(o), o.clear();

    for (auto i : q1) {
      if (i.first < i.second) {
        int mid = i.first + high[i.second - i.first] - 1;
        for (int j = mid + 1; j <= i.second; j++) {
          step.emplace_back(mid + mid + 1 - j, j);
        }
        if (i.first < mid) {
          o.emplace_back(i.first, mid);
        }
        if (mid + 1 < i.second) {
          o.emplace_back(mid + 1, i.second);
        }
      }
    }
    q2.swap(o), o.clear();
    if (!step.empty()) {
      ans.emplace_back(step), step.clear();
    }

    for (; !q2.empty();) {
      for (auto i : q2) {
        int mid = i.first + high[i.second - i.first] - 1;
        for (int j = mid + 1; j <= i.second; j++) {
          step.emplace_back(j - mid - 1 + i.first, j);
        }
        if (i.first < mid) {
          o.emplace_back(i.first, mid);
        }
        if (mid + 1 < i.second) {
          o.emplace_back(mid + 1, i.second);
        }
      }
      q2.swap(o), o.clear();
      if (!step.empty()) {
        ans.emplace_back(step), step.clear();
      }
    }
  }

  cout << ans.size() << '\n';
  for (auto &i : ans) {
    for (auto &j : i) {
      if (j.first < n && j.second < n) {
        cout << "CMPSWP R" << j.first + 1 << " R" << j.second + 1 << ' ';
      }
    }
    cout << '\n';
  }
  return 0;
}

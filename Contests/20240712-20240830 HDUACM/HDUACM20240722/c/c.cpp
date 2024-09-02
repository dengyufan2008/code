// by wls
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, m;
map<int, int> mp[6];
set<int> pt[8];
int cur[55], goal[55];
void init() {
  int p = 0;
  for (int i = 0; i < 9; i++) goal[++p] = 1;
  for (int i = 0; i < 3; i++)
    for (int j = 2; j <= 5; j++)
      for (int k = 0; k < 3; k++) goal[++p] = j;
  for (int i = 0; i < 9; i++) goal[++p] = 6;

  pt[0] = {7, 12, 13};
  pt[1] = {9, 15, 16};
  pt[2] = {3, 18, 19};
  pt[3] = {36, 37, 46};
  pt[4] = {39, 40, 48};
  pt[5] = {42, 43, 54};
  pt[6] = {1, 10, 21};
  pt[7] = {34, 45, 52};

  mp[0] = {{13, 16},
           {14, 17},
           {15, 18},
           {16, 19},
           {17, 20},
           {18, 21},
           {19, 10},
           {20, 11},
           {21, 12},
           {10, 13},
           {11, 14},
           {12, 15},
           {1, 7},
           {4, 8},
           {7, 9},
           {8, 6},
           {9, 3},
           {6, 2},
           {3, 1},
           {2, 4}};
  mp[1] = {{1, 13},
           {4, 25},
           {7, 37},
           {13, 46},
           {25, 49},
           {37, 52},
           {46, 45},
           {49, 33},
           {52, 21},
           {45, 1},
           {33, 4},
           {21, 7},
           {10, 34},
           {22, 35},
           {34, 36},
           {35, 24},
           {36, 12},
           {24, 11},
           {12, 10},
           {11, 22}};
  mp[2] = {{7, 16},
           {8, 28},
           {9, 40},
           {16, 48},
           {28, 47},
           {40, 46},
           {48, 36},
           {47, 24},
           {46, 12},
           {36, 7},
           {24, 8},
           {12, 9},
           {13, 15},
           {14, 27},
           {15, 39},
           {27, 38},
           {39, 37},
           {38, 25},
           {37, 13},
           {25, 14}};
  mp[3] = {{9, 19},
           {6, 31},
           {3, 43},
           {19, 54},
           {31, 51},
           {43, 48},
           {54, 39},
           {51, 27},
           {48, 15},
           {39, 9},
           {27, 6},
           {15, 3},
           {16, 18},
           {17, 30},
           {18, 42},
           {30, 41},
           {42, 40},
           {41, 28},
           {40, 16},
           {28, 17}};
  mp[4] = {{3, 10},
           {2, 22},
           {1, 34},
           {10, 52},
           {22, 53},
           {34, 54},
           {52, 42},
           {53, 30},
           {54, 18},
           {42, 3},
           {30, 2},
           {18, 1},
           {19, 21},
           {20, 33},
           {21, 45},
           {33, 44},
           {45, 43},
           {44, 31},
           {43, 19},
           {31, 20}};
  mp[5] = {{37, 40},
           {38, 41},
           {39, 42},
           {40, 43},
           {41, 44},
           {42, 45},
           {43, 34},
           {44, 35},
           {45, 36},
           {34, 37},
           {35, 38},
           {36, 39},
           {46, 48},
           {47, 51},
           {48, 54},
           {51, 53},
           {54, 52},
           {53, 49},
           {52, 46},
           {49, 47}};
}
string s;
void rot(int id, bool rev) {
  static int tmp[55];
  memcpy(tmp, cur, sizeof(tmp));
  for (auto [x, y] : mp[id]) {
    if (rev)
      cur[x] = tmp[y];
    else
      cur[y] = tmp[x];
  }
}

int Res = 0;
bool check() {
  Res = 0;
  vector<int> er;
  for (int i = 1; i <= 54; i++)
    if (cur[i] != goal[i]) er.push_back(i);
  if (er.size() != 0 && er.size() != 2) return 0;
  if (er.size() == 0) return Res = -1, 1;
  for (int i = 0; i < 8; i++) {
    if (pt[i].count(er[0]) && pt[i].count(er[1])) return Res = i, 1;
  }
  return 0;
}
bool ok = 0;
vector<int> ans;
void dfs(int dep) {
  if (ok) return;
  if (check()) {
    if (Res != -1) {
      for (auto x : pt[Res]) ans.push_back(cur[x]);
    }
    ok = 1;
    return;
  }
  if (dep >= 3) return;
  for (int i = 0; i < 6; i++) {
    rot(i, 0), dfs(dep + 1), rot(i, 1);
    rot(i, 1), dfs(dep + 1), rot(i, 0);
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  init();
  int T;
  cin >> T;
  while (T--) {
    int tot = 0;
    for (int i = 0; i < 9; i++) {
      cin >> s;
      for (int j = 0; j < 12; j++)
        if (s[j] != '*') cur[++tot] = s[j] - '0';
    }

    ok = 0, ans.clear();
    dfs(0);
    if (ans.size() == 0)
      cout << "No problem\n";
    else {
      sort(ans.begin(), ans.end());
      for (int x : ans) cout << x << ' ';
      cout << '\n';
    }
  }
  return 0;
}

#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

typedef __int128_t LLL;

int PopCount(auto x) {
  int ans = 0;
  for (; x; x &= x - 1, ans++) {
  }
  return ans;
}

class Game {
  int alice_life, bob_life;
  LLL alice_chess, bob_chess, magic, attack_chess;
  int play_round, grow_round, grow_need, attack_coor;
  std::mt19937 Rand;

  bool CheckCoor(int coor_x, int coor_y) {
    if (coor_x < 0 || coor_x >= 9 || coor_y < 0 || coor_y >= 9) {
      return 0;
    }
    int coor = coor_x * 9 + coor_y;
    if (alice_chess >> coor & 1) {
      return 0;
    } else if (bob_chess >> coor & 1) {
      return 0;
    }
    return 1;
  }

  void Grow(int coor, int loop) {
    static std::vector<int> coor_list;
    int coor_x = coor / 9, coor_y = coor % 9;
    coor_list.clear();
    for (int i = 0; i < 9 * 9; i++) {
      if ((alice_chess | bob_chess | attack_chess | magic) >> i & 1 ^ 1) {
        coor_list.push_back(i);
      }
    }
    shuffle(coor_list.begin(), coor_list.end(), Rand);
    sort(coor_list.begin(), coor_list.end(), [&](int coor1, int coor2) {
      return abs(coor1 / 9 - coor_x) + abs(coor1 % 9 - coor_y) <
             abs(coor2 / 9 - coor_x) + abs(coor2 % 9 - coor_y);
    });
    int weight = 0;
    for (int i : coor_list) {
      weight += 1 << 20 - abs(i / 9 - coor_x) - abs(i % 9 - coor_y);
    }
    while (loop-- && !coor_list.empty()) {
      int target = Rand() % weight;
      for (auto i = coor_list.begin();; i++) {
        target -= 1 << 20 - abs(*i / 9 - coor_x) - abs(*i % 9 - coor_y);
        if (target < 0) {
          weight -= 1 << 20 - abs(*i / 9 - coor_x) - abs(*i % 9 - coor_y);
          magic |= (LLL)1 << *i, coor_list.erase(i);
          break;
        }
      }
    }
  }

  LLL CheckAscend(int coor) {
    int coor_x = coor / 9, coor_y = coor % 9;
    LLL tmp = 0;
    for (auto [delta_x, delta_y] : {std::make_pair(0, 1), std::make_pair(1, -1),
                                    std::make_pair(1, 0), std::make_pair(1, 1)}) {
      int neg = 0, pos = 0;
      for (int now_x = coor_x - delta_x, now_y = coor_y - delta_y;;) {
        if (now_x < 0 || now_x >= 9 || now_y < 0 || now_y >= 9) {
          break;
        } else if ((alice_chess >> now_x * 9 + now_y & 1) != (alice_chess >> coor & 1)) {
          break;
        } else if ((bob_chess >> now_x * 9 + now_y & 1) != (bob_chess >> coor & 1)) {
          break;
        }
        now_x -= delta_x, now_y -= delta_y, neg++;
      }
      for (int now_x = coor_x + delta_x, now_y = coor_y + delta_y;;) {
        if (now_x < 0 || now_x >= 9 || now_y < 0 || now_y >= 9) {
          break;
        } else if ((alice_chess >> now_x * 9 + now_y & 1) != (alice_chess >> coor & 1)) {
          break;
        } else if ((bob_chess >> now_x * 9 + now_y & 1) != (bob_chess >> coor & 1)) {
          break;
        }
        now_x += delta_x, now_y += delta_y, pos++;
      }
      if (neg + pos >= 3) {
        for (int i = -neg; i <= pos; i++) {
          tmp |= (LLL)1 << (coor_x + i * delta_x) * 9 + (coor_y + i * delta_y);
        }
      }
    }
    return tmp;
  }

  void Fight(LLL defend_chess) {
    int attack_strength = PopCount(attack_chess);
    int attack_extra = PopCount(attack_chess & magic);
    int defend_strength = PopCount(defend_chess);
    int defend_extra = PopCount(defend_chess & magic);

    int tmp = std::min(attack_extra, defend_extra);
    attack_extra -= tmp, defend_extra -= tmp;

    if (attack_extra) {
      tmp = std::min(attack_extra, defend_strength);
      attack_extra -= tmp, defend_strength -= tmp;
    } else {
      tmp = std::min(defend_extra, attack_strength);
      defend_extra -= tmp, attack_strength -= tmp;
    }

    tmp = std::min(attack_strength, defend_strength);
    attack_strength -= tmp, defend_strength -= tmp;

    if (attack_strength) {
      if (play_round & 1 ^ 1) {
        alice_life -= attack_strength;
      } else {
        bob_life -= attack_strength;
      }
    } else {
      if (play_round & 1) {
        alice_life -= defend_strength;
      } else {
        bob_life -= defend_strength;
      }
    }
  }

 public:
  void Init(long long seed = std::chrono::steady_clock().now().time_since_epoch().count()) {
    alice_life = bob_life = 6;
    alice_chess = bob_chess = magic = attack_chess = 0;
    play_round = grow_round = 0, grow_need = 11, attack_coor = 0;
    Rand = std::mt19937(seed);
  }

  Game() { Init(); }

  void Status(int &_alice_life, int &_bob_life,
              LLL &_alice_chess, LLL &_bob_chess,
              LLL &_magic, LLL &_attack_chess) {
    _alice_life = alice_life, _bob_life = bob_life;
    _alice_chess = alice_chess, _bob_chess = bob_chess;
    _magic = magic, _attack_chess = attack_chess;
  }

  /// @return -1:invalid operate 0:game continues 1:game over
  int Operate(int coor_x, int coor_y) {
    if (!CheckCoor(coor_x, coor_y)) {
      return -1;
    }
    int coor = coor_x * 9 + coor_y;
    if (play_round & 1 ^ 1) {
      alice_chess |= (LLL)1 << coor;
    } else {
      bob_chess |= (LLL)1 << coor;
    }
    LLL tmp = CheckAscend(coor);
    if (play_round & 1 ^ 1) {
      alice_chess ^= tmp;
    } else {
      bob_chess ^= tmp;
    }
    if (attack_chess) {
      attack_chess ^= attack_chess & (LLL)1 << coor;
      Fight(tmp);
      magic ^= magic & (attack_chess | tmp);
      if (alice_life <= 0 || bob_life <= 0) {
        return 1;
      }
      Grow(attack_coor, 5), grow_round = -1;
      attack_chess = attack_coor = 0;
    } else {
      attack_chess = tmp, attack_coor = coor;
    }
    play_round++, grow_round++;
    if (grow_round == (grow_need | 1)) {
      Grow(coor, 2), grow_round = 0, grow_need > 2 && --grow_need;
    }
    return 0;
  }
};

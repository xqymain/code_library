#include <bits/extc++.h>

// 1 插入 2 删除 3 查询排名 4 查询位次 5 查询前驱 6 查询后继

using namespace std;
#define pll pair<long long, long long>
const long long INF = 1ll << (sizeof(long long) * 8 - 2);
__gnu_pbds::tree<pll, __gnu_pbds::null_type, std::less<pll>,
                 __gnu_pbds::rb_tree_tag,
                 __gnu_pbds::tree_order_statistics_node_update>
    rbt;
long long n;

int main() {
  int opt;
  long long k;
  decltype(rbt)::point_iterator ptr;
  qcin>>n;
  for (int i = 1; i <= n; i++) {
    qcin>>opt>>k;
    switch (opt) {
    case 1:
      rbt.insert(make_pair(k, i));
      break;
    case 2:
      rbt.erase(rbt.lower_bound(make_pair(k, 0)));
      break;
    case 3:
      qcout<<(rbt.order_of_key(make_pair(k, 0)) + 1);
      break;
    case 4:
      qcout<<(rbt.find_by_order(k - 1)->first);
      break;
    case 5:
      ptr = rbt.lower_bound(make_pair(k, 0));
      --ptr;
      qcout<<(ptr->first);
      break;
    case 6:
      ptr = rbt.upper_bound(make_pair(k, INF));
      qcout<<(ptr->first);
      break;
    }
  }
  return 0;
}
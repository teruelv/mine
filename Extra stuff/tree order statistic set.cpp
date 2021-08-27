
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>

using namespace __gnu_pbds;

typedef tree <ii, null_type, less<ii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

typedef long double ld;
typedef long long ll;
typedef pair <ll, ll> ii;



//s.order_of_key(x)       cant < x
//*s.find_by_order(k)      k-esimo elemento (0...n-1)

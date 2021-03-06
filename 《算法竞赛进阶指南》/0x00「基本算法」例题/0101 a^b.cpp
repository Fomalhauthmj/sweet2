#include <iostream>
using namespace std;
#define ll long long
ll a, b, p;
ll power(ll a, ll b, ll p)
{
    ll ans = 1 % p;
    for (; b; b >>= 1)
    {
        if (b & 1)
            ans = ans * a % p;
        a = a * a % p;
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> a >> b >> p;
    cout << power(a, b, p) << endl;
    //system("pause");
    return 0;
}
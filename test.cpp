#include <cstring>
#include <iostream>
#include <queue>
#include <stdio.h>
using namespace std;
#define ui unsigned int
ui seed, lastans;
ui A[16][16], R[16][16];
ui base1[16], base2[16];
ui ret[16][16];
struct node
{
    ui matrix[16][16];
};
deque<node> q;
deque<node> qc;
void Init()
{
    base1[0] = base2[0] = 1;
    for (int i = 1; i < 16; i++)
        base1[i] = base1[i - 1] * 17;
    for (int i = 1; i < 16; i++)
        base2[i] = base2[i - 1] * 19;
}
void Build()
{
    seed ^= lastans;
    for (int i = 0; i < 16; i++)
    {
        seed ^= seed * seed + 15;
        for (int j = 0; j < 16; j++)
            A[i][j] = (seed >> j) & 1;
    }
}
void Mul(ui m1[16][16], ui m2[16][16])
{
    memset(R, 0, sizeof(R));
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            for (int k = 0; k < 16; k++)
            {
                R[i][j] = (R[i][j] + m1[i][k] * m2[k][j]) % 2;
            }
        }
    }
}
ui Ret()
{
    ui ans = 0;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
            ans += ret[i][j] * base1[i] * base2[j];
    }
    return ans;
}
int main()
{
    freopen("input", "r", stdin);
    freopen("output2", "w", stdout);
    int T;
    scanf("%d", &T);
    Init();
    while (T--)
    {
        while (q.size())
            q.pop_front();
        memset(ret, 0, sizeof(ret));
        int n;
        scanf("%d", &n);
        ui t;
        lastans = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> t >> seed;
            if (t == 1)
            {
                Build();
                node add;
                if (!empty_flag)
                    memcpy(ret, A, sizeof(ret));
                else
                {
                    Mul(A, ret);
                    memcpy(ret, R, sizeof(ret));
                }
                empty_flag++;
                memcpy(add.matrix, A, sizeof(add.matrix));
                q.push_back(add);
            }
            else
            {
                if (empty_flag)
                {
                    empty_flag--;
                    q.pop_front();
                    if (empty_flag)
                    {
                        qc = q;
                        ui T[16][16];
                        memcpy(T, qc.back().matrix, sizeof(T));
                        qc.pop_back();
                        while (qc.size())
                        {
                            Mul(T, qc.back().matrix);
                            qc.pop_back();
                            memcpy(T, R, sizeof(T));
                        }
                        memcpy(ret, T, sizeof(ret));
                    }
                }
            }
            ui ans = 0;
            if (empty_flag)
                ans = Ret();
            lastans = ans;
            cout << ans << endl;
        }
    }
    system("pause");
    return 0;
}

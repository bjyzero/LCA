#include <bits/stdc++.h>
using namespace std;

void solve(const int &Case)
{
    int n;
    cin >> n;

    //确认和 x 相连的数(向上和向下) 有哪些
    vector<vector<int>> G(n + 1);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    // 倍增数组，制表
    vector<array<int, 21>> F(n + 1);    // 21 和给的数据有关系
    vector<int> dep(n + 1);

    function<void(int, int)> dfs = [&](int x, int fax)
    {
        F[x][0] = fax;
        for (int i = 1; i <= 20; ++i)
        {
            F[x][i] = F[F[x][i - 1]][i - 1];
        }

        for (const auto &tox : G[x])    // 遍历和 x 有关的所有结点
        {
            if (tox == fax)    // 确保不是向上的父结点
                continue;
            dep[tox] = dep[x] + 1;
            dfs(tox, x);
        }
    };

    dfs(1, 0);    // dfs()中 1 是因为根节点为 1 号节点

    auto glca = [&](int x, int y)
    {
        if (dep[x] < dep[y])
            swap(x, y);

        // 将 x 跳到和 y 相同的深度
        int d = dep[x] - dep[y];
        for (int i = 20; i >= 0; --i)
        {
            if (d >> i & 1)
                x = F[x][i];
        }

        if (x == y)
            return x;

        // 循环顺序不能变，必须倒序
        for (int i = 20; i >= 0; --i)
        {
            if (F[x][i] != F[y][i])    // x 和 y 一起向上跳，但是不能重合
            {
                x = F[x][i];
                y = F[y][i];
            }
        }
        return F[x][0];
    };

    int q;
    cin >> q;
    while (q--)
    {
        int x, y;
        cin >> x >> y;
        cout << glca(x, y) << '\n';
    }
}

int main(void)
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
    for (int i = 1; i <= T; ++i)
        solve(i);
    return 0;
}

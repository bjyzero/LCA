#include <bits/stdc++.h>
using namespace std;

void solve(const int &Case)
{
    int n;
    cin >> n;

    //ȷ�Ϻ� x ��������(���Ϻ�����) ����Щ
    vector<vector<int>> G(n + 1);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    // �������飬�Ʊ�
    vector<array<int, 21>> F(n + 1);
    vector<int> dep(n + 1);

    function<void(int, int)> dfs = [&](int x, int fax)
    {
        F[x][0] = fax;
        for (int i = 1; i <= 20; ++i)
        {
            F[x][i] = F[F[x][i - 1]][i - 1];
        }

        for (const auto &tox : G[x])
        {
            if (tox == fax)
                continue;
            dep[tox] = dep[x] + 1;
            dfs(tox, x);
        }
    };

    dfs(1, 0);

    auto glca = [&](int x, int y)
    {
        if (dep[x] < dep[y])
            swap(x, y);

        // �� x ������ y ��ͬ�����
        int d = dep[x] - dep[y];
        for (int i = 20; i >= 0; --i)
        {
            if (d >> i & 1)
                x = F[x][i];
        }

        if (x == y)
            return x;

        // ѭ��˳���ܱ䣬���뵹��
        for (int i = 20; i >= 0; --i)
        {
            if (F[x][i] != F[y][i])
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
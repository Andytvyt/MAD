#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <chrono>

using namespace std;

const double INF = 1e18;

int n, m;

// Danh sách kề
vector<vector<pair<int, double>>> g;

// =========================
// Đọc đồ thị từ file
// =========================
void readGraph(string filename)
{
    ifstream fin(filename);

    if (!fin)
    {
        cout << "Khong mo duoc file!\n";
        exit(0);
    }

    fin >> n >> m;

    g.assign(n + 1, {});

    for (int i = 0; i < m; i++)
    {
        int u, v;
        double w;

        fin >> u >> v >> w;

        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    fin.close();
}

int main()
{
    string filename;

    cout << "=============================\n";
    cout << "      DIJKSTRA ALGORITHM\n";
    cout << "=============================\n\n";

    cout << "Nhap ten file: ";
    cin >> filename;

    readGraph(filename);

    char tiepTuc;

    do
    {
        int start;
        int target;

        cout << "\nNhap dinh bat dau (1 -> " << n << "): ";
        cin >> start;

        while (start < 1 || start > n)
        {
            cout << "Nhap sai! Nhap lai: ";
            cin >> start;
        }

        cout << "Nhap dinh dich (1 -> " << n << "): ";
        cin >> target;

        while (target < 1 || target > n)
        {
            cout << "Nhap sai! Nhap lai: ";
            cin >> target;
        }

        vector<double> dist(n + 1, INF);
        vector<int> parent(n + 1, -1);

        priority_queue<
            pair<double, int>,
            vector<pair<double, int>>,
            greater<pair<double, int>>
        > pq;

        auto begin = chrono::high_resolution_clock::now();

        dist[start] = 0;

        pq.push({0, start});

        while (!pq.empty())
        {
            auto top = pq.top();
            pq.pop();

            double cost = top.first;
            int u = top.second;

            if (cost > dist[u])
                continue;

            for (auto &edge : g[u])
            {
                int v = edge.first;
                double w = edge.second;

                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    parent[v] = u;

                    pq.push({dist[v], v});
                }
            }
        }
        auto end = chrono::high_resolution_clock::now();
        auto runtime = chrono::duration_cast<chrono::microseconds>(end-begin);
        cout << "\nRuntime = "<< runtime.count()<< " microseconds\n";

        cout << "\n=============================\n";
        cout << "Khoang cach ngan nhat\n";
        cout << "=============================\n\n";

        for (int i = 1; i <= n; i++)
        {
            cout << "Dinh " << i << " : ";

            if (dist[i] == INF)
                cout << "Khong den duoc\n";
            else
                cout << dist[i] << endl;
        }

        cout << "\n=============================\n";

        if (dist[target] == INF)
        {
            cout << "Khong ton tai duong di!\n";
        }
        else
        {
            cout << "Duong ngan nhat tu "
                 << start
                 << " den "
                 << target
                 << " = "
                 << dist[target]
                 << endl;

            vector<int> path;

            for (int v = target; v != -1; v = parent[v])
                path.push_back(v);

            cout << "Duong di: ";

            for (int i = path.size() - 1; i >= 0; i--)
            {
                cout << path[i];

                if (i)
                    cout << " -> ";
            }

            cout << endl;
        }

        cout << "\nTinh tiep? (y/n): ";
        cin >> tiepTuc;

    } while (tiepTuc == 'y' || tiepTuc == 'Y');

    return 0;
}
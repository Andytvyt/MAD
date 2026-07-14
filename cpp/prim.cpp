#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <chrono>

using namespace std;

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
    cout << "       PRIM ALGORITHM\n";
    cout << "=============================\n\n";

    cout << "Nhap ten file: ";
    cin >> filename;

    readGraph(filename);

    char tiepTuc;

    do
    {
        int start;

        cout << "\nNhap dinh bat dau (1 -> " << n << "): ";
        cin >> start;

        while (start < 1 || start > n)
        {
            cout << "Nhap sai! Nhap lai: ";
            cin >> start;
        }

        vector<bool> visited(n + 1, false);

        priority_queue<
            pair<double, pair<int, int>>,
            vector<pair<double, pair<int, int>>>,
            greater<pair<double, pair<int, int>>>
        > pq;

        visited[start] = true;

        for (auto &edge : g[start])
        {
            pq.push({edge.second, {start, edge.first}});
        }

        double totalWeight = 0;

        cout << "\n=============================\n";
        cout << "Cac canh trong MST\n";
        cout << "=============================\n\n";

        int edgeCount = 0;

        auto begin = chrono::high_resolution_clock::now();

        while (!pq.empty())
        {
            auto top = pq.top();
            pq.pop();

            double w = top.first;
            int u = top.second.first;
            int v = top.second.second;

            if (visited[v])
                continue;

            visited[v] = true;

            totalWeight += w;

            edgeCount++;

            cout << u
                 << " ---- "
                 << v
                 << "    ("
                 << w
                 << ")\n";

            for (auto &edge : g[v])
            {
                if (!visited[edge.first])
                {
                    pq.push({edge.second, {v, edge.first}});
                }
            }
        }
        auto end = chrono::high_resolution_clock::now();

        auto runtime = chrono::duration_cast<chrono::microseconds>(end-begin);

        cout<<"Runtime = "<<runtime.count()<<" microseconds\n";

        cout << "\n=============================\n";

        if (edgeCount != n - 1)
        {
            cout << "Do thi KHONG lien thong!\n";
            cout << "Khong ton tai Minimum Spanning Tree.\n";
        }
        else
        {
            cout << "Tong trong so MST = "
                 << totalWeight
                 << endl;
        }

        cout << "\nTinh tiep? (y/n): ";
        cin >> tiepTuc;

    } while (tiepTuc == 'y' || tiepTuc == 'Y');

    return 0;
}
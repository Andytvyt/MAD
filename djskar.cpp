#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

vector<pair<int, ll>> g[11];

void add(int u, int v, ll w) {
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
}

int main() {
    
    add(1,2,3);     // A-B
    add(1,3,8);     // A-C
    add(1,4,4);     // A-D
    add(2,3,4);     // B-C
    add(3,5,5);     // C-E
    add(4,5,7);     // D-E
    add(5,6,2);     // E-F
    add(5,7,3);     // E-G
    add(6,8,2);     // F-H
    add(7,9,5);     // G-I
    add(8,9,6);     // H-I
    add(8,10,5);    // H-J
    add(9,10,1.5);  // I-J
    add(4,10,20);   // D-J

    cout << "=== DIJKSTRA - TIM DUONG NGAN NHAT DEN CUA HANG O QUAN 1 (J) ===\n\n";

    char tiepTuc;
    do {
        int start;
        cout << "Nhap diem bat dau (1=A, 2=B, ..., 10=J): ";
        cin >> start;

        while (start < 1 || start > 10) {
            cout << "Nhap sai! Vui long nhap lai: ";
            cin >> start;
            continue;
        }

        vector<ll> dist(11, INF);
        dist[start] = 0;

        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            auto front = pq.top(); pq.pop();
            ll cost = front.first;
            int u = front.second;

            if (cost > dist[u]) continue;

            for (auto &e : g[u]) {
                int v = e.first;
                ll w = e.second;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "\n=== KET QUA TU " << char('A' + start - 1) << " ===\n";
        for (int i = 1; i <= 10; i++) {
            cout << char('A' + i - 1) << " : " 
                 << (dist[i] == INF ? "Khong den duoc" : to_string(dist[i]) + " km") << endl;
        }

        cout << "\n=> Duong ngan nhat den cua hang o Quan 1 (J): " << dist[10] << " km\n";

        cout << "\nTinh tiep khong? (y/n): ";
        cin >> tiepTuc;

    } while (tiepTuc == 'y' || tiepTuc == 'Y');

    system("pause");
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

typedef double ll;

vector<pair<int, ll>> g[11];

void add(int u, int v, ll w) {
    g[u].push_back({v, w});
    g[v].push_back({u, w});
}

int main() {

    add(1,2,3);      // A-B
    add(1,3,8);      // A-C
    add(1,4,4);      // A-D
    add(2,3,4);      // B-C
    add(3,5,5);      // C-E
    add(4,5,7);      // D-E
    add(5,6,2);      // E-F
    add(5,7,3);      // E-G
    add(6,8,2);      // F-H
    add(7,9,5);      // G-I
    add(8,9,6);      // H-I
    add(8,10,5);     // H-J
    add(9,10,1.5);   // I-J
    add(4,10,20);    // D-J

    cout << "=== PRIM - MINIMUM SPANNING TREE ===\n\n";

    char tiepTuc;

    do {

        int start;

        cout << "Nhap diem bat dau (1=A, 2=B, ..., 10=J): ";
        cin >> start;

        while (start < 1 || start > 10) {
            cout << "Nhap sai! Vui long nhap lai: ";
            cin >> start;
        }

        vector<bool> visited(11, false);

        priority_queue<
            pair<ll, pair<int,int>>,
            vector<pair<ll, pair<int,int>>>,
            greater<pair<ll, pair<int,int>>>
        > pq;

        visited[start] = true;

        for(auto &e : g[start])
            pq.push({e.second, {start, e.first}});

        ll totalWeight = 0;

        cout << "\n=== CAC CANH DUOC CHON ===\n";

        while(!pq.empty()){

            auto top = pq.top();
            pq.pop();

            ll w = top.first;
            int u = top.second.first;
            int v = top.second.second;

            if(visited[v]) continue;

            visited[v] = true;

            totalWeight += w;

            cout << char('A'+u-1)
                 << " - "
                 << char('A'+v-1)
                 << " : "
                 << w
                 << " km\n";

            for(auto &e : g[v]){
                if(!visited[e.first]){
                    pq.push({e.second,{v,e.first}});
                }
            }
        }

        cout << "\nTong trong so MST = " << totalWeight << " km\n";

        cout << "\nTinh tiep khong? (y/n): ";
        cin >> tiepTuc;

    } while(tiepTuc=='y' || tiepTuc=='Y');

    system("pause");
    return 0;
}
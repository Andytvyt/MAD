#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <random>
#include <string>

using namespace std;

//struct and function
struct Edge;

void generateMoreEdges();

void generateTree();

int randomInt(int L,int R);

void addEdge(int u,int v,int w);

void saveGraph();
//Global variables

vector<Edge> edges;
set<pair<int,int>> existed;

random_device rd;
mt19937 rng(rd());

int n;
int m;

int minWeight;
int maxWeight;

string filename;

//main

int main()
{
    cout<<"===== GRAPH GENERATOR =====\n\n";

    cout<<"Nhap ten file: ";
    cin>>filename;

    cout<<"Nhap so dinh: ";
    cin>>n;

    cout<<"Nhap so canh: ";
    cin>>m;

    while(m<n-1)
    {
        cout<<"Do thi lien thong can it nhat "<<n-1<<" canh.\n";
        cout<<"Nhap lai: ";
        cin>>m;
    }

    int maxEdges = n * (n - 1) / 2;
    while (m > maxEdges)
    {
        cout << "Do thi don voi " << n << " dinh chi co toi da "
             << maxEdges << " canh.\n";
        cout << "Nhap lai: ";
        cin >> m;
    }

    cout<<"Nhap trong so nho nhat: ";
    cin>>minWeight;

    cout<<"Nhap trong so lon nhat: ";
    cin>>maxWeight;

    generateTree();

    generateMoreEdges();

    saveGraph();

    cout<<"\nDa sinh thanh cong "<<filename<<"\n";

    return 0;
}

struct Edge
{
    int u;
    int v;
    int w;
};

int randomInt(int L,int R)
{
    uniform_int_distribution<int> dist(L,R);
    return dist(rng);
}

void addEdge(int u,int v,int w)
{
    if(u==v)
        return;

    if(u>v)
        swap(u,v);

    if(existed.count({u,v}))
        return;

    existed.insert({u,v});

    edges.push_back({u,v,w});
}

void generateTree()
{
    for(int i=2;i<=n;i++)
    {
        int parent=randomInt(1,i-1);

        int weight=randomInt(minWeight,maxWeight);

        addEdge(parent,i,weight);
    }
}

void generateMoreEdges()
{
    while(edges.size() < m)
    {
        int u=randomInt(1,n);
        int v=randomInt(1,n);

        int w=randomInt(minWeight,maxWeight);

        addEdge(u,v,w);
    }
}

void saveGraph()
{
    ofstream fout(filename);

    fout<<n<<" "<<m<<"\n";

    for(auto &e:edges)
    {
        fout<<e.u<<" "
            <<e.v<<" "
            <<e.w<<"\n";
    }

    fout.close();
}
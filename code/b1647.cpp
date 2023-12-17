#include <iostream>
#include <queue>

using namespace std;
typedef pair<int, pair<int, int>> edge;

int getRoot(vector<int> &parent, int node) {
    if(parent[node] == node) return node;
    parent[node] = getRoot(parent, parent[node]);
    return parent[node];
}

int main() {
    int n, m;
    cin >> n >> m;

    int a, b, c;
    priority_queue<edge, vector<edge>, greater<edge>> edges;
    for(int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        edges.push({c, {a, b}});
    }

    vector<int> parent(n + 1);
    for(int i = 0; i <= n; i++)
        parent[i] = i;
    
    int rootCount = n;
    int cost = 0;
    edge top;
    while(rootCount > 2) {
        top = edges.top();
        edges.pop();

        a = top.second.first;
        b = top.second.second;
        c = top.first;

        getRoot(parent, a);
        getRoot(parent, b);

        if(parent[a] == parent[b])
            continue;
        
        parent[getRoot(parent, a)] = getRoot(parent, b);
        cost += c;
        rootCount--;
    }

    cout << cost << endl;
    return 0;
}
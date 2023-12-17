#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

vector<int> dikstra(map<int, vector<pair<int, int>>> adjMatrix, int x) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
    pair<int, int> top;

    vector<int> x2n(1001, 1000000);
    x2n[x] = 0;
    heap.push({0, x});
    while(!heap.empty()) {
        top = heap.top();
        heap.pop();
        
        if(x2n[top.second] < top.first)
            continue;

        for(auto h: adjMatrix[top.second]) {
            if(x2n[h.first] > h.second + top.first) {
                x2n[h.first] = h.second + top.first;
                heap.push({h.second + top.first, h.first});
            }
        }
    }
    return x2n;
}

int main() {
    int n, m, x;
    cin >> n >> m >> x;

    int s, e, t;
    map<int, vector<pair<int, int>>> adjMatrix;
    map<int, vector<pair<int, int>>> reversedAdjMatrix;
    for(int i = 0; i < m; i++) {
        cin >> s >> e >> t;
        adjMatrix[s].push_back({e, t});
        reversedAdjMatrix[e].push_back({s, t});
    }

    int maxCost = 0;
    vector<int> x2n = dikstra(adjMatrix, x);
    vector<int> n2x = dikstra(reversedAdjMatrix, x);
    for(int i = 1; i <= n; i++) {
        if(maxCost < n2x[i] + x2n[i])
            maxCost = n2x[i] + x2n[i];
    }
    cout << maxCost << endl;
    return 0;
}
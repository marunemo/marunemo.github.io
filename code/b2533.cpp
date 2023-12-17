#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> tree;
int earlyAd[1000001][2]; // 0 : 어답터 / 1 : ~어답터

void dfs(int node) {
    earlyAd[node][0] = 1;
    earlyAd[node][1] = 0;
    for(auto n: tree[node]) {
        if(earlyAd[n][0] == -1) {
            dfs(n);
            // 현재 노드가 어답터인 경우, 인접 노드가 어답터일 때와 어답터가 아닐 때 중 작은 값을 취함
            earlyAd[node][0] += min(earlyAd[n][0], earlyAd[n][1]);
            // 현재 노드가 어답터가 아닌 경우, 인접 노드는 반드시 어답터이어야 함 
            earlyAd[node][1] += earlyAd[n][0];
        }
    }
}

int main() {
    // Fast IO
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    tree = vector<vector<int>>(n + 1);

    int u, v;
    for(int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    for(int i = 1; i <= n; i++)
        earlyAd[i][0] = -1;

    dfs(1);
    cout << min(earlyAd[1][0], earlyAd[1][1]) << endl;
    return 0;
}
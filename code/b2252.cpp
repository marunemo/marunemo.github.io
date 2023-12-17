#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    int a, b;
    vector<int> priority(n + 1);
    vector<vector<int>> table(n + 1);
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        table[a].push_back(b);
        priority[b]++;
    }

    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(priority[i] == 0)
            q.push(i);
    }

    int top;
    while(!q.empty()) {
        top = q.front();
        q.pop();

        cout << top << ' ';
        for(auto node: table[top]) {
            priority[node]--;
            if(priority[node] == 0)
                q.push(node);
        }
    }

    cout << endl;
    return 0;
}
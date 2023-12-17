#include <iostream>
#include <queue>

using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;

    queue<pair<long long, long>> q;
    pair<long long, long> top;

    q.push({a, 1});
    while(!q.empty()) {
        top = q.front();
        q.pop();

        if(top.first == b) {
            cout << top.second << endl;
            return 0;
        }

        if(top.first * 2 <= b)
            q.push({top.first * 2, top.second + 1});
        if(top.first * 10 + 1 <= b)
            q.push({top.first * 10 + 1, top.second + 1});
    }

    cout << -1 << endl;
    return 0;
}
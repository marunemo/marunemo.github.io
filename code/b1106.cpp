#include <iostream>
#include <vector>

using namespace std;

int main() {
    int c, n;
    cin >> c >> n;

    int cost, value;
    int costSum = 0;
    vector<pair<int, int>> costValue(n);
    for(int i = 0; i < n; i++) {
        cin >> cost >> value;
        costValue[i] = {cost, value};
        costSum += cost;
    }

    cout << costSum << endl;
    vector<vector<int>> knapsack(n, vector<int>(costSum + 1, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= costSum; j++) {
            // 비용을 지불하지 않을 시
            knapsack[i][j] = knapsack[i - 1][j];
            // 비용을 지불했을 시(비용 지불 전 고객 + 비용 지불 시 고객)
            if(j >= costValue[i].first)
                knapsack[i][j] = max(knapsack[i][j], knapsack[i - 1][j - costValue[i].first] + costValue[i].second);
        }
    }

    for(int i = 0; i <= costSum; i++) {
        // 낮은 총 비용부터 최소 고객을 만족하는 비용 탐색
        if(knapsack[n - 1][i] >= c) {
            cout << i << endl;
            return 0;
        }
    }
    return 0;
}
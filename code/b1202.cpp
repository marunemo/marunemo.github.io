#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
typedef pair<long, long> jewel;

jewel jewels[300000];
long bag[300000];

int main() {
    // Fast IO
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    long priceSum = 0;

    for(int i = 0; i < n; i++)
        cin >> jewels[i].first >> jewels[i].second;

    for(int i = 0; i < k; i++)
        cin >> bag[i];
    
    sort(jewels, jewels + n);
    sort(bag, bag + k);
    
    int jewelIndex = 0;
    priority_queue<int, vector<int>, less<int>> price;
    for(int i = 0; i < k; i++) {
        // 현재 배낭에 담을 수 있는 보석 모두 추가
        // 배낭이 오름차순으로 정렬되어 있으므로, 다음 배낭은 무조건 이전의 배낭을 담을 수 있음
        // 따라서 이전 배낭에서 담은 보석을 제외한 이전의 모든 보석을 불러옴
        while(jewelIndex < n && jewels[jewelIndex].first <= bag[i])
            price.push(jewels[jewelIndex++].second);
        
        // price는 내림차순이므로, 맨 앞이 현재 담을 수 있는 보석 중 가장 가격이 높음
        if(!price.empty()) {
            priceSum += price.top();
            price.pop();
        }
    }
    
    cout << priceSum << endl;
    return 0;
}
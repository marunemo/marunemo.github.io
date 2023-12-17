#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define ft first
#define sd second

using namespace std;
using pii = pair<int, int>;

// second에 대해 오름차순 / 같은 경우 first에 대해 오름차순
bool compare(pii a, pii b) {
    if(a.sd == b.sd)
        return a.ft < b.ft;
    return a.sd < b.sd;
}

// 참고 : https://everenew.tistory.com/108

int main() {
    // Fast IO
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    // 사람 수
    int n;
    cin >> n;

    // 집과 사무실 위치
    vector<pii> pos;
    int first, second;
    for(int i = 0; i < n; i++) {
        cin >> first >> second;
        // 더 왼쪽에 있는 것을 first에 저장
        if(first > second)
            pos.push_back({second, first});
        else
            pos.push_back({first, second});
    }
    
    // 철도 길이
    int d;
    cin >> d;

    // 집이나 사무소 중 오른쪽에 있는 것을 기준으로 오름차순 정렬
    // 오른쪽에 있는 집이나 사무실의 위치가 같은 사람은 그 외의 것이 더 왼쪽에 있는 사람을 앞으로 보냄
    sort(pos.begin(), pos.end(), compare);

    priority_queue<int, vector<int>, greater<int>> q;
    int max_count = 0;
    for(int i = 0; i < n; i++) {
        // 철도의 범위 지정
        int end = pos[i].sd;
        int start = end - d;

        // 현재 가장 왼쪽에 있는 사무실이나 집이 철도 범위를 벗어나면
        // 해당 사람은 선분 내부에 없는 것으로 간주
        while(!q.empty() && q.top() < start)
            q.pop();

        // 만약 현재 왼쪽에 있는 것이 철도 범위 안에 있다면
        if(pos[i].ft >= start) {
            // 선분 안에 있는 것으로 간주
            q.push(pos[i].ft);

            // 포함되는 사람의 최댓값 선택
            int count = q.size();
            max_count = max(count, max_count);
        }
    }

    // 최댓값 출력
    cout << max_count << endl;
    return 0;
}
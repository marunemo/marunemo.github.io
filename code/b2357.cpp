#include <iostream>
#include <vector>
#include <cmath>
#define MAX_N 100000
#define MAX_RANGE 1000000000

using namespace std;
using min_max = pair<int, int>;

// 참고 : https://book.acmicpc.net/ds/segment-tree
// 코드 참고 : https://everenew.tistory.com/80
int n, m;
int arr[MAX_N + 1];
vector<int> min_tree, max_tree;

// 세그멘트 트리 생성
void init(int node, int start, int end) {
    // 리프 노드는 두 트리가 동일
    if(start == end)
        min_tree[node] = max_tree[node] = arr[start];
    // min_tree와 max_tree는 각 리프 노드의 최솟값과 최댓값을 저장
    else {
        init(node * 2, start, (start + end) / 2);
        init(node * 2 + 1, (start + end) / 2 + 1, end);
        min_tree[node] = min(min_tree[node * 2], min_tree[node * 2 + 1]);
        max_tree[node] = max(max_tree[node * 2], max_tree[node * 2 + 1]);
    }
}

min_max query(int node, int start, int end, int left, int right) {
    // 만약 범위 밖이면 최솟값은 범위 외 값을, 최댓값은 0을 반환
    if(end < left || start > right)
        return make_pair(MAX_RANGE + 1, 0);
    // 현재 범위가 탐색 범위에 완전히 감싸지면, 현재 위치의 최솟값과 최댓값 반환
    if(start >= left && end <= right)
        return make_pair(min_tree[node], max_tree[node]);
    
    // 현재 범위의 일부가 탐색 범위 내에 있다면, 좌측 노드와 우측 노드의 최소최댓값을 비교
    min_max mm_left = query(node * 2, start, (start + end) / 2, left, right);
    min_max mm_right = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
    return make_pair(min(mm_left.first, mm_right.first), max(mm_left.second, mm_right.second));
}

int main() {
    // Fast IO
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;

    // 높이가 H인 트리는 2^(H+1)-1개의 노드를 필요로 하나,
    // 루트 노드의 인덱스가 1부터 시작하므로 최대 2^(H+1)개의 공간이 필요함
    int height = (int)ceil(log2(n));
    min_tree = vector<int>(1 << (height + 1));
    max_tree = vector<int>(1 << (height + 1));

    // 범위가 1부터 N까지이므로, 인덱싱을 1부터 시작
    for(int i = 1; i <= n; i++)
        cin >> arr[i];
    
    // 세그먼트 트리 생성
    init(1, 1, n);

    int left, right;
    min_max result;
    for(int i = 0; i < m; i++) {
        cin >> left >> right;
        result = query(1, 1, n, left, right);
        cout << result.first << ' ' << result.second << '\n';
    }
    return 0;
}
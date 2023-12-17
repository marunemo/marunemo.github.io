#include <iostream>
#include <vector>
#include <cmath>
#define MOD 1000000007

using namespace std;

// 참고 : https://book.acmicpc.net/ds/segment-tree
int n, m, k;
long long arr[1000001];
vector<long long> mul_tree;

void init(int node, int start, int end) {
    if(start == end)
        mul_tree[node] = arr[start];
    else {
        init(node * 2, start, (start + end) / 2);
        init(node * 2 + 1, (start + end) / 2 + 1, end);
        mul_tree[node] = (mul_tree[node * 2] * mul_tree[node * 2 + 1]) % MOD;
    }
}

long long query(int node, int start, int end, int left, int right) {
    if(start > right || end < left)
        return 1;
    if(start >= left && end <= right)
        return mul_tree[node];
    
    long long left_mul = query(node * 2, start, (start + end) / 2, left, right);
    long long right_mul = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
    return (left_mul * right_mul) % MOD;
}

void update(int node, int start, int end, int index, long long new_value) {
    if(start > index || end < index)
        return;
    if(start == end) {
        mul_tree[node] = new_value;
        arr[index] = new_value;
    }
    else {
        update(node * 2, start, (start + end) / 2, index, new_value);
        update(node * 2 + 1, (start + end) / 2 + 1, end, index, new_value);
        mul_tree[node] = (mul_tree[node * 2] * mul_tree[node * 2 + 1]) % MOD;
    }
}

int main() {
    // Fast IO
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> k;

    int height = (int)ceil(log2(n));
    mul_tree = vector<long long>(1 << (height + 1));

    for(int i = 1; i <= n; i++)
        cin >> arr[i];
    
    init(1, 1, n);

    int a, b, c;
    for(int i = 0; i < m + k; i++) {
        cin >> a >> b >> c;
        if(a == 1)
            update(1, 1, n, b, c);
        else if(a == 2)
            cout << query(1, 1, n, b, c) << '\n';
    }
    return 0;
}
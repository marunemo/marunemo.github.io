#include <iostream>
#include <vector>
#include <algorithm>
#define ft first
#define sd second

using namespace std;
using lli = long long int;
using coord = pair<lli, lli>;

int n;
vector<coord> pos;
vector<coord> stack;

// ccw 알고리즘
lli ccw(coord a, coord b, coord c) {
    return (a.ft * b.sd) + (b.ft * c.sd) + (c.ft * a.sd) - ((b.ft * a.sd) + (c.ft * b.sd) + (a.ft * c.sd));
}

// 반시계 방향으로 정렬하는 코드
bool compare(coord a, coord b) {
    lli cc = ccw(pos[0], a, b);

    // cc가 0이 아니면 cc가 작은 순
    if(cc)
        return cc > 0;
    // 각도가 0이면 y 값이 작은 순
    if(a.sd != b.sd)
        return a.sd < b.sd;
    // 그 외에는 x 값이 작은 순 정렬
    return a.ft < b.ft;
}

void swap(coord &a, coord &b) {
    coord tmp = a;
    a = b;
    b = tmp;
}

int main() {
    // Fast IO
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    pos = vector<coord>(n);
    for(int i = 0; i < n; i++)
        cin >> pos[i].ft >> pos[i].sd;
    
    for(int i = 1; i < n; i++) {
        if(pos[i].sd < pos[0].sd)
            swap(pos[i], pos[0]);
        else if(pos[i].sd == pos[0].sd && pos[i].ft < pos[0].ft)
            swap(pos[i], pos[0]);
    }

    sort(++pos.begin(), pos.end(), compare);

    coord top, sub_top;
    stack.push_back(pos[0]);
    stack.push_back(pos[1]);
    for(int i = 2; i < n; i++) {
        while(stack.size() >= 2) {
            sub_top = stack.back();
            stack.pop_back();

            top = stack.back();
            if(ccw(top, sub_top, pos[i]) > 0) {
                stack.push_back(sub_top);
                break;
            }
        }
        stack.push_back(pos[i]);
    }

    cout << stack.size() << endl;
    return 0;
}
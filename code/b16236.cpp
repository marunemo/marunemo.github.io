#include <iostream>
#include <queue>

using namespace std;
typedef pair<int, int> rc;

void clear(priority_queue<rc ,vector<rc>, greater<rc>> &q) {
    while(!q.empty()) q.pop();
}

int main() {
    int n;
    cin >> n;

    rc top;
    vector<vector<int>> map(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> map[i][j];
            if(map[i][j] == 9) {
                top = {i, j};
                map[i][j] = 0;
            }
        }
    }

    int row, col;
    int depth = 0;
    int size = 2;
    int bite = 0;
    int cost = 0;
    vector<vector<bool>> found(n, vector<bool>(n, false));
    // 위쪽 우선, 동일 행에서는 왼쪽 우선
    priority_queue<rc, vector<rc>, greater<rc>> curr;
    priority_queue<rc, vector<rc>, greater<rc>> next;

    curr.push(top);
    found[top.first][top.second] = true;
    // 모든 지역 탐색이 끝날 때까지 실행(다음 depth가 존재하지 않을 때까지)
    while(!curr.empty()) {
        top = curr.top();
        curr.pop();
        row = top.first, col = top.second;

        if(map[row][col] != 0 && map[row][col] != 9 && map[row][col] < size) {
            map[row][col] = 0;
            bite++;
            if(bite == size) {
                size++;
                bite = 0;
            }
            cost += depth;
            // 초기화
            found = vector<vector<bool>>(n, vector<bool>(n, false));
            clear(curr);
            clear(next);
            curr.push(top);
            found[top.first][top.second] = true;
            depth = 0;
        }
        
        // 한 번도 탐색 안 한 곳을 탐색
        // 자신보다 큰 물고기는 지나갈 수 없음
        if(row > 0 && !found[row - 1][col] && map[row - 1][col] <= size) {
            next.push({row - 1, col});
            found[row - 1][col] = true;
        }
        if(col > 0 && !found[row][col - 1] && map[row][col - 1] <= size) {
            next.push({row, col - 1});
            found[row][col - 1] = true;
        }
        if(col < n - 1 && !found[row][col + 1] && map[row][col + 1] <= size) {
            next.push({row, col + 1});
            found[row][col + 1] = true;
        }
        if(row < n - 1 && !found[row + 1][col] && map[row + 1][col] <= size) {
            next.push({row + 1, col});
            found[row + 1][col] = true;
        }

        // 현재 depth에서 탐색이 종료되면 다음 depth에서 탐색 진행
        if(curr.empty()) {
            curr = next;
            clear(next);
            depth++;
        }
    }

    cout << cost << endl;
    return 0;
}
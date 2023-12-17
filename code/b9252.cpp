#include <iostream>
#include <vector>
#include <string>

using namespace std;

int lcs[1001][1001];

// 참고 : https://beginthread.tistory.com/142
int main() {
    string a, b;
    cin >> a >> b;

    int aLen = a.length();
    int bLen = b.length();

    // a와 b의 자리에서 같은 글자가 나온 개수 저장
    for(int i = 0; i <= aLen; i++) {
        for(int j = 0; j <= bLen; j++)
            lcs[i][j] = 0;
    }

    for(int i = 1; i <= aLen; i++) {
        for(int j = 1; j <= bLen; j++) {
            // 현재 글자가 같은 경우, 이전의 lcs 길이 + 1 저장
            if(a[i - 1] == b[j - 1])
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            // 현재 글자가 다를 경우, 이전 lcs 최대 길이 저장
            else
                lcs[i][j] = max(lcs[i][j - 1], lcs[i - 1][j]);
        }
    }

    int i = aLen;
    int j = bLen;
    vector<char> answer;
    // lcs 길이가 없을 때까지 역행
    while(lcs[i][j] != 0) {
        // 현재 글자가 같은 경우, 글자 저장
        if(a[i - 1] == b[j - 1]) {
            answer.push_back(a[i - 1]);
            i--, j--;
        }
        // 글자가 다를 경우, 더 긴 lcs가 있는 방향으로 이동
        else {
            if(lcs[i - 1][j] > lcs[i][j - 1])
                i--;
            else
                j--;
        }
    }

    cout << answer.size() << '\n';
    while(!answer.empty()) {
        cout << answer.back();
        answer.pop_back();
    }
    cout << endl;
    return 0;
}
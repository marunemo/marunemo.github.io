#include <iostream>
#include <string>

using namespace std;

// 이미 켜진 행에 대하여 스위치를 누르면 해당 행이 사라지므로,
// 켜진 행을 하나 완성헀을 때, 다른 켜진 행의 개수가 최대인 시점을 찾는다.
// 단, 하나의 행을 완성했을 때 다른 행도 완성되려면, 각 행은 모두 종속이므로 두 행이 동일해야한다.
int main() {
    int n, m;
    cin >> n >> m;

    string lamp[50];
    for(int i = 0; i < n; i++)
        cin >> lamp[i];
    
    int k;
    cin >> k;

    int maxCount = 0;
    for(int i = 0; i < n; i++) {
        int switchCount = 0;
        for(int j = 0; j < m; j++) {
            if(lamp[i][j] == '0')
                switchCount++;
        }

        int count = 0;
        if(switchCount <= k && (k - switchCount) % 2 == 0) {
            for(int j = 0; j < n; j++) {
                if(lamp[i].compare(lamp[j]) == 0)
                    count++;
            }
        }

        if(maxCount < count)
            maxCount = count;
    }

    cout << maxCount << endl;
    return 0;
}
#include <iostream>
#define MOD 1000000000
#define MAX_RANGE 1023

using namespace std;

// 첫번째 배열 = 자리 길이
// 두번째 배열 = 맨 마지막 자리의 숫자
// 세번째 배열 = 9~0의 유무에 따른 비트마스킹(9~0 = 111...11)
int memo[101][10][1024];

int main() {
    int target_digit;
    cin >> target_digit;

    // 첫번째 자리 수에 1~9까지의 분기 생성
    // 첫 자리는 0이 될 수 없으므로, 0은 제외
    for(int curr_num = 1; curr_num <= 9; curr_num++)
        memo[1][curr_num][1 << curr_num] = 1;

    // 두번째부터 n자리까지 반복
    for(int index = 2; index <= target_digit; index++) {
        // 각 자리에 0~9이 들어가는 분기 생성
        for(int curr_num = 0; curr_num <= 9; curr_num++) {
            // 과거 숫자 이력에 대한 모든 분기 조사
            for(int bit_mask = 0; bit_mask <= MAX_RANGE; bit_mask++) {
                // 현재 자리의 숫자와 1만큼 차이나는 이전 분기를 현재 분기에 합산(0~9 범위 내)
                // memo[index][curr_num][bit_mask | (1 << curr_num)] = 현재 자리 / 현재 숫자 / 0~9가 임의로 포함된 분기 중 현재 숫자가 반드시 포함된 분기
                // memo[index - 1][curr_num ± 1][bit_mask] = 이전 자리 / 현재 숫자와 1만큼 차이나는 분기 / 현재 숫자가 과거에 있었던지와 무관한 임의의 분기
                if(curr_num > 0)
                    memo[index][curr_num][bit_mask | (1 << curr_num)] = (memo[index][curr_num][bit_mask | (1 << curr_num)] + memo[index - 1][curr_num - 1][bit_mask]) % MOD;
                if(curr_num < 9)
                    memo[index][curr_num][bit_mask | (1 << curr_num)] = (memo[index][curr_num][bit_mask | (1 << curr_num)] + memo[index - 1][curr_num + 1][bit_mask]) % MOD;
            }
        }
    }

    // 길이가 n이고, 모든 숫자가 있었던 이력이 있는 수들 중 현재 숫자가 0~9인 모든 분기 조사
    int count = 0;
    for(int last_num = 0; last_num <= 9; last_num++)
        count = (count + memo[target_digit][last_num][MAX_RANGE]) % MOD;

    cout << count << endl;
    return 0;
}
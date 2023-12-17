#include <iostream>
#include <map>

using namespace std;

// 참고 : https://degurii.tistory.com/158
int main() {
    long long int a, b;
    cin >> a >> b;

    long long int sq_two = 1;
    map<long, long long int> one_count;
    one_count[0] = 0;

    // 최상위 비트가 sq_two일때, 모든 1의 개수의 누적 합
    // 최상위 비트 기준이므로, 최상위 비트가 4(1000)일 경우, 1~7까지의 모든 1의 누적 합
    one_count[sq_two] = sq_two;
    while(sq_two < b) {
        sq_two *= 2;
        one_count[sq_two] = one_count[sq_two / 2] * 2 + sq_two;
    }

    long long a_one = 0;
    long long b_one = 0;
    long long bits = 1;

    // a 이상이므로, a는 개수에 포함
    a--;
    while(a > bits) bits <<= 1;
    for(; a != 0; bits >>= 1) {
        if(a & bits) {
            // one_count[bits / 2] = 현재 최상위 비트 이전의 모든 1의 누적합
            // (a - bits + 1) = 현재 비트를 포함하여 표현될 현재 비트 이하 값의 개수
            // 예로 들어 1100의 경우, 1000~1100까지 4번째 비트를 포함하여 나타내어지는 값의 개수가 (12 - 8 + 1)개 있음
            a_one += one_count[bits / 2] + (a - bits + 1);
            a -= bits;
        }
    }

    bits = 1;
    while(b > bits) bits <<= 1;
    for(; b != 0; bits >>= 1) {
        if(b & bits) {
            b_one += one_count[bits / 2] + (b - bits + 1);
            b -= bits;
        }
    }

    cout << (b_one - a_one) << endl;
    return 0;
}
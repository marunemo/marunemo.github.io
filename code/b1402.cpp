#include <iostream>
using namespace std;

// 부호 관계 없이
// 큰 수 : 1씩 곱하면 무한대까지 더할 수 있음
// 작은 수 : -1 * -1 * 1 => -1 + (-1 + 1) = -1로 무한대까지 뺄 수 있음
int main() {
    int t;
    cin >> t;

    long a, b;
    for(int i = 0; i < t; i++)
        cin >> a >> b;
        
    for(int i = 0; i < t; i++)
        cout << "yes\n";
    return 0;
}
#include <iostream>

using namespace std;

/* 참고 : https://namu.wiki/w/%EC%98%A4%EC%9D%BC%EB%9F%AC%20%ED%94%BC%20%ED%95%A8%EC%88%98
 * 코드 출처 : https://kyr-db.tistory.com/197
 * 위 자료에 따르면, 오일러 피 함수는 다음과 같이 나타낼 수 있다.
 * φ(n)≡∣{m:1≤m≤n,gcd(m,n)=1}∣ (n∈N) ==> 자연수 n에 대해 서로소인 자연수들의 개수
 * 오일러 피 함수는 소수 p에 대해 φ(p^n) = p^n−p^(n−1) = p^n*(1−1/p) = p^n*(p-1)/p이 성립한다.
 * 또한, 오일러 피 함수는 φ(ab)=φ(a)φ(b)이라는 성질이 있다.
 * 이 두 특성을 합치면, 합성수 n에 대해 φ(a^na)φ(b^nb)...φ(z^nz)로 나타낼 수 있다(a~z는 소수).
 * 이는 a^na*(a-1)/a*b^nb*(b-1)/b*...z^nz*(z-1)/z이고, a^na*b^nb*...z^nz = n이므로
 * φ(n) = φ(a^na)φ(b^nb)...φ(z^nz) = n*(a-1)/a*(b-1)/b*...*(z-1)/z이 성립한다.
 * 정리하자면, 합성수 n에 대해 n의 소인수들의 "f(x) = (x-1)/x" 식들의 곱이 φ(n)의 값이 된다.
 * 소수 n의 경우에는 위의 소수 공식에 따라, φ(n) = n*(n-1)/n = n-1이다.
 **/
int main() {
    long long n;
    cin >> n;

    long long euler = n;
    for(long long p = 2; p * p <= n; p++) {
        // p가 n의 소인수일 경우, n에 약수의 (x-1)/x를 곱해줌
        if(n % p == 0)
            euler = euler / p * (p - 1);
        // p^n에서 중복해서 세지 않도록, p의 거듭제곱 제거
        while(n % p == 0)
            n /= p;
    }

    // 가장 큰 소수가 거듭제곱으로 이루어져 1로 나누어 떨어진 경우,
    // 위 식에서 모두 나누어 떨어지면 그대로 출력
    if(n == 1)
        cout << euler << endl;
    // 가장 큰 소수가 거듭제곱이 아니어서 위 식에서 모두 나누어 떨어지지 않은 경우, 
    // 남은 마지막 수는 무조건 소수이므로 소수 공식에 따라 (n-1)/n 적용
    else
        cout << (euler / n * (n - 1)) << endl;
    return 0;
}
#include <iostream>

using namespace std;

long long permutSum[100001];

int main() {
    // Fast IO
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    int n;
    long long s;
    cin >> n >> s;
    
    long long permut;
    long long sum = 0;
    permutSum[0] = 0;
    for(int i = 1; i <= n; i++) {
        cin >> permut;
        sum += permut;
        permutSum[i] = sum;
    }

    int l = 0;
    int r = 1;
    long long accSum;
    int minLen = n + 1;
    while(l < r && r <= n) {
        accSum = permutSum[r] - permutSum[l];
        if(accSum < s)
            r++;
        else {
            if(minLen > r - l)
                minLen = r - l;
            l++;
        }
    }
    
    if(minLen == n + 1)
        cout << 0 << endl;
    else
        cout << minLen << endl;
    return 0;
}
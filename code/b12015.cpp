#include <iostream>

using namespace std;

int lis[1000001];

int main() {
    // Fast IO
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    int permut;
    int lisIndex = 0;
    for(int i = 0; i < n; i++) {
        cin >> permut;
        
        if(lisIndex == 0)
            lis[lisIndex++] = permut;
        else {
            if(lis[lisIndex - 1] < permut)
                lis[lisIndex++] = permut;
            else {
                int l = 0;
                int r = lisIndex - 1;
                int mid;
                while(l < r) {
                    mid = (l + r) / 2;
                    if(lis[mid] < permut)
                        l = mid + 1;
                    else
                        r = mid;
                }
                lis[r] = permut;
            }
        }
    }

    cout << lisIndex << endl;
    return 0;
}
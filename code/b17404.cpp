#include <iostream>
#include <vector>
#define MAX_VALUE 10000

using namespace std;

int main() {
    // Fast IO
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    long rgb[3];
    vector<int> rStart(3, MAX_VALUE);
    vector<int> gStart(3, MAX_VALUE);
    vector<int> bStart(3, MAX_VALUE);
    vector<int> preValue(3);
    int minCost[3];
    for(int i = 0; i < n; i++) {
        cin >> rgb[0] >> rgb[1] >> rgb[2];
        if(i == 0) {
            rStart[0] = rgb[0];
            gStart[1] = rgb[1];
            bStart[2] = rgb[2];
        }
        else {
            preValue = rStart;
            rStart[0] = min(preValue[1], preValue[2]) + rgb[0];
            rStart[1] = min(preValue[0], preValue[2]) + rgb[1];
            rStart[2] = min(preValue[0], preValue[1]) + rgb[2];
            
            preValue = gStart;
            gStart[0] = min(preValue[1], preValue[2]) + rgb[0];
            gStart[1] = min(preValue[0], preValue[2]) + rgb[1];
            gStart[2] = min(preValue[0], preValue[1]) + rgb[2];
            
            preValue = bStart;
            bStart[0] = min(preValue[1], preValue[2]) + rgb[0];
            bStart[1] = min(preValue[0], preValue[2]) + rgb[1];
            bStart[2] = min(preValue[0], preValue[1]) + rgb[2];
        }
    }

    minCost[0] = min(rStart[1], rStart[2]);
    minCost[1] = min(gStart[0], gStart[2]);
    minCost[2] = min(bStart[0], bStart[1]);

    minCost[0] = min(minCost[0], minCost[1]);
    minCost[0] = min(minCost[0], minCost[2]);

    cout << minCost[0] << endl;
    return 0;
}
#include <stdio.h>

void swap(int* s1, int* s2) {
    int tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}

int lineFinder(int *arr, int n) {
    int pie[9] = {0};
    for(int i = 0; i < n; i++)
        pie[i + 1] = pie[i] + arr[i];
    
    int lines = 0;
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(pie[i] + 50 == pie[j])
                lines++;
        }
    }
    return lines;
}

int chartMaker(int* arr, int depth, int n) {
    if(depth >= n) return lineFinder(arr, n);

    int maxLine = 0;
    for(int i = depth; i < n; i++) {
        swap(&arr[depth], &arr[i]);
        int line = chartMaker(arr, depth + 1, n);
        if(line > maxLine)
            maxLine = line;
        swap(&arr[depth], &arr[i]);
    }
    return maxLine;
}

int main() {
    int n;
    scanf("%d", &n);

    int ratio[8];
    for(int i = 0; i < n; i++)
        scanf("%d", &ratio[i]);

    swap(&ratio[0], &ratio[1]);
    printf("%d\n", chartMaker(ratio, 0, n));
    return 0;
}
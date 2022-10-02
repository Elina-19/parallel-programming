#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

int main() {

    int start, end;
    std::vector<int> res;

    printf("Start: ");
    std::cin >> start;
    printf("End: ");
    std::cin >> end;

    bool isSimple = true;
    int sqr = 0;

    #pragma omp parallel for private(isSimple, sqr)
    for (int i = start; i <= end; i++) {
        isSimple = true;
        sqr = sqrt(i);

        for (int j = 2; j <= sqr; j++) {
            if (i % j == 0) {
                isSimple = false;
                break;
            }
        }

        if (isSimple && i != 1) {
            #pragma omp critical
            res.insert(res.end(), i);
        }
    }
    sort(res.begin(), res.end());

    for (int i = 0; i < res.size(); i++) {
        printf("%d ", res[i]);
    }
}
#include <iostream>
#include <omp.h>
using namespace std;

int main()
{
    int sum = 0, a[20];
    for (int i = 0; i < 20; i++) {
        a[i] = i;
    }
#pragma omp parallel num_threads(4)
    {
// #pragma omp for schedule(dynamic,3)
// #pragma omp for schedule(static,3)
#pragma omp for schedule(static, 5)
        for (int i = 0; i < 20; i++) {
#pragma omp critical
            {
                cout << a[i] << " in the " << omp_get_thread_num()
                     << " th thread" << endl;
            }
        }
    }
    return 0;
}

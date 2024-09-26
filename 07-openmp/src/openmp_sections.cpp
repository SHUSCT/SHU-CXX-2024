#include <iostream>
#include <omp.h>

using namespace std;
int main()
{
    omp_set_num_threads(3);
#pragma omp parallel sections
    {
#pragma omp section
        {
            cout << omp_get_thread_num();
        }
#pragma omp section
        {
            cout << omp_get_thread_num();
        }
#pragma omp section
        {
            cout << omp_get_thread_num();
        }
    }
}

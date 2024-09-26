#include <iostream>
#include <omp.h>

int main()
{
    int shared_var = 0;

#pragma omp parallel private(shared_var)
    {
        // 每个线程都有自己的 shared_var 副本
        shared_var = omp_get_thread_num();
#pragma omp critical
        {
            std::cout << "Thread " << omp_get_thread_num()
                      << " has private shared_var = " << shared_var
                      << std::endl;
        }
    }
    return 0;
}

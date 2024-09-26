#include <iostream>
#include <omp.h>

int main()
{
    int shared_var = 0;  // 默认共享

#pragma omp parallel shared(shared_var)
    {
        // 所有线程都可以访问和修改 shared_var
        shared_var += 1;
#pragma omp critical
        {
            std::cout << "Thread " << omp_get_thread_num()
                      << " incremented shared_var to " << shared_var
                      << std::endl;
        }
    }
    return 0;
}

#include <iostream>
#include <omp.h>  //头文件

void Hello();

int main()
{
    int thread_count = 4;
#pragma omp parallel num_threads(thread_count)
    // 编程制导语句标识符，标志着并行域的建立
    {
        Hello();
    }
    return 0;
}

void Hello()
{
    int my_rank = omp_get_thread_num();        // 库函数：哪个线程
    int thread_count = omp_get_num_threads();  // 库函数：一共多少线程
#pragma omp critical  // 同步：确保只有一个线程在同一时间执行Hello函数中的打印操作
    {
        std::cout << "Hello from thread " << my_rank << " of " << thread_count
                  << std::endl;
    }
}

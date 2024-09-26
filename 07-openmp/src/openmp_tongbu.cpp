#include <iostream>
#include <omp.h>

int main()
{
    const int N = 10;
    int sum = 0;
#pragma omp parallel
    {
        int thread_sum = 0;
        // 每个线程计算局部和
#pragma omp for
        for (int i = 1; i <= N; i++) {
            thread_sum += i;
        }
        // 使用 critical 确保对共享 sum 的安全更新
#pragma omp critical
        {
            sum += thread_sum;
        }
        // 使用 barrier 确保所有线程到达这里
#pragma omp barrier
        // 使用 master 确保只有主线程打印结果
#pragma omp master
        {
            std::cout << "Total sum from 1 to " << N << " is: " << sum
                      << std::endl;
        }
    }
    return 0;
}

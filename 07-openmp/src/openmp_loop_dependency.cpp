#include <iostream>
#include <omp.h>

int main()
{
    const int N = 10;
    int array[N];

    // 初始化数组
    for (int i = 0; i < N; ++i) {
        array[i] = i;  // array[i] = i
    }

    // 计算结果，当前值依赖于前一个值
    for (int i = 1; i < N; ++i) {
        array[i] = array[i - 1] + 1;  // array[i] 依赖于 array[i - 1]
    }

    // 输出结果
    for (int i = 0; i < N; ++i) {
        std::cout << "array[" << i << "] = " << array[i] << std::endl;
    }

    return 0;
}

#include <iostream>
#include <vector>

#include "lab2.h"

int main()
{
    DynamicArray<int32_t> arr;
    DynamicArray<int32_t> arr1;

    for (int32_t i = 0; i < 10; ++i)
    {
        arr.pushBack(i + 1);
        arr1.pushBack(i);
    }

    for (int32_t i = 0; i < arr.size(); ++i)
    {
        arr[i] *= 2;
    }

    arr = arr1;
    DynamicArray<int32_t> arrMove = std::move(arr1);
    arr.remove(2);

    for (auto it = arr.iterator(); it.hasNext(); it.next())
    {
        std::cout << it.get() << std::endl;
    }

    return 0;
}

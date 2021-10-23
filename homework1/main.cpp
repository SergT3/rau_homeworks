#include <iostream>
#include "Complex.h"

int main()
{
        int n;
        std::cin >> n;
        Complex* arr = new Complex[n];
        for(int i = 0;i < n; ++i)
        {
                std::cin >> arr[i];
        }
        insertionSort(arr, n);

        for(int i = 0;i < n; ++i)
        {
                std::cout << arr[i] << ", ";
        }

        std::cout << std::endl;
        return 0;
}


#include <cassert>
#include <iostream>

// Find the last index of the last duplicate number in a sorted array.
// ex input: 1,2,5,6,6,7,9 output: 4(index)
int lastDuplicate(int* arr, int len)
{
    for(int i = len-1; i >= 1; --i) {
        if(arr[i] == arr[i-1]) {
            return i;
        }
    }

    return -1;
}

int main(int argc, char* argv[])
{
    int a1[] = {1};
    assert(lastDuplicate(a1, 1) == -1);

    int a2[] = {1, 2, 5, 6, 6, 7, 9};
    assert(lastDuplicate(a2, 7) == 4);

    int a3[] = {1, 2, 3, 4};
    assert(lastDuplicate(a3, 4) == -1);

    int a4[] = {1, 1, 2, 4, 5};
    assert(lastDuplicate(a4, 5) == 1);
}

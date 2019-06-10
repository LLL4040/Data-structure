#include <iostream>
using namespace std;

void halfInsertSort(int *array, int length);

int main()
{
    int a[10] = {5, 1, 9, 0, 3, 7, 8, 2, 4, 6};
    halfInsertSort(a, 10);
    for(int i = 0; i < 10; i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}

void halfInsertSort(int *array, int length)
{
    int low, high, middle, index, tmp, i, j;
    for(i = 1; i < length; i++)
    {
        low = 0;
        high = i - 1;
        tmp = array[i];
        index = i;
        if(array[0] < tmp && array[i - 1] > tmp)
        {
            while(low <= high)
            {
                middle = (low + high) / 2;
                if(array[middle] > tmp)
                {
                    high = middle - 1;
                }
                else
                {
                    low = middle + 1;
                }
            }
            index = low;
        }
        if(array[0] >= tmp)
        {
            index = 0;
        }
        if(array[i - 1] <= tmp)
        {
            index = i;
        }
        for(j = i - 1; j >= index; j--)
        {
            array[j + 1] = array[j];
        }
        array[index] = tmp;
    }
}
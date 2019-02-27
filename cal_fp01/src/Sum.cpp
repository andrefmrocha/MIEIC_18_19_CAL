/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>

string calcSum(int* sequence, int size)
{

    int minSum;
    std::pair<int, int> mininums[size];
    int index;
    for(int i = 1; i <= size; i++)
    {
        minSum = 0;
        for(int j = 0; j < i; j++)
            minSum += sequence[j];

        index = 0;
        for(int j = 1; j < size - i + 1; j++)
        {
            int sum = 0;
            for(int k = j; k <= j + i - 1; k++)
            {
                sum += sequence[k];
            }
            if(sum < minSum)
            {
                minSum = sum;
                index = j;
            }

        }
        mininums[i - 1] = make_pair(minSum, index);
    }

    string result;
    for(int i = 0; i < size; i++)
    {
        result+=to_string(mininums[i].first) + "," + to_string(mininums[i].second) + ";";
    }
	return result;
}


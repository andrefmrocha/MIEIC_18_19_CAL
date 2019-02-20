/*
 * Change.cpp
 */

#include "Change.h"
#include <cstring>

string calcChange(int m, int numCoins, int *coinValues)
{
    int minCoins[m + 1];
    minCoins[0] = 0;
    for (int i = 1; i < m + 1; i++)
    {
        minCoins[i] = 2000;
    }
    if( m == 0)
        return "";
    if(m < coinValues[0])
        return "-";
    int lastCoin[m + 1];
    memset(lastCoin, 0, (m+1) * sizeof(int));
    for(int i = 0; i < numCoins; i++)
    {
        for(int k = coinValues[i]; k <= m; k++)
        {
            if( 1 + minCoins[k - coinValues[i]] < minCoins[k])
            {
                minCoins[k] = 1 + minCoins[k - coinValues[i]];
                lastCoin[k] = i;

            }
        }
    }

    string change;
    while (m > 0)
    {
        change += to_string(coinValues[lastCoin[m]]) + ";";
        m -= coinValues[lastCoin[m]];
    }
    return change;
}


/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n)
{
	if(n == 2)
		return 2;
	return n * factorialRecurs(n - 1);

}

int factorialDinam(int n)
{
    int fact = n--;
    for(n; n>=2; n--)
    {
        fact*=n;
    }
	return fact;
}

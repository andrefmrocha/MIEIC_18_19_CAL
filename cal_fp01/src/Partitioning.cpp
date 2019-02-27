/*
 * Partioning.cpp
 */

#include "Partitioning.h"
#include <ctime>


int s_recursive(int n,int k)
{
   if(k == 1 || n == k)
	   return 1;
	return s_recursive(n - 1, k - 1) + k * s_recursive(n - 1, k);
}

int s_dynamic(int n,int k)
{
	vector<int> vec(k, 1);
	for(int i = 0; i < (n - k); i++){
		for(int j = 0; j < k; j++){
			vec[j] = (j + 1) * vec[j] + vec[j - 1];
		}
	}
	return vec[k - 1];
}


int b_recursive(int n)
{
    clock_t time = clock();
	int b = 0;
	for(int i = 1; i <= n; i++){
		b+=s_recursive(n, i);
	}
    cout << (clock() - time) << endl;
    return b;
}

int b_dynamic(int n)
{
    clock_t time = clock();
    int b = 0;
	for(int i = 1; i <= n; i++){
		b+=s_dynamic(n, i);
	}
    cout << (clock() - time) << endl;
    return b;
}



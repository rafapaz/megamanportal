#include "commom.h"

int runNumber(int ini, int min, int max)
{
int k;
    
    k = ini;
    k++;
    if (k > max) return min;
    return k;
}


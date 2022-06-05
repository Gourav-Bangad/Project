#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<string.h>
#include "hashfunc.h"
#include <math.h>


unsigned long hash1(unsigned char *str)
{

    unsigned long hash = 0;
//    int c;

    for(int i = 0;i<strlen(str);i++)
    {
        hash = (str[i]*(pow(7,i))) + hash;
    }
    if(hash<0)
        hash = hash*(-1);
    if(hash>100000)
    {
        hash = hash %100013;
    }
    return hash;
}

unsigned long hash2(unsigned char *str)
{

    unsigned long hash = 0;
    for(int i = 0;i<strlen(str);i++)
    {
        hash = hash*17 + str[i];
    }
    if(hash<0)
        hash = hash*(-1);
    if(hash>100000)
    {
        hash = hash %100013;
    }
    return hash;
}

unsigned long hash3(unsigned char *str, unsigned int i) // combination of hash1 and hash2
{
	return (hash1(str) + i*hash2(str) + i*i)%100013;
}

unsigned long hash4(unsigned char * str)
{
    unsigned hash = 107;
    unsigned long a = 50003;
    for(int i = 0;i<strlen(str);i++)
    {
        hash = hash ^ a;
        hash = hash * str[i];
    }
    if(hash<0)
        hash = hash*(-1);
    if(hash>100000)
    {
        hash = hash %100013;
    }
    return hash;
}

unsigned long hash5(unsigned char *str, unsigned int i) // combination of hash1 and hash2 and hash4
{
	return (hash1(str)*hash2(str) + i*hash4(str))%100013;
}

/*
p = pow(1 - exp(-k / (m / n)), k)
n- no of item   (15000)
p -probabilty of false positve  p = 0.04089
m - number of bits in filter  ( 100000 )
k - no. of hash function   k  = 5 (calculated)
https://hur.st/bloomfilter/?n=15000&p=1.0E-7&m=100000&k=
*/

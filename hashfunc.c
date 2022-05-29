#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<string.h>
#include "hashfunc.h"


unsigned long hash1(unsigned char *str) // djb2
{

    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
    if(hash<0)
        hash = hash*(-1);
    if(hash>25000)
    {
        hash = hash %25013;
    }
    return hash;
}

unsigned long hash2(unsigned char *str) // sdbm
{

    unsigned long hash = 0;
    int c;
    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;
//   printf("%ld ",hash);
    if(hash<0)
        hash = hash*(-1);
    if(hash>25000)
    {
        hash = hash %25013;
    }
    return hash;
}

unsigned long hash3(unsigned char *str) // fnv
{

    const unsigned int fnv_prime = 0x811C9DC5;
    unsigned long hash = 0;
    int c;
    while (c =* (str++))
    {

        hash *= fnv_prime;
        hash ^= (*str);
    }
    if(hash<0)
        hash = hash*(-1);
    if(hash>25000)
    {
        hash = hash %25013;
    }
    return hash;
}

unsigned long hash4 ( const char * str, int len, unsigned int seed )//murmur
{
  const unsigned int m = 0xc6a4a793;

  const int r = 16;

  unsigned int h = seed ^ (len * m);

  const unsigned char * data = (const unsigned char *)str;

  while(len >= 4)
  {
    unsigned int k = *(unsigned int *)data;

    h += k;
    h *= m;
    h ^= h >> 16;

    data += 4;
    len -= 4;
  }

  switch(len)
  {
  case 3:
    h += data[2] << 16;
  case 2:
    h += data[1] << 8;
  case 1:
    h += data[0];
    h *= m;
    h ^= h >> r;
  };

  h *= m;
  h ^= h >> 10;
  h *= m;
  h ^= h >> 17;

  return h % 25013;
}

unsigned long hash5(unsigned char *str, unsigned int i) // combination of sdbm and djb2
{
	return (hash1(str) + i*hash2(str) + i*i)%25013;
}

unsigned long hash6(unsigned char *str, unsigned int i) // combination of fnv and murmur
{
	return (hash3(str) + i*hash4(str,strlen(str),i) + i*i)%25013;
}

unsigned long hash7(unsigned char *str, unsigned int i) // combination of fnv and djb2
{
	return (hash3(str) + i*hash2(str)+ i*i)%25013;
}

unsigned long hash8(unsigned char *str, unsigned int i) // combination of djb2 and murmur
{
	return (hash1(str) + i*hash4(str,strlen(str),i) + i*i)%25013;
}

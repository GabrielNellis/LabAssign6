#include <iostream>
using range = std::pair<int, int>;
using alloc = std::pair<range, int>;
range r;
int size=0; //size of the range
int start=0; //starting address of the range
alloc a;
range allocated; //the range of memory currently allocated from freelist
int leaseExpirey; //time at which this block will be returned to free list
auto [allocated, leaseExpirey] = r;
auto [start, size] = r;
MIN_LEASE = 40;
MAX_LEASE = 70;
MIN_SIZE = 50;
MAX_SIZE = 350;
TIME_LIMIT = 1000;
MEMORY_SIZE = 1000;
REQUEST_INTERVAL = 10;
int main()
{
	long int clock = 0;
	repeat

	until(++clock == TIME_LIMIT);
}
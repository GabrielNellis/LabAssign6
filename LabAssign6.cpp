#ifndef LabAssign6
#define LabAssign6
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
using range = std::pair<int, int>;
using alloc = std::pair<range, int>;
using freelist_t = std::vector<range>;
using alloclist_t = std::vector<alloc>;
#endif LabAssign6
int reqTotal = 0, reqSatis = 0, reqUnsat = 0;
range allocated; //the range of memory currently allocated from freelist
int leaseExpirey; //time at which this block will be returned to freelist
//auto [allocated, leaseExpirey] = a;
//auto [start, size] = r;
freelist_t freeList;
alloclist_t aloccList;
const int MIN_LEASE = 40;
const int MAX_LEASE = 70;
const int MIN_SIZE = 50;
const int MAX_SIZE = 350;
const int TIME_LIMIT = 1000;
//const int MEMORY_SIZE = 1000;
const int REQUEST_INTERVAL = 10;

bool comp(const range& a, const range& b) { //for the starting points of objects in freelist
	return a.first > b.first;
}

bool time(const alloc& a, const alloc& b) { //for the times of objects in alloclist
	return a.second > b.second;
}

void printFree(freelist_t list) {
	for (range e : list) {
		std::cout << e.second << " size starting at " << e.first << " ";
	}
}

void printAlloc(alloclist_t list) {
	for (alloc e : list) {
		//printFree(e.first);

	}
}

bool merge() { //called whenever a request is denied
	bool change = false;
	for (int i = freeList.size()-1; i > 1; i--) { //going through the free list in reverse order (smallest start point to greatest)
		if ((freeList[i].first + freeList[i].second) == freeList[i - 1].first) { //if size+start of current==start of current-1
			freeList[i + 1].first = freeList[i].first; //changing the start to join them
			freeList[i + 1].second += freeList[i].second; //changing the size to equal the size of both
			//have to get rid of freeList[i]
			//can swap freeList[i] with the end, pop, then try to swap it back
			change = true;
		}
	}
	return change;
}

void generateReq() {
	//range r = range((), ()); //first number is the start position, second is the size
	//alloc a = alloc(r, ()); //second number is the time (in ticks) for it to be allocated for
	reqTotal++;
	int size = MIN_SIZE + (rand() % (MAX_SIZE - MIN_SIZE + 1)); //making a number between 50 and 350
	for (range e : freeList) {

	}
}

int main() {
	freeList.push_back(range(0, 1000)); //pushing back all the memory space
	for (long int clock = 0; clock < TIME_LIMIT; clock++) {
		if (clock % REQUEST_INTERVAL == 0) { //should I generate a request?
			generateReq();
			//do I have the space avaliable?
			//for how long do you want it?
			//should I join chunks of memory together as avaliable
			//int i=r.begin()
		}
		//see if a lease has expired (multiple can expire at the same time)
		//check to see if there's any before trying to check if it should expire

	} //track requests made, number satisfied, and number unsatisfied
	//always take the first avaliable chunk
	//use std::sort(begin(), end()) and bool comp(const range&a,const range&b){ return (a.first<b.first); }
}
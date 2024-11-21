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
alloclist_t allocList;
const int MIN_LEASE = 40;
const int MAX_LEASE = 70;
const int MIN_SIZE = 50;
const int MAX_SIZE = 350;
const int TIME_LIMIT = 1000;
const int MEMORY_SIZE = 1000;
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
		//printFree(e.first); //no suitable conversion exists?

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

bool pushReq(int size) {
	bool satis = false;
	for (range e : freeList) {
		if (e.second >= size) {
			int start = e.first; //saving the current value for e.first (since it will be the new start point for the allocated space)
			//if e.second==size, just change the value in free list to alloc list, otherwise segment off a part of freelist to alloclist
			int time = MIN_LEASE + (rand() % (MAX_LEASE - MIN_LEASE + 1)); //number between the min and max lease inclusive
			if (e.second > size) { //if else statement to deal with free list in each scenario, not alloclist
				e.second -= size; //changing the values of freelist (since I don't need to make another range for freeList to push)
				e.first += size;
			}
			else { //e.second==size
				e.second = 0; 
				e.first = -1; //making the start -1 so it'll be pushed to the back by sort to pop it
				std::sort(freeList.begin(), freeList.end()); //may change to bubble sort for efficiency, but it should work
				freeList.pop_back();
			}
			alloc a = alloc(range(start, size), time);
			allocList.push_back(a);
			reqSatis++;
			satis = true;
			break;
		}
	}
	return satis;
}

void generateReq() {
	reqTotal++;
	int size = MIN_SIZE + (rand() % (MAX_SIZE - MIN_SIZE + 1)); //making a number between 50 and 350 inclusive
	bool satis = pushReq(size); //pushReq returns whether the push was successful or not
	if (!satis) { //if the request is not satisfied
		merge();
		satis = pushReq(size); //tries again after merging any adjacent free space
		if (!satis) { //if there's still not enough space, then it can't be fulfilled
			reqUnsat++; //reqSatis is incremented in pushReq if space is avaliable
		}
	}
}

int main() {
	freeList.push_back(range(0, MEMORY_SIZE)); //pushing back all the memory space
	for (long int clock = 0; clock < TIME_LIMIT; clock++) {
		if (!(allocList.empty())) { //checking if it's empty before seeing if any leases expire
			int pop = 0; //for keeping track of how many times allocList needs to be popped (for multiple expiry's at once)
			for (alloc e : allocList) {
				e.second--;
				if (e.second == 0) { //increments a variable to pop as many times as needed to
					freeList.push_back(e.first); //pushing the allocated memory back to the free memory
					pop++;
				}
				else { //do I need to do anything else?

				}
			}
			for (pop; pop > 0; pop--) {
				allocList.pop_back();
			}
		}
		//going to check if a lease has expired, then generate a request to make more space avaliable for requests
		if (clock % REQUEST_INTERVAL == 0) { //should I generate a request?
			generateReq();
		}
		//see if a lease has expired (multiple can expire at the same time)
		//check to see if there's any before trying to check if it should expire

	}
	//use std::sort(begin(), end()) and bool comp(const range&a,const range&b){ return (a.first<b.first); }
}
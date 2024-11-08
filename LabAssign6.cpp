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
int size=0; //size of the range
int start=0; //starting address of the range
range allocated; //the range of memory currently allocated from freelist
int leaseExpirey; //time at which this block will be returned to freelist
//auto [allocated, leaseExpirey] = a;
//auto [start, size] = r;
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

}

void printAlloc(alloclist_t list) {

}

void merge(freelist_t list) { //called whenever a request is denied

}

void generateReq() {
	range r = make_pair(rand(), rand());

}

int main() {
	range r = make_pair(0, MEMORY_SIZE);
	range p = make_pair(make_pair(20, 100), 45);
	freelist_t f;
	int reqTotal = 0, reqSatis = 0, reqUnsat = 0;
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
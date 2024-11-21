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

bool comp(const alloc& a, const alloc& b) { //for the times of objects in alloclist
	return a.second > b.second; 
}

void printFree(freelist_t list) {
	for (range e : list) {
		std::cout << e.second << " size starting at " << e.first << "\n";
	}
}

void printAlloc(alloclist_t list) {
	for (alloc e : list) {
		range r = e.first;
		std::cout << r.second << " allocated size starting at " << r.first << " for " << e.second << " ticks left \n";
	}
}

bool merge() { //called whenever a request is denied
	std::cout << "merging \n";
	bool change = false;
	for (int i = freeList.size()-1; i > 1; i--) { //going through the free list in reverse order (smallest start point to greatest)
		if ((freeList[i].first + freeList[i].second) == freeList[i - 1].first) { //if size+start of current==start of current-1
			freeList[i-1].first = freeList[i].first; //changing the start to join them
			freeList[i-1].second += freeList[i].second; //changing the size to equal the size of both
			freeList[i].first = -1; //making it so that this value will be popped after the list gets sorted
			std::sort(freeList.begin(), freeList.end()); //using for now to get rid of freeList[i]
			freeList.pop_back();
			change = true;
		}
	}
	if (change) {
		std::cout << "merge successful \n";
	}
	return change;
}

bool pushReq(int size) {
	bool satis = false;
	for (int i = 0; i < freeList.size(); i++) {
		if (freeList[i].second >= size) {
			int start = freeList[i].first; //saving the current value for e.first (since it will be the new start point for the allocated space)
			//if e.second==size, just change the value in free list to alloc list, otherwise segment off a part of freelist to alloclist
			int time = MIN_LEASE + (rand() % (MAX_LEASE - MIN_LEASE + 1)); //number between the min and max lease inclusive
			if (freeList[i].second == size) { //if else statement to deal with free list in each scenario, not alloclist
				freeList[i].second = 0; //making the size 0 to clarify that it shouldn't have size
				freeList[i].first = -1; //making the start -1 so it'll be pushed to the back by sort to pop it
				std::sort(freeList.begin(), freeList.end()); //may change to bubble sort for efficiency, but it should work
				freeList.pop_back();
				//std::cout << "went through if ";
			}
			else { //e.second>size
				freeList[i].second -= size; //changing the values of freelist (since I don't need to make another range for freeList to push)
				freeList[i].first += size; //not actually changing freeList
				//std::cout << "went through else ";
			}
			alloc a = alloc(range(start, size), time);
			//std::cout << "start at " << start << " with size " << size << "\n";
			allocList.push_back(a);
			reqSatis++;
			satis = true;
			//printFree(freeList);
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
		//std::cout << "request not initially satisfied \n";
		merge();
		satis = pushReq(size); //tries again after merging any adjacent free space
		if (!satis) { //if there's still not enough space, then it can't be fulfilled
			reqUnsat++; //reqSatis is incremented in pushReq if space is avaliable
			std::cout << "request denied \n";
		}
		else {
			std::cout << "request accepted after inspection \n";
		}
	}
	else {
		std::cout << "request accepted \n";
	}
}

int main() {
	freeList.push_back(range(0, MEMORY_SIZE)); //pushing back all the memory space
	//allocList.push_back(alloc(range(0, 0), 0)); //using this to test if the for loop deletes elements
	for (long int clock = 0; clock < TIME_LIMIT; clock++) { //checking if leases expire before generating a request to make more space for requests
		if (!(allocList.empty())) { //checking if it's empty before seeing if any leases expire
			int pop = 0; //for keeping track of how many times allocList needs to be popped (for multiple expiry's at once)
			for (int i = 0; i < allocList.size(); i++) {
				allocList[i].second--; 
				if (allocList[i].second <= 0) { //increments a variable to pop as many times as needed to
					freeList.push_back(allocList[i].first); //pushing the allocated memory back to the free memory
					pop++;
				}
				//std::cout << e.second << " ";
			}
			std::sort(allocList.begin(), allocList.end()); //sorts the list before popping the elements
			for (pop; pop > 0; pop--) {
				allocList.pop_back(); //never pops the list
			}
		}
		else {
			//std::cout << "list is empty \n";
		}
		if (clock % REQUEST_INTERVAL == 0) { //generates the memory requests
			generateReq();
		}
		//std::cout << "\n";
	}
	std::cout << "free list: \n";
	std::sort(freeList.begin(), freeList.end());
	printFree(freeList);
	std::cout << "allocated list: \n";
	std::sort(allocList.begin(), allocList.end()); //not sorting the times???
	printAlloc(allocList);
	std::cout << "total requests = " << reqTotal << "  successful requests = " << reqSatis << "  failed requests = " << reqUnsat;
	return 0;
}
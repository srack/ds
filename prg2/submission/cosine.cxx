/* Samantha Rack
 * CSE 30331
 * Program 2
 * cosine.cxx
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <cmath>

#include "map.h"
#include "queue.h"

using namespace std;

typedef fightingirish::map<string, int> counter;
typedef fightingirish::priority_queue<pair<string, int> > ranker;

// used to fill up the map with the words and their frequencies
void count_words(istream &is, counter &c) {
	while (!is.eof()) {
		string line, word;
		getline(is, line);
		istringstream ss(line);
		while (ss >> word)
			c[word] += 1;
	}
}

int main(int argc, char *argv[]) {
	// check arguments
	if (argc != 3) {
		cerr << "Usage: ./cosine file1 file2" << endl;
		exit(1);
	}

	// open the two files passed as arguments
	ifstream file1(argv[1]);
	ifstream file2(argv[2]);

	// maps for counting words in files 1 and 2	
	counter count_f1, count_f2;
	count_words(file1, count_f1);
	count_words(file2, count_f2);

	// set up priority queues -- these will be in alphabetical order
	ranker pq1(count_f1.begin(), count_f1.end());
	ranker pq2(count_f2.begin(), count_f2.end());


	/* COSINE CALCULATION */
	//initialize values to 0
	// dot product for the two files
	double dotSum = 0;
	// file 1 distance
	double d_f1 = 0;
	// file 2 distance
	double d_f2 = 0;

	assert (!pq1.empty() && !pq2.empty());

	// loop until one of the priority queues are empty
	// each time through the loop:
	//	compare the string components of the top entries of pq1 and pq2
	//	if equal:	update dotSum, d_f1, and d_f2
	//			pop pq1 & pq2	
	//	if pq1 > pq2:	update d_f1
	//			pop pq1
	//	if pq1 < pq2:	update d_f2
	//			pop pq2

	while (!pq1.empty() && !pq2.empty()) {
		// if the words on top are the same
		if (pq1.top().first == pq2.top().first) {
			dotSum += (pq1.top().second) * (pq2.top().second);
			d_f1 += (pq1.top().second) * (pq1.top().second);
			d_f2 += (pq2.top().second) * (pq2.top().second);
			pq1.pop();
			pq2.pop();
		} 
		else if (pq1.top().first > pq2.top().first) {
			d_f1 += (pq1.top().second) * (pq1.top().second);
			pq1.pop();
		} 
		else {
			d_f2 += (pq2.top().second) * (pq2.top().second);
			pq2.pop();
		}
	}

	
	// finish getting d_f1 or d_f2 (whichever pq isn't empty yet)
	while (!pq1.empty()) {
		d_f1 += (pq1.top().second) * (pq1.top().second);
		pq1.pop();
	}
	while (!pq2.empty()) {
		d_f2 += (pq2.top().second) * (pq2.top().second);
		pq2.pop();
	}


	d_f1 = sqrt(d_f1);
	d_f2 = sqrt(d_f2);

	double result = dotSum / (d_f1 * d_f2);
	cout << result << endl;
	
}

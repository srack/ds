/* Samantha Rack
 * CSE 30331
 * Program 2
 * topwords.cxx
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cstdlib>

#include "map.h"
#include "queue.h"

using namespace std;

//typedef std::map<string, int> counter;
typedef fightingirish::map<string, int> counter;

//typedef std::priority_queue<pair<int, string> > ranker;
typedef fightingirish::priority_queue<pair<int, string> > ranker;

template <typename T, typename U>
pair<U, T> flip (const pair <T, U> p) {
  return make_pair(p.second, p.first);
}

void count_words(istream &is, counter &c) {
  while (!is.eof()) {
    string line, word;
    getline(is, line);
    istringstream ss(line);
    while (ss >> word)
      c[word] += 1;
  }
}

int main (int argc, char *argv[]) {
  if (argc < 2 || argc > 3) {
    cerr << "usage: topwords filename [k]" << endl;
    exit(1);
  }

  string filename(argv[1]);

  int k;
  if (argc == 3) {
    k = atoi(argv[2]);
  } else {
    k = 20;
  }

  ifstream file(filename.c_str());
  counter count;
  count_words(file, count);

  vector<pair<int, string> > v;
  transform(count.begin(), count.end(), back_inserter(v), flip<string, int>);
  ranker pq(v.begin(), v.end());

  for (int i=0; i<k; i++) {
    if (pq.empty()) break;
    cout << pq.top().second << "\t" << pq.top().first << endl;
    pq.pop();
  }
}

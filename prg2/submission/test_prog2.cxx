#include <string>
#include <iostream>
#include <cstdlib>

#include <map>
#include <queue>

#include "map.h"
#include "queue.h"

using namespace std;

typedef fightingirish::map<string, int> string_counter;
typedef fightingirish::map<int, int> int_counter;
typedef std::map<int, int> std_int_counter;
typedef fightingirish::priority_queue<int> int_heap;
typedef std::priority_queue<int> std_int_heap;

template <typename T>
void test_equal(const T& x, const T& y) {
  cout << x << " == " << y << ":\t";
  cout << (x == y ? "PASSED" : "FAILED") << endl;
}

int main (int argc, char *argv[]) {
  cout << "==== testing map<string,int> ====" << endl;
  string_counter c;
  test_equal(c["foo"], 0);
  c["foo"] += 1;
  test_equal(c["foo"], 1);
  c["bar"] += 1;
  test_equal(c["bar"], 1);
  c["foo"] += 1;
  test_equal(c["foo"], 2);

  cout << "==== large-scale random test of map<int,int> ====" << endl;

  int_counter ic;
  std_int_counter sic;
  for (int i=0; i<1000000; i++) {
    int r = rand() % 100000;
    ic[r] += 1;
    sic[r] += 1;
  }

  for (std_int_counter::iterator it=sic.begin(); it != sic.end(); ++it) {
    if (rand() % 10000 == 0)
      test_equal(ic[it->first], it->second);
  }

  cout << " ==== testing priority_queue<int> ====" << endl;
  int_heap ih;
  test_equal(ih.empty(), true);
  ih.push(42);
  test_equal(ih.empty(), false);
  ih.push(123);
  ih.push(1);
  test_equal(ih.top(), 123);
  ih.pop();
  test_equal(ih.top(), 42);
  ih.pop();
  test_equal(ih.top(), 1);
  ih.pop();
  test_equal(ih.empty(), true);
  
  cout << " ==== large-scale random test of priority_queue<int> ====" << endl;
  std_int_heap sih;
  for (int i=0; i<1000000; i++) {
    if (rand() % 3 > 0) {
      int r = rand();
      sih.push(r);
      ih.push(r);
    } else if (!sih.empty()) {
      sih.pop();
      ih.pop();
    }
    if (rand() % 100000 == 0 && !sih.empty()) {
      test_equal(ih.top(), sih.top());
    }
  }

}

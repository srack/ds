/* Samantha Rack
 * CSE 30331 Program 1
 * ccalc.cxx
 * This class contains the main function using the templated stack
 * class to implement a calculator using complex numbers.
 */

#include <iostream>
#include <string>
#include <stack>

#include <cstdlib>
#include <unistd.h>
#include <math.h>
#include <complex>

#include "stack.h"

using namespace std;

#if defined USE_STD_STACK
typedef std::stack<double> number_stack;
#elif defined USE_MY_STACK
typedef fightingirish::stack number_stack;
#elif defined USE_MY_STACK_TEMPLATE
typedef fightingirish::stack< complex<double> > number_stack;
#endif

const bool interactive = isatty(0);
int linenum = 0;

void error (const char *s) {
	if (interactive) {
		cout << "error: " << s << endl;
	} else {
		cerr << "error: " << s << " on line " << linenum << endl;
	}
}

template <typename Stack, typename T>
int pop2 (Stack &stk, T &x, T &y) {
	if (stk.empty()) {
		error("stack underflow");
		return 1;
	}
	y = stk.top(); stk.pop();

	if (stk.empty()) {
		error("stack underflow");
		return 1;
	}
	x = stk.top(); stk.pop();

	return 0;
}

template <typename Stack, typename T>
int sqrt (Stack &stk, T &x) {
//returns 1 on error, 0 on success
	if (stk.empty()) {
		error("stack underflow");
		return 1;
	}
	T radicand = stk.top();
	stk.pop();
	x = sqrt(radicand);
	
	return 0;	
}
	

int main (int argc, char *argv[]) {
	string s;
	number_stack stk;
	char *end;
	complex<double> x, y;

	while (!cin.eof()) {
		if (!stk.empty())
			cout << stk.top() << endl;

		if (interactive) cout << "> ";
		getline(cin, s);
		linenum++;

		x = strtod(s.c_str(), &end);
		if (*end == '\0') {
			stk.push(x);
		} else if (s == "+") {
			if (pop2(stk, x, y) == 0) {
				stk.push(x + y);
			}
		} else if (s == "-") {
			if (pop2(stk, x, y) == 0) {
				stk.push(x - y);
			}
		} else if (s == "*") {
			if (pop2(stk, x, y) == 0) {
				stk.push(x * y);
			}
		} else if (s == "/") {
			if (stk.top() == 0.0) {
				error("division by zero");
			} else if (pop2(stk, x, y) == 0) {
				stk.push(x / y);
	      		}
		} else if (s == "drop") {
			if (!stk.empty()) {
				stk.pop();
			} else {
				error("stack underflow");
			}
		} else if ( s == "sqrt") {
			if(sqrt(stk, x) == 0) {
				stk.push(x);
			}
		} else {
			error("couldn't understand input");
		}
	}
}

#include <iostream>
#include "deque.h"
using namespace std;

int main() {
    Deque<int> dq;

    // Stress test for push and pop
    for (int i = 0; i < 1000; ++i) {
        dq.push_back(i);
        dq.push_front(-i);
    }

    for (int i = 0; i < 500; ++i) {
        dq.pop_back();
        dq.pop_front();
    }

    // Access elements using []
    try {
        for (size_t i = 0; i < dq.size(); ++i)
	  cout << dq[i] << " ";
	cout <<endl;
    } catch (out_of_range& e) {
        cerr << e.what() << endl;
    }

    return 0;
}

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "deque.h"

using namespace std;

int main() {
    // Perform test based on the user input
    int choice;

    while (true) {
        // Display menu
        cout << "\nDeque Operations Menu:\n";
        cout << "1. Test edge cases (push, pop, empty check)\n";
        cout << "2. Perform push and pop stress test\n";
        cout << "3. Test random access with large number of elements\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            // Test edge cases
            Deque<int> dq;
            dq.push_back(1);
            dq.push_back(2);
            dq.push_front(0);
            dq.push_front(-1);
            cout << dq.front() << " " << dq.back() << endl;
            dq.pop_front();
            dq.pop_back();
            cout << dq.front() << " " << dq.back() << endl;
        } else if (choice == 2) {
            // Stress test push and pop
            Deque<int> dq;
            for (int i = 0; i < 1000; ++i) {
                dq.push_back(i);
                dq.push_front(-i);
            }
            for (int i = 0; i < 500; ++i) {
                dq.pop_back();
                dq.pop_front();
            }
        } else if (choice == 3) {
            // Test random access
            Deque<int> dq;
            for (int i = 0; i < 10000; ++i) {
                dq.push_back(i);
            }
            for (int i = 0; i < 1000; ++i) {
                int index = rand() % dq.size();
                try {
                    cout << "accessing index " << index << ": " << dq[index] << " ";
                } catch (const out_of_range& e) {
                    cerr << "out of range error while accessing index: " << e.what() << endl;
                }
            }
            cout << endl;
        } else if (choice == 4) {
            break;  // Exit
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}

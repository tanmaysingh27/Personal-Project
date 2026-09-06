#include "mylib/Stack/Stack.hpp" 
#include <iostream>
using namespace std;

int main() {
    myLib::Stack<int> s(2);  

    for (int i = 1; i <= 6; i++) {
        s.push(i * 10);
        cout << "Pushed " << i * 10 << " | top: " << s.peek() << endl;
    }

    cout << "\n--- Testing copy ---" << endl;
    auto s2 = s;
    cout << "s2 top: " << s2.peek() << endl;

    cout << "\n--- Testing exceptions ---" << endl;
    myLib::Stack<int> empty(3);
    try {
        empty.pop();
    }
    catch (const std::out_of_range& e) {
        cout << "Caught: " << e.what() << endl;
    }
}
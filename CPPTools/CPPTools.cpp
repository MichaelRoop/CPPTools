// CPPTools.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//https://www.quora.com/Are-there-any-ways-to-simulate-or-implement-interfaces-in-C++-other-than-using-pure-virtual-methods
struct Process1 {
    void DoIt(int i) {
        std::cout << "Process 1 = " << i << std::endl;
    }
};

struct Process2 {
    void DoIt(int i) {
        std::cout << "Process 2 = " << i << std::endl;
    }
};

// Sample of building a non inherited class with different
// functionality that you would normally do with inheritance. 
// No overhead. Compile time check on existence of method
template<typename ProcessType>
class Processor {
public:
    void Process(int i) {
        p.DoIt(i);
    }

private:
    ProcessType p;
};



int main()
{
    std::cout << "Hello World!\n";

    Processor<Process1> p1;
    Processor<Process2> p2;
    p1.Process(2334);
    p2.Process(1009);


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

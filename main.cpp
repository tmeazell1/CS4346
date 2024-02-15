#include <iostream>
#include "backwardchaining.cpp"
#include "forwardchaining.cpp"

using namespace std;

int main() {
    // Backward chaining
    cout << "Backward chaining" << endl;
    BC_main();

    // Forward chaining
    cout << "Forward chaining" << endl;
    FC_main();

    return 0;
}
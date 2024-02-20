#include <iostream>
#include "backwardchaining.cpp"
#include "forwardchaining.cpp"

using namespace std;

int main() {
    // Backward chaining
    cout << "Backward chaining" << endl;
    BC_main();
    ATTACK = getAttack();

    // Forward chaining
    cout << "Forward chaining" << endl;
    FC_main(ATTACK);

    cout << "Analysis complete, goodbye!" << endl;

    return 0;
}
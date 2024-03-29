#include <iostream>
#include "backwardchaining.cpp"
#include "forwardchaining.cpp"

using namespace std;

int main() {
    // Backward chaining
    cout << "Backward chaining" << endl;
    BC_main();
    string m_ATTACK = getAttack();

    // Forward chaining
    cout << "Forward chaining" << endl;
    FC_main(m_ATTACK);

    cout << "Analysis complete, goodbye!" << endl;

    return 0;
}
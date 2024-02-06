#include <iostream>
#include <vector>

// Global data structures
std::vector<std::string> rules;  // List of rules
std::vector<std::string> variableList;  // Variable list
std::vector<std::string> conclusionList;  // Conclusion list
std::vector<std::string> derivedGlobalVariableList;  // Derived global variable list

// Function prototypes
int search_con(std::string variable);
int rule_to_clause(int ruleNumber);
void update_VL(int clauseNumber);
void validate_Ri(int ruleNumber, std::string& conclusion);
void process(std::string goalVariable);

// Backward chaining function
void backwardChaining(std::string goalVariable) {
    // Call Process(Goal variable)
    process(goalVariable);

    // After the program is complete, check if the derived global variable list contains Goal variable
    // and it is not null. If it does, print the value of the variable.
    // Pass it to the Forward chaining program if it's not null. If it is null, print a comment that Goal cannot be determined.
    // ...
}

// Process function for backward chaining
void process(std::string goalVariable) {
    // Start a loop. In each cycle of the loop, do the following:
    while (true) {
        // Call search_con(variable) with passing the goal variable as a parameter
        int ruleNumber = search_con(goalVariable);
        
        // Call rule_to_clause(Ri) with passing Ri as a parameter
        int clauseNumber = rule_to_clause(ruleNumber);

        // Call update_VL(Ci) with passing Ci to it
        update_VL(clauseNumber);

        // Initialize conclusion to null
        std::string conclusion;

        // Call validate_Ri(Ri, Conclusion) with passing Ri to it
        validate_Ri(ruleNumber, conclusion);

        // Save the value of the conclusion variable in the derived global variable list
        if (!conclusion.empty()) {
            derivedGlobalVariableList.push_back(conclusion);
            return;
        }
        
        // If the values of the variables in the ‘if’ clauses of the rule are not satisfied,
        // use ‘continue’ statement to continue the loop.
        // Repeat the process with the next entry of the conclusion list.
    }
}

// Other function definitions (search_con, rule_to_clause, update_VL, validate_Ri)...

// Main function
int main() {
    // Declare variables and arrays
    // ...

    // Identify the Goal variable (the variable whose value needs to be determined)
    std::string goalVariable;
    // ...

    // Call Backward Chaining function
    backwardChaining(goalVariable);

    // Check if the derived global variable list contains Goal variable and it is not null
    // If it does, print the value of the variable and pass it to the Forward chaining program
    // If it is null, print a comment that Goal cannot be determined.
    // ...

    return 0;
}

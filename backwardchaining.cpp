#include <iostream>
#include <string>

using namespace std;


//TODO: change # of elements in each array to be appropriate for our data
const int CONCLUSION_LIST_SIZE = 10;
const int VAR_LIST_SIZE = 10;
const int CLAUSE_VAR_LIST_SIZE = 40;

string conclusionList[CONCLUSION_LIST_SIZE];
string varList[VAR_LIST_SIZE];
string clauseVarList[CLAUSE_VAR_LIST_SIZE];

string variable;
//TODO: change these variables to match variable list in lists.txt
string qu, de, di, po;
string buff;
//new strings
string problem, traffic, pattern, emails, database, scripts, intercept, ransom, dnsrequests, vulnerablilties;

// Instantiated list
int instantiatedList[11];

// Statement stack
int statementStack[11];

// Clause stack
int clauseStack[11];

int sn, f, i, j, s, k, /*stack pointer */ sp;

//TODO: remove these, we don;t have any floating point data
// Grade and experience
float gr, ex;

// Function prototypes
void determine_member_concl_list();
void push_on_stack();
void instantiate();

int main() {
    // Initialization section
    //TODO: change stack pointer to be appropriate for our data 
    sp = 11;

    for (int i = 1; i < 11; i++) {//TODO: change # of iterations to appropriate for our data
        // Initialize arrays
        conclusionList[i] = "";
        varList[i] = "";
        instantiatedList[i] = 0;
        statementStack[i] = 0;
        clauseStack[i] = 0;
    }

    for (int i = 1; i < 41; i++) { //TODO: change # of iterations to appropriate for our data
        // Initialize clause variable list
        clauseVarList[i] = "";
    }

    //TODO: Enter conclusions from lists.txt
    conclusionList[1] = "PO";
    conclusionList[2] = "QU";
    conclusionList[3] = "PO";
    conclusionList[4] = "PO";
    conclusionList[5] = "PO";
    conclusionList[6] = "PO";

    cout << "*** CONCLUSION LIST ***" << endl;
    for (int i = 1; i < 11; i++) { //TODO: change # of iterations to appropriate for our data
        cout << "CONCLUSION " << i << " " << conclusionList[i] << endl;
    }
    cout << "HIT RETURN TO CONTINUE";
    getline(cin, buff);

    //TODO: Enter variables from lists.txt
    varList[1] = "DE";
    varList[2] = "DI";
    varList[3] = "EX";
    varList[4] = "GR";

    cout << "*** VARIABLE LIST ***" << endl;
    for (int i = 1; i < 11; i++) {//TODO: change # of iterations to appropriate for our data
        cout << "VARIABLE " << i << " " << varList[i] << endl;
    }
    cout << "HIT RETURN KEY TO CONTINUE";
    getline(cin, buff);

    //TODO: Enter clause variables from lists.txt
    clauseVarList[1] = "DE";
    clauseVarList[5] = "DE";
    clauseVarList[9] = "DE";
    clauseVarList[10] = "DI";
    clauseVarList[13] = "QU";
    clauseVarList[14] = "GR";
    clauseVarList[15] = "EX";
    clauseVarList[17] = "QU";
    clauseVarList[18] = "GR";
    clauseVarList[19] = "EX";
    clauseVarList[21] = "QU";
    clauseVarList[22] = "GR";

    for (int i = 1; i < 9; i++) { //TODO: change # of iterations to appropriate for our data
        cout << "** CLAUSE " << i << endl;
        for (int j = 1; j < 5; j++) {
            int k = 4 * (i - 1) + j;
            cout << "VARIABLE " << j << " " << clauseVarList[k] << endl;
        }
        if (i == 4) {
            cout << "HIT RETURN KEY TO CONTINUE";
            getline(cin, buff);
        }
    }

    // Inference section
    cout << "** ENTER CONCLUSION ? "; //I think here the user is expected to enter "attack" ie the goal is identify the attack
    getline(cin, variable);

    // Get conclusion statement number (sn) from the conclusion list (conclusionList)
    // First statement starts search
    b520:
    int f = 1;
    determine_member_concl_list();

    if (sn != 0) {
        do {
            // Push statement number (sn) and clause number=1 on goal stack
            push_on_stack();

            do {/* calculate clause location in clause-variable list */
            b545:
                int i = (statementStack[sp] - 1) * 4 + clauseStack[sp];
                variable = clauseVarList[i];

                if (variable != "") {
                    f = 1;
                    determine_member_concl_list();

                    if (sn != 0)
                        goto b520;

                    instantiate();
                    clauseStack[sp]++;
                }
            } while (variable != "");

            sn = statementStack[sp];
            int s = 0;

            // If-then statements
            switch (sn) { //TODO: modify this to represent our knowledge base
                case 1: if (de == "NO") s = 1; break;
                case 2: if (de == "YES") s = 1; break;
                case 3: if (de == "YES" && di == "YES") s = 1; break;
                case 4: if (qu == "YES" && gr < 3.5 && ex >= 2) s = 1; break;
                case 5: if (qu == "YES" && gr < 3 && ex < 2) s = 1; break;
                case 6: if (qu == "YES" && gr >= 3.5) s = 1; break;

            }

            if (s != 1) {
                int i = statementStack[sp];
                variable = conclusionList[i];
                f = statementStack[sp] + 1;
                determine_member_concl_list();
                sp++;
            }

        } while (s != 1 && sn != 0);

        if (sn != 0) {
            switch (sn) { //TODO: modify this to represent our knowledge base
                case 1: po = "NO"; cout << "PO=NO" << endl; break;
                case 2: qu = "YES"; cout << "QU=YES" << endl; break;
                case 3: po = "YES"; cout << "PO=RESEARCH" << endl; break;
                case 4: po = "YES"; cout << "PO=SERVICE ENGINEER" << endl; break;
                case 5: po = "NO"; cout << "PO=NO" << endl; break;
                case 6: po = "YES"; cout << "PO=PRODUCT ENGINEER" << endl; break;
            }

            sp++;
            if (sp >= 11) //TODO: modify this number to work for our data
                cout << "*** SUCCESS" << endl;
            else {
                clauseStack[sp]++;
                goto b545;
            }
        }
    }

    return 0;
}

// Routine to determine if a variable (variable) is a member of the conclusion list (conclusionList)
// If yes, return sn != 0. If not a member, sn = 0.
void determine_member_concl_list() {
    sn = 0;
    int i = f;

    while (variable != conclusionList[i] && i < 8)
        i++;

    if (variable == conclusionList[i]) sn = i; // A member
}

// Routine to push statement number (sn) and a clause number of 1 onto the conclusion stack
// Decrements stack pointer (sp)
void push_on_stack() {
    sp--;
    statementStack[sp] = sn;
    clauseStack[sp] = 1;
}

// Routine to instantiate a variable (variable) if it isn't already instantiated
// Instantiate indication (instantiatedList) is 0 if not, 1 if it is. Variable list (varList) contains the variable (variable).
void instantiate() {
    int i = 1;

    while (variable != varList[i] && i < 10) //TODO: modify loop iterations to work for our data
        i++;

    if (variable == varList[i] && instantiatedList[i] != 1) {
        instantiatedList[i] = 1; // Mark instantiated

        // Input statements for sample position knowledge base
        switch (i) { //TODO: modify this to get user inputs for each variable in the variable list from lists.txt
            case 1: cout << "INPUT YES OR NO FOR DE-? "; getline(cin, de); break;
            case 2: cout << "INPUT YES OR NO FOR DI-? "; getline(cin, di); break;
            case 3: cout << "INPUT A REAL NUMBER FOR EX-? "; cin >> ex; break;
            case 4: cout << "INPUT A REAL NUMBER FOR GR-? "; cin >> gr; break;
        }
    }
}


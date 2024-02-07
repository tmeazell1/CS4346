#include <iostream>
#include <string>

using namespace std;

// Conclusion list
string conclt[10];

// Variable list
string varlt[10];

// Clause variable list
string clvarlt[40];

string varble;
string qu, de, di, po;
string buff;

// Instantiated list
int instlt[11];

// Statement stack
int statsk[11];

// Clause stack
int clausk[11];

int sn, f, i, j, s, k, /*stack pointer */ sp;

// Grade and experience
float gr, ex;

// Function prototypes
void determine_member_concl_list();
void push_on_stack();
void instantiate();

int main() {
    // Initialization section
    sp = 11;

    for (int i = 1; i < 11; i++) {
        // Initialize arrays
        conclt[i] = "";
        varlt[i] = "";
        instlt[i] = 0;
        statsk[i] = 0;
        clausk[i] = 0;
    }

    for (int i = 1; i < 41; i++) {
        // Initialize clause variable list
        clvarlt[i] = "";
    }

    // Enter conclusions
    conclt[1] = "PO";
    conclt[2] = "QU";
    conclt[3] = "PO";
    conclt[4] = "PO";
    conclt[5] = "PO";
    conclt[6] = "PO";

    cout << "*** CONCLUSION LIST ***" << endl;
    for (int i = 1; i < 11; i++) {
        cout << "CONCLUSION " << i << " " << conclt[i] << endl;
    }
    cout << "HIT RETURN TO CONTINUE";
    getline(cin, buff);

    // Enter variables
    varlt[1] = "DE";
    varlt[2] = "DI";
    varlt[3] = "EX";
    varlt[4] = "GR";

    cout << "*** VARIABLE LIST ***" << endl;
    for (int i = 1; i < 11; i++) {
        cout << "VARIABLE " << i << " " << varlt[i] << endl;
    }
    cout << "HIT RETURN KEY TO CONTINUE";
    getline(cin, buff);

    // Enter clause variables
    clvarlt[1] = "DE";
    clvarlt[5] = "DE";
    clvarlt[9] = "DE";
    clvarlt[10] = "DI";
    clvarlt[13] = "QU";
    clvarlt[14] = "GR";
    clvarlt[15] = "EX";
    clvarlt[17] = "QU";
    clvarlt[18] = "GR";
    clvarlt[19] = "EX";
    clvarlt[21] = "QU";
    clvarlt[22] = "GR";

    for (int i = 1; i < 9; i++) {
        cout << "** CLAUSE " << i << endl;
        for (int j = 1; j < 5; j++) {
            int k = 4 * (i - 1) + j;
            cout << "VARIABLE " << j << " " << clvarlt[k] << endl;
        }
        if (i == 4) {
            cout << "HIT RETURN KEY TO CONTINUE";
            getline(cin, buff);
        }
    }

    // Inference section
    cout << "** ENTER CONCLUSION ? ";
    getline(cin, varble);

    // Get conclusion statement number (sn) from the conclusion list (conclt)
    // First statement starts search
    int f = 1;
    determine_member_concl_list();

    if (sn != 0) {
        do {
            // Push statement number (sn) and clause number=1 on goal stack
            push_on_stack();

            do {
                int i = (statsk[sp] - 1) * 4 + clausk[sp];
                varble = clvarlt[i];

                if (varble != "") {
                    f = 1;
                    determine_member_concl_list();

                    if (sn != 0)
                        goto b520;

                    instantiate();
                    clausk[sp]++;
                }
            } while (varble != "");

            sn = statsk[sp];
            int s = 0;

            // If-then statements
            switch (sn) {
                case 1: if (de == "NO") s = 1; break;
                case 2: if (de == "YES") s = 1; break;
                case 3: if (de == "YES" && di == "YES") s = 1; break;
                case 4: if (qu == "YES" && gr < 3.5 && ex >= 2) s = 1; break;
                case 5: if (qu == "YES" && gr < 3 && ex < 2) s = 1; break;
                case 6: if (qu == "YES" && gr >= 3.5) s = 1; break;
            }

            if (s != 1) {
                int i = statsk[sp];
                varble = conclt[i];
                f = statsk[sp] + 1;
                determine_member_concl_list();
                sp++;
            }

        } while (s != 1 && sn != 0);

        if (sn != 0) {
            switch (sn) {
                case 1: po = "NO"; cout << "PO=NO" << endl; break;
                case 2: qu = "YES"; cout << "QU=YES" << endl; break;
                case 3: po = "YES"; cout << "PO=RESEARCH" << endl; break;
                case 4: po = "YES"; cout << "PO=SERVICE ENGINEER" << endl; break;
                case 5: po = "NO"; cout << "PO=NO" << endl; break;
                case 6: po = "YES"; cout << "PO=PRODUCT ENGINEER" << endl; break;
            }

            sp++;
            if (sp >= 11)
                cout << "*** SUCCESS" << endl;
            else {
                clausk[sp]++;
                goto b545;
            }
        }
    }

    return 0;
}

// Routine to determine if a variable (varble) is a member of the conclusion list (conclt)
// If yes, return sn != 0. If not a member, sn = 0.
void determine_member_concl_list() {
    sn = 0;
    int i = f;

    while (varble != conclt[i] && i < 8)
        i++;

    if (varble == conclt[i]) sn = i; // A member
}

// Routine to push statement number (sn) and a clause number of 1 onto the conclusion stack
// Decrements stack pointer (sp)
void push_on_stack() {
    sp--;
    statsk[sp] = sn;
    clausk[sp] = 1;
}

// Routine to instantiate a variable (varble) if it isn't already instantiated
// Instantiate indication (instlt) is 0 if not, 1 if it is. Variable list (varlt) contains the variable (varble).
void instantiate() {
    int i = 1;

    while (varble != varlt[i] && i < 10)
        i++;

    if (varble == varlt[i] && instlt[i] != 1) {
        instlt[i] = 1; // Mark instantiated

        // Input statements for sample position knowledge base
        switch (i) {
            case 1: cout << "INPUT YES OR NO FOR DE-? "; getline(cin, de); break;
            case 2: cout << "INPUT YES OR NO FOR DI-? "; getline(cin, di); break;
            case 3: cout << "INPUT A REAL NUMBER FOR EX-? "; cin >> ex; break;
            case 4: cout << "INPUT A REAL NUMBER FOR GR-? "; cin >> gr; break;
        }
    }
}


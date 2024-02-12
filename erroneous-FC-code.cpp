#include <iostream>
#include <string>

using namespace std;

int flag;
string cndvar[10];
string varlt[10], clvarlt[40]; // Variable lists
string c, vp, v; // Condition variables
string fedint, interest, stock, dollar, fedmon;
string po, qu; // Conclusion variables
int instlt[10]; // Instantiated list
//TODO: remove unnecesarily global variables such as loop counters
int f, i, j, k, s, fp, bp, gr, sn, cn; // Pointers and counters 

// Function prototypes
void search();
void check_instantiation();
void instantiate();

int main() {
    // Initialization section
    fp = 1;
    bp = 1;

    for (i = 1; i < 41; i++)
        clvarlt[i] = "";

    for (i = 1; i < 11; i++) {
        cndvar[i] = "";
        instlt[i] = 0;
        varlt[i] = "";
    }

    // Enter variables in the IF part
    varlt[1] = "DO";
    varlt[2] = "FT";
    varlt[3] = "FM";
    varlt[4] = "IN";
    varlt[5] = "ST";

    cout << "*** VARIABLE LIST ***" << endl;
    for (i = 1; i < 11; i++)
        cout << "ENTER VARIABLE " << i << " " << varlt[i] << endl;

    cout << "HIT RETURN TO CONTINUE";
    getchar();

    // Enter variables as they appear in the IF clauses
    clvarlt[1] = "IN";
    clvarlt[5] = "IN";
    clvarlt[9] = "DO";
    clvarlt[13] = "DO";
    clvarlt[17] = "FT";
    clvarlt[18] = "FM";

    cout << "*** CLAUSE-VARIABLE LIST ***" << endl;
    for (i = 1; i < 9; i++) {
        cout << "** CLAUSE " << i << endl;
        for (j = 1; j < 5; j++) {
            k = 4 * (i - 1) + j;
            cout << "VARIABLE " << j << " " << clvarlt[k] << endl;
        }
        if (i == 4) {
            cout << "HIT RETURN TO CONTINUE";
            getchar();
        }
    }

    // Inference section
    cout << "ENTER CONDITION VARIABLE? ";
    getline(cin, c);

    // Place condition variable c on the condition variable queue cndvar
    cndvar[bp] = c;
    bp++;

    // Set the condition variable pointer
    sn = 1;
    cn = 1;

    // Find the next statement number containing the condition variable
    // which is in front of the queue (cndvar), this statement number
    // is located in the clause variable list (clvarlt)
    f = 1;

    while (sn != 0) {
        search();

        cn = 1;
        if (sn != 0) {
            i = 4 * (sn - 1) + cn;

            while (!clvarlt[i].empty()) { // are there any more clauses for this statement?
                check_instantiation();
                cn++;
                i = 4 * (sn - 1) + cn;
            }
            /* no more clauses - check IF part of statement */
            s = 0;

            switch (sn) {
                case 1: if (interest == "FALL") s = 1; break;
                case 2: if (interest == "RISE") s = 1; break;
                case 3: if (dollar == "FALL") s = 1; break;
                case 4: if (dollar == "RISE") s = 1; break;
                case 5: if (fedint == "FALL" && fedmon == "ADD") s = 1; break;
                case 6: if (qu == "YES" && gr >= 3.5) s = 1; break;
            }
            /* see if the THEN part should be inovked, i.e., s=1 */
            if (s != 1) {
                f = sn + 1;
                continue;
            }

            switch (sn) {
                case 1: stock = "RISE"; cout << "ST=RISE" << endl; v = "ST"; instantiate(); break;
                case 2: stock = "FALL"; cout << "ST=FALL" << endl; v = "ST"; instantiate(); break;
                case 3: interest = "RISE"; cout << "IN=RISE" << endl; v = "IN"; instantiate(); break;
                case 4: interest = "FALL"; cout << "IN=FALL" << endl; v = "IN"; instantiate(); break;
                case 5: interest = "FALL"; cout << "IN=FALL" << endl; v = "IN"; instantiate(); break;
                case 6: po = "YES"; cout << "PO=YES" << endl; break;
            }

            f = sn + 1;
        }

        // No more clauses in the clause variable list (clvarlt) containing the variable
        // in front of the conclusion queue (cndvar(fp))
        // Remove front variable (cndvar(fp)) and replace it by the next variable (cndvar(fp+1))
        if (fp < bp) {
            fp++;
            f = 1;
        }
    }

    return 0;
}

// Function to instantiate a variable (v) if it isn't already instantiated
void check_instantiation() {
    i = 1;

    while (v != varlt[i] && i <= 10)
        i++;

    if (instlt[i] != 1) {
        instlt[i] = 1;

        switch (i) {
            case 1: cout << "RISE OR FALL FOR DO? "; getline(cin, dollar); break;
            case 2: cout << "RISE OR FALL FOR FT? "; getline(cin, fedint); break;
            case 3: cout << "ADD OR SUBTRACT FOR FM? "; getline(cin, fedmon); break;
            case 4: cout << "RISE OR FALL FOR IN? "; getline(cin, interest); break;
            case 5: cout << "RISE OR FALL FOR ST? "; getline(cin, stock); break;
        }
    }
}

// Function to search the clause variable list for a variable (clvarlt)
int search() {
    flag = 0;
    sn = f;

    while (flag == 0 && sn <= 10) {
        cn = 1;
        k = (sn - 1) * 4 + cn;

        while (clvarlt[k] != cndvar[fp] && cn < 4) {
            cn++;
            k = (sn - 1) * 4 + cn;
        }

        if (clvarlt[k] == cndvar[fp])
            flag = 1;

        if (flag == 0)
            sn++;
    }

    if (flag == 0)
        sn = 0;

    return sn;
}

// Function to instantiate a variable (v) and place it on the back of the queue (cndvar[bp])
void instantiate() {
    i = 1;

    while (v != varlt[i] && i <= 10)
        i++;

    instlt[i] = 1;
    i = 1;

    while (v != cndvar[i] && i <= 10)
        i++;

    if (v != cndvar[i]) {
        cndvar[bp] = v;
        bp++;
    }
}

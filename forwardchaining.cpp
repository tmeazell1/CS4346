#include <iostream>
#include <string>

using namespace std;

int flag;
string conditionVar[10]; //condition variable
string varList[10], clauseVarList[40]; // Variable list and clause variable list //TODO change these to appropriate lengths
string c, vp, v; // Condition variables
string fedint, interest, stock, dollar, fedmon; //TODO use the variable from FC lists.txt
string po, qu; // Conclusion variables TODO change these to conclusions from FC lists
int instlt[10]; // Instantiated list (for instantiated variables)
//TODO: remove unnecesarily global variables such as loop counters
int f, i, j, k, s, fp, bp, gr, sn, cn; // Pointers and counters 

// Function prototypes
void search();
void check_instantiation();
void instantiate();

int main() {
    // Initialization section
    fp = 1; //front pointer
    bp = 1; //back pointer

    for (i = 1; i < 41; i++)
        clauseVarList[i] = "";

    for (i = 1; i < 11; i++) {
        conditionVar[i] = "";
        instlt[i] = 0;
        varList[i] = "";
    }

    // Enter variables in the IF part
    //TODO change this to match variable list from FC lists.txt
    varList[1] = "PROBLEM";
    varList[2] = "TRAFFIC";
    varList[3] = "PATTERN";
    varList[4] = "EMAILS";
    varList[5] = "DATABASE";
    varList[6] = "SCRIPTS";
    varList[7] = "INTERCEPT";
    varList[8] = "RANSOM";
    varList[9] = "DNSREQUESTS";
    varList[10] = "VULNERABILITIES";

    cout << "*** VARIABLE LIST ***" << endl; //we only have one variable. It seems like we need to get the variable from the BC function?
    for (i = 1; i < 11; i++)
        cout << "ENTER VARIABLE " << i << " " << varList[i] << endl;

    cout << "HIT RETURN TO CONTINUE";
    getchar();

    // Enter variables as they appear in the IF clauses
    //TODO make this match the clause variable list from FC lists.txt
    clauseVarList[1] = "PROBLEM";
    clauseVarList[5] = "PROBLEM";
    clauseVarList[6] = "ATTACK";
    clauseVarList[9] = "PROBLEM";
    clauseVarList[10] = "ATTACK";
    clauseVarList[13] = "PROBELM";
    clauseVarList[14] = "ATTACK";
    clauseVarList[17] = "PROBLEM";
    clauseVarList[18] = "ATTACK";
    clauseVarList[21] = "PROBLEM";
    clauseVarList[22] = "ATTACK";
    clauseVarList[25] = "PROBLEM";
    clauseVarList[26] = "ATTACK";
    clauseVarList[29] = "PROBLEM";
    clauseVarList[30] = "ATTACK";
    clauseVarList[33] = "PROBLEM";
    clauseVarList[34] = "ATTACK";
    clauseVarList[37] = "PROBLEM";
    clauseVarList[38] = "ATTACK";

    cout << "*** CLAUSE-VARIABLE LIST ***" << endl;
    for (i = 1; i < 9; i++) {
        cout << "** CLAUSE " << i << endl;
        for (j = 1; j < 5; j++) {
            k = 4 * (i - 1) + j;
            cout << "VARIABLE " << j << " " << clauseVarList[k] << endl;
        }
        if (i == 4) {
            cout << "HIT RETURN TO CONTINUE";
            getchar();
        }
    }

    // Inference section
    cout << "ENTER CONDITION VARIABLE? "; //basically asking the user what they want to find. In this case, we are looking for PREVENTION
    getline(cin, c);

    // Place condition variable c on the condition variable queue conditionVar
    conditionVar[bp] = c;
    bp++;

    // Set the condition variable pointer
    sn = 1; //statement number
    cn = 1; //clause number

    // Find the next statement number containing the condition variable (ie )
    // which is in front of the queue (conditionVar), this statement number
    // is located in the clause variable list (clauseVarList)
    f = 1; //f is an iterator

    while (sn != 0) {
        search(); //b496 //search() searches the clause variable list for our condition ATTACK

        cn = 1; // start at the first clause
        if (sn != 0) {
            i = 4 * (sn - 1) + cn;

            while (!clauseVarList[i].empty()) { // are there any more clauses for this statement?
                check_instantiation();
                cn++;
                i = 4 * (sn - 1) + cn;
            }
            /* no more clauses - check IF part of statement */
            s = 0;

            switch (sn) { //TODO change this
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
                continue; //goto b496
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
            continue; //goto b496
        }

        /* no more clauses in the clause variable list (clauseVarList)
        containing the variable in front of the queue (conditionVar(fp))
        then remove front variable (conditionVar(fp)) and replace it by
        the next variable (conditionVar(fp+1)). If no more variables are
        at the front of the queue, stop. */
        fp++; // next queue variable
        if (fp < bp) {
            //check out the condition variable 
            f = 1;
            continue; //goto b496
        }
        //no more conclusion variables on queue
        break;
    }

    return 0;
}

// Function to instantiate a variable (v) if it isn't already instantiated
//The instantiate indication (instlt) is a 0 if not, a 1 if it is.
//The vriable list (varList) contains the variable (v)
void check_instantiation() {
    i = 1;

    while (v != varList[i] && i <= 10)
        i++;

    if (instlt[i] != 1) {
        instlt[i] = 1;

        switch (i) { //TODO change this to ask what type of attack was identified
            case 1: cout << "RISE OR FALL FOR DO? "; getline(cin, dollar); break;
            case 2: cout << "RISE OR FALL FOR FT? "; getline(cin, fedint); break;
            case 3: cout << "ADD OR SUBTRACT FOR FM? "; getline(cin, fedmon); break;
            case 4: cout << "RISE OR FALL FOR IN? "; getline(cin, interest); break;
            case 5: cout << "RISE OR FALL FOR ST? "; getline(cin, stock); break;
        }
    }
}

// Function to search the clause variable list for a variable (clauseVarList)
void search() {
    flag = 0;
    sn = f; //set sn to f

    while (flag == 0 && sn <= 10) { //TODO change number of iterations to match our # of statements
        cn = 1;
        k = (sn - 1) * 4 + cn;

        while (clauseVarList[k] != conditionVar[fp] && cn < 4) {
            cn++;
            k = (sn - 1) * 4 + cn;
        }

        if (clauseVarList[k] == conditionVar[fp]) //if we find the condition variable
            flag = 1;

        if (flag == 0)
            sn++;
    }

    if (flag == 0)
        sn = 0; 

}

// Function to instantiate a variable (v) and place it on the back of the queue (conditionVar[bp])
void instantiate() {
    i = 1;

    while (v != varList[i] && i <= 10) //TODO change the number of iterations
        i++;

    instlt[i] = 1;
    i = 1;

    while (v != conditionVar[i] && i <= 10)
        i++;

    if (v != conditionVar[i]) {
        conditionVar[bp] = v;
        bp++;
    }
}

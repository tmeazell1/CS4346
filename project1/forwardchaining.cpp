#include <iostream>
#include <string>

using namespace std;

int flag;
string conditionVar[10]; //condition variable
string varList[10], clauseVarList[40]; // Variable list and clause variable list //TODO change these to appropriate lengths
string c, vp, v; // Condition variables
string PREVENTION, FC_ATTACK;
string FIREWALL, HTTPS, TRAINING, SANITIZE, VPN, ANTIVIRUS, PATCH; // Conclusion variables TODO change these to conclusions from FC lists

//TODO: write a brief description of how to implement each prevention, see example
string prevention1 = "The best prevention for this attack is a firewall. Find a robust firewall that has rate limiting features.";
string prevention2 = "https prevention";
string prevention3 = "training prevention";
string prevention4 = "sanitize prevention";
string prevention5 = "csp prevention";
string prevention6 = "vpn prevention";
string prevention7 = "antivirus prevention";
string prevention8 = "dnssec prevention";
string prevention9 = "patch prevention";

int instlt[10]; // Instantiated list (for instantiated variables)
//TODO: remove unnecesarily global variables such as loop counters
int f, i, j, k, s, fp, bp, gr, sn, cn; // Pointers and counters 

// Function prototypes
void search();
void check_instantiation();
void instantiate();

int FC_main(string a) {
    // Initialization section
    FC_ATTACK = a;
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
    varList[1] = "ATTACK";

    cout << "*** VARIABLE LIST ***" << endl; //we only have one variable. It seems like we need to get the variable from the BC function?
    for (i = 1; i < 2; i++)
        cout << "ENTER VARIABLE " << i << " " << varList[i] << endl;

    cout << "HIT RETURN TO CONTINUE";
    getchar();

    // Enter variables as they appear in the IF clauses
    //made this match the clause variable list from FC lists.txt
    clauseVarList[1] = "ATTACK";
    clauseVarList[2] = "PREVENTION";
    clauseVarList[5] = "ATTACK";
    clauseVarList[6] = "PREVENTION";
    clauseVarList[9] = "ATTACK";
    clauseVarList[10] = "PREVENTION";
    clauseVarList[13] = "ATTACK";
    clauseVarList[14] = "PREVENTION";
    clauseVarList[17] = "ATTACK";
    clauseVarList[18] = "PREVENTION";
    clauseVarList[21] = "ATTACK";
    clauseVarList[22] = "PREVENTION";
    clauseVarList[25] = "ATTACK";
    clauseVarList[26] = "PREVENTION";
    clauseVarList[29] = "ATTACK";
    clauseVarList[30] = "PREVENTION";
    clauseVarList[34] = "ATTACK";
    clauseVarList[35] = "PREVENTION";

    cout << "*** CLAUSE-VARIABLE LIST ***" << endl;
    for (i = 1; i < 10; i++) {
        cout << "** CLAUSE " << i << endl;
        for (j = 1; j < 3; j++) {
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
        search(); //b496 //search() searches the clause variable list for our condition PREVENTION
        //sets sn =0 if no match found, sn !=0 otherwise

        cn = 1; // start at the first clause
        if (sn != 0) { //if we found a match between conditionvar[fp] and clausevarlist
            i = 4 * (sn - 1) + cn;

            while (!clauseVarList[i].empty()) { // are there any more clauses for this statement?
                check_instantiation();
                cn++;
                i = 4 * (sn - 1) + cn;
            }
            /* no more clauses - check IF part of statement */
            s = 0;

            switch (sn) { //TODO change this
                case 1: if (FC_ATTACK == "DOS") s = 1; break;
                case 2: if (FC_ATTACK == "MITM") s = 1; break;
                case 3: if (FC_ATTACK == "PHISHING") s = 1; break;
                case 4: if (FC_ATTACK == "SQLI") s = 1; break;
                case 5: if (FC_ATTACK == "XSS") s = 1; break;
                case 6: if (FC_ATTACK == "PACKETSNIFF") s = 1; break;
                case 7: if (FC_ATTACK == "RANSOMEWARE") s = 1; break;
                case 8: if (FC_ATTACK == "DNSSPOOF") s = 1; break;
                case 9: if (FC_ATTACK == "ZERODAY") s = 1; break;
            }
            /* see if the THEN part should be inovked, i.e., s=1 */
            if (s != 1) {
                f = sn + 1;
                continue; //goto b496
            }

            switch (sn) {
                case 1: PREVENTION = "FIREWALL"; cout << prevention1 << endl; return 0;
                case 2: PREVENTION = "HTTPS"; cout << prevention2 << endl; return 0;
                case 3: PREVENTION = "TRAINING"; cout << prevention3 << endl; return 0;
                case 4: PREVENTION = "SANITIZE"; cout << prevention4 << endl; return 0;
                case 5: PREVENTION = "CSP"; cout << prevention5 << endl; return 0;
                case 6: PREVENTION = "VPN"; cout << prevention6 << endl; return 0;
                case 7: PREVENTION = "ANTIVIRUS"; cout << prevention7 << endl; return 0;
                case 8: PREVENTION = "DNSSEC"; cout << prevention8 << endl; return 0;
                case 9: PREVENTION = "PATCH"; cout << prevention9 << endl; return 0;
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
    cout << "We couldn't find a prevention" << endl;
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

        switch (i) { //TODO change this to get the attack directly from the backward chaining results
            case 1: cout << "You are experiencing a(n) " << FC_ATTACK << " attack. Finding prevention..." << endl; break;
            case 2: cout << "You are experiencing a(n) " << FC_ATTACK << " attack. Finding prevention..." << endl; break;
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

        if (clauseVarList[k] == conditionVar[fp]){ //if we find the condition variable
            flag = 1;
        }

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

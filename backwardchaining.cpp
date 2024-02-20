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
//changed these variables to match variable list in lists.txt
string TRAFFIC, PATTERN, EMAILS, DATABASE, SCRIPTS, INTERCEPT, RANSOM, DNSREQUESTS, VULNERABILITIES; //im not sure if these are even necessary 
string PROBLEM, ATTACK;
string buff;

// Instantiated list
int instantiatedList[11];

// Statement stack
int statementStack[11];

// Clause stack
int clauseStack[11];

int sn, sp, s, i;
int f =1;

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

    //entered the new conclusions from lists.txt
    conclusionList[1] = "PROBLEM";
    conclusionList[2] = "ATTACK";
    conclusionList[3] = "ATTACK";
    conclusionList[4] = "ATTACK";
    conclusionList[5] = "ATTACK";
    conclusionList[6] = "ATTACK";
    conclusionList[7] = "ATTACK";
    conclusionList[8] = "ATTACK";
    conclusionList[9] = "ATTACK";
    conclusionList[10] = "ATTACK";


    cout << "*** CONCLUSION LIST ***" << endl;
    for (int i = 1; i < 11; i++) { //TODO: change # of iterations to appropriate for our data
        cout << "CONCLUSION " << i << " " << conclusionList[i] << endl;
    }
    cout << "HIT RETURN TO CONTINUE";
    getline(cin, buff);

    //had to change varlist a bit, trying to understand the algorithm
    varList[1] = "PROBLEM";
    varList[2] = "ATTACK";
    varList[3] = "ATTACK";
    varList[4] = "ATTACK";
    varList[5] = "ATTACK";
    varList[6] = "ATTACK";
    varList[7] = "ATTACK";
    varList[8] = "ATTACK";
    varList[9] = "ATTACK";
    varList[10] = "ATTACK";

    cout << "*** VARIABLE LIST ***" << endl;
    for (int i = 1; i < 11; i++) {//TODO: change # of iterations to appropriate for our data
        cout << "VARIABLE " << i << " " << varList[i] << endl;
    }
    cout << "HIT RETURN KEY TO CONTINUE";
    getline(cin, buff);

    //Enter clause variables from lists.txt
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

    /*for (int i = 1; i < 9; i++) { //idk what was going on in this part tbh, i changed it to the part below
        cout << "** CLAUSE " << i << endl;
        for (int j = 1; j < 5; j++) {
            //int k = 4 * (i - 1) + j;
            cout << "VARIABLE " << j << " " << clauseVarList[k] << endl;
        }
        if (i == 4) {
            cout << "HIT RETURN KEY TO CONTINUE";
            getline(cin, buff);
        }
    }*/

    for (int i = 10; i < 101; i+=10) { //calculates the clause variables associated with each rule
        cout << "** RULE NUMBER " << i << endl;
        int k = 4*(i/10-1) +1;
        cout << "VARIABLE " << i << " " << clauseVarList[k] << endl;
    }

    // Inference section
    cout << "** ENTER CONCLUSION ? "; //I think here the user is expected to enter "attack" ie the goal is identify the attack
    getline(cin, variable);

    // Get conclusion statement number (sn) from the conclusion list (conclusionList)
    // First statement starts search
    b520:
    f = 1;
    determine_member_concl_list(); // If variable is a member, sn != 0. If not a member, sn = 0.

    if (sn != 0) {
        do {
            // Push statement number (sn) and clause number=1 on goal stack
            push_on_stack(); //decrements sp

            do {/* calculate clause location in clause-variable list */
            b545:
                int i = (statementStack[sp] - 1) * 4 + clauseStack[sp]; //this is causing mad issues
                variable = clauseVarList[i]; //finds problem,stuck on problem!
                

                if (variable != "") {
                    f = 1;
                    determine_member_concl_list(); // If variable is a member, sn != 0. If not a member, sn = 0.

                    if (sn != 0){//if we found a match, and its a conclusion, push it
                        //goto b520;
                        //f = 1;
                        //determine_member_concl_list();
                        //push_on_stack(); //decrements sp
                        int i = (statementStack[sp] - 1) * 4 + clauseStack[sp];
                        
                        variable = clauseVarList[i]; //finds problem

                    }
                    instantiate(); //where we get the user input
                    clauseStack[sp]++;
                }
            } while (variable != "");

            sn = statementStack[sp];
            s = 0;

            // If-then statements
            switch (sn) { //modified this to represent our knowledge base
                case 1: if (PROBLEM == "NO" || PROBLEM == "YES") s = 1; break;
                case 2: if (PROBLEM == "YES" && TRAFFIC == "YES") s = 1; break;
                case 3: if (PROBLEM == "YES" && PATTERN == "YES") s = 1; break;
                case 4: if (PROBLEM == "YES" && EMAILS == "YES") s = 1; break;
                case 5: if (PROBLEM == "YES" && DATABASE == "YES") s = 1; break;
                case 6: if (PROBLEM == "YES" && SCRIPTS == "YES") s = 1; break;
                case 7: if (PROBLEM == "YES" && INTERCEPT == "YES") s = 1; break;
                case 8: if (PROBLEM == "YES" && RANSOM == "YES") s = 1; break;
                case 9: if (PROBLEM == "YES" && DNSREQUESTS == "YES") s = 1; break;
                case 10: if (PROBLEM == "YES" && VULNERABILITIES == "YES") s = 1; break;
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
            switch (sn) {//modified this to represent our knowledge base
                case 1: PROBLEM = "NO"; cout << "there is no problem in the system" << endl; break;
                case 2: PROBLEM = "YES"; cout << "there is a problem in the system" << endl; break;
                case 3: ATTACK = "DOS"; cout << "This is a DoS attack" << endl; break;
                case 4: ATTACK = "PHISHING"; cout << "This is a phishing attack" << endl; break;
                case 5: ATTACK = "MITM"; cout << "This is a Man in the Middle attack" << endl; break;
                case 6: ATTACK = "SQLI"; cout << "This is a SQL injection attack" << endl; break;
                case 7: ATTACK = "XSS"; cout << "This is a Cross site scripting attack" << endl; break;
                case 8: ATTACK = "PACKETSNIFF"; cout << "this is a packet sniffing attack" << endl; break;
                case 9: ATTACK = "RANSOMWARE"; cout << "this is a ransomeware attack" << endl; break;
                case 10: ATTACK = "DNSSPOOF"; cout << "this is a DNS spoofing attack" << endl; break;
                case 11: ATTACK = "ZERODAY"; cout << "this is a zero day exploit" << endl; break;
            }

            sp++;
            if (sp >= 11) {//TODO: modify this number to work for our data
                cout << "*** SUCCESS" << endl;
                return 0;
            }

            else {
                clauseStack[sp]++;
                goto b545;
            }
        }
    }
    cout << "we couldnt find a conclusion matching " << variable << endl;
    return 0;
}

// Routine to determine if a variable (variable) is a member of the conclusion list (conclusionList)
// If yes, return sn != 0. If not a member, sn = 0.
void determine_member_concl_list() {
    sn = 0;
    int i = f;

    while (variable != conclusionList[i] && i < 8){
        i++;
    }

    if (variable == conclusionList[i]){
        sn = i; // A member
    }
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
    while ((variable != varList[i] && i < 11) || (variable == varList[i] && instantiatedList[i] >= 1)){  //changed this condition
        i++;
    }

    if (variable == varList[i] && instantiatedList[i] < 1) {
        instantiatedList[i] = 1; // Mark instantiated 

        // Input statements for sample position knowledge base
        switch (i) { //modified this to get user inputs for each variable in the variable list from lists.txt
            case 1: cout << "Is there a problem in the network? YES or NO "; getline(cin, PROBLEM); break;
            case 2: cout << "Is there an increase in network traffic? YES or NO "; getline(cin, TRAFFIC); break;
            case 3: cout << "Are there unusual patterns or network actovity? YES or NO "; getline(cin, PATTERN); break;
            case 4: cout << "Are users receiving fraudulent emails or suspicious links? YES or NO "; getline(cin, EMAILS); break;
            case 5: cout << "Has there been fraudulent database activity? YES or NO "; getline(cin, DATABASE); break;
            case 6: cout << "Have malicious scripts been executing on webpages? YES or NO "; getline(cin, SCRIPTS); break;
            case 7: cout << "Has network traffic been intercepted? YES or NO "; getline(cin, INTERCEPT); break;
            case 8: cout << "Have ransom demands been found in files? YES or NO "; getline(cin, RANSOM); break;
            case 9: cout << "Are there any manipulated DNS requests? YES or NO "; getline(cin, DNSREQUESTS); break;
            case 10: cout << "Is it possible there are unknown vulnerabilities? YES or NO "; getline(cin, VULNERABILITIES); break;

        }
    }
}


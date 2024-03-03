#include <iostream>
#include <string>
#include "variables.h"

using namespace std;




int BC_main() {
    // Initialization section
    //TODO: change stack pointer to be appropriate for our data 
    sp = 11;

    for (int i = 1; i < 11; i++) {//TODO: change # of iterations to appropriate for our data
        // Initialize arrays
        conclusionList[i] = "";
        bc_varList[i] = "";
        instantiatedList[i] = 0;
        statementStack[i] = 0;
        clauseStack[i] = 0;
    }

    for (int i = 1; i < 41; i++) { //TODO: change # of iterations to appropriate for our data
        // Initialize clause variable list
        bc_clauseVarList[i] = "";
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
    bc_varList[1] = "PROBLEM";
    bc_varList[2] = "ATTACK";
    bc_varList[3] = "ATTACK";
    bc_varList[4] = "ATTACK";
    bc_varList[5] = "ATTACK";
    bc_varList[6] = "ATTACK";
    bc_varList[7] = "ATTACK";
    bc_varList[8] = "ATTACK";
    bc_varList[9] = "ATTACK";
    bc_varList[10] = "ATTACK";

    cout << "*** VARIABLE LIST ***" << endl;
    for (int i = 1; i < 11; i++) {//TODO: change # of iterations to appropriate for our data
        cout << "VARIABLE " << i << " " << bc_varList[i] << endl;
    }
    cout << "HIT RETURN KEY TO CONTINUE";
    getline(cin, buff);

    //Enter clause variables from lists.txt
    bc_clauseVarList[1] = "PROBLEM";
    bc_clauseVarList[2] = "ATTACK";
    bc_clauseVarList[5] = "PROBLEM";
    bc_clauseVarList[6] = "ATTACK";
    bc_clauseVarList[9] = "PROBLEM";
    bc_clauseVarList[10] = "ATTACK";
    bc_clauseVarList[13] = "PROBELM";
    bc_clauseVarList[14] = "ATTACK";
    bc_clauseVarList[17] = "PROBLEM";
    bc_clauseVarList[18] = "ATTACK";
    bc_clauseVarList[21] = "PROBLEM";
    bc_clauseVarList[22] = "ATTACK";
    bc_clauseVarList[25] = "PROBLEM";
    bc_clauseVarList[26] = "ATTACK";
    bc_clauseVarList[29] = "PROBLEM";
    bc_clauseVarList[30] = "ATTACK";
    bc_clauseVarList[33] = "PROBLEM";
    bc_clauseVarList[34] = "ATTACK";
    bc_clauseVarList[37] = "PROBLEM";
    bc_clauseVarList[38] = "ATTACK";

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

    for (int n = 10; n < 101; n+=10) { //calculates the clause variables associated with each rule
        cout << "** RULE NUMBER " << n << endl;
        int k = 4*(n/10-1) +1;
        cout << "VARIABLE " << n << " " << bc_clauseVarList[k] << endl;
    }

    // Inference section
    cout << "** ENTER CONCLUSION ? "; //I think here the user is expected to enter "attack" ie the goal is identify the attack
    getline(cin, variable);

    // Get conclusion statement number (sn) from the conclusion list (conclusionList)
    // First statement starts search
    b520:
    bc_f = 1;
    determine_member_concl_list(); // If variable (Attack) is a member, sn != 0. If not a member, sn = 0.

    if (bc_sn != 0) {
        do {
            // Push statement number (sn) and clause number=1 on goal stack
            push_on_stack(); //decrements sp

            do {/* calculate clause location in clause-variable list */
            b545:
                int i = (statementStack[sp] - 1) * 4 + clauseStack[sp]; 
                variable = bc_clauseVarList[i]; //finds problem

                if (variable != "") {
                    bc_f = 1;
                    determine_member_concl_list(); // If problem is a member, sn != 0. If not a member, sn = 0.

                    if (bc_sn != 0){//if we found a match, and its a conclusion, push it
                        //goto b520;
                        //f = 1;
                        //determine_member_concl_list();
                        //push_on_stack(); //decrements sp
                        int i = (statementStack[sp] - 1) * 4 + clauseStack[sp];
                        
                        variable = bc_clauseVarList[i]; //finds problem

                    }
                    BC_instantiate(); //where we get the user input
                    clauseStack[sp]++;
                }
            } while (variable != "");

            bc_sn = statementStack[sp];
            bc_s = 0;

            // If-then statements
            switch (bc_sn) { //modified this to represent our knowledge base
                case 1: if (PROBLEM == "NO") bc_s = 1; break;
                case 2: if (PROBLEM == "YES" && TRAFFIC == "YES") bc_s = 1; break;
                case 3: if (PROBLEM == "YES" && PATTERN == "YES") bc_s = 1; break;
                case 4: if (PROBLEM == "YES" && EMAILS == "YES") bc_s = 1; break;
                case 5: if (PROBLEM == "YES" && DATABASE == "YES") bc_s = 1; break;
                case 6: if (PROBLEM == "YES" && SCRIPTS == "YES") bc_s = 1; break;
                case 7: if (PROBLEM == "YES" && INTERCEPT == "YES") bc_s = 1; break;
                case 8: if (PROBLEM == "YES" && RANSOM == "YES") bc_s = 1; break;
                case 9: if (PROBLEM == "YES" && DNSREQUESTS == "YES") bc_s = 1; break;
                case 10: if (PROBLEM == "YES" && VULNERABILITIES == "YES") bc_s = 1; break;
            }

            if (bc_s != 1) {
                int i = statementStack[sp];
                variable = conclusionList[i];
                bc_f = statementStack[sp] + 1;
                determine_member_concl_list();
                sp++;
            }

        } while (bc_s != 1 && bc_sn != 0);

        if (bc_sn != 0) {
            switch (bc_sn) {//modified this to represent our knowledge base
                case 1: ATTACK = "NO"; cout << "there is no problem in the system" << endl; break;
                case 2: ATTACK = "DOS"; cout << "This is a DoS attack" << endl; break;
                case 4: ATTACK = "PHISHING"; cout << "This is a phishing attack" << endl; break;
                case 3: ATTACK = "MITM"; cout << "This is a Man in the Middle attack" << endl; break;
                case 5: ATTACK = "SQLI"; cout << "This is a SQL injection attack" << endl; break;
                case 6: ATTACK = "XSS"; cout << "This is a Cross site scripting attack" << endl; break;
                case 7: ATTACK = "PACKETSNIFF"; cout << "this is a packet sniffing attack" << endl; break;
                case 8: ATTACK = "RANSOMWARE"; cout << "this is a ransomeware attack" << endl; break;
                case 9: ATTACK = "DNSSPOOF"; cout << "this is a DNS spoofing attack" << endl; break;
                case 10: ATTACK = "ZERODAY"; cout << "this is a zero day exploit" << endl; break;
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
    bc_sn = 0;
    int i = bc_f;

    while (variable != conclusionList[i] && i < 8){
        i++;
    }

    if (variable == conclusionList[i]){
        bc_sn = i; // A member
    }
}

// Routine to push statement number (sn) and a clause number of 1 onto the conclusion stack
// Decrements stack pointer (sp)
void push_on_stack() {
    sp--;
    statementStack[sp] = bc_sn;
    clauseStack[sp] = 1;
}

// Routine to instantiate a variable (variable) if it isn't already instantiated
// Instantiate indication (instantiatedList) is 0 if not, 1 if it is. Variable list (varList) contains the variable (variable).
void BC_instantiate() {
    int i = 1;
    while ((variable != bc_varList[i] && i < 11) || (variable == bc_varList[i] && instantiatedList[i] >= 1)){  //changed this condition
        i++;
    }

    if (variable == bc_varList[i] && instantiatedList[i] < 1) {
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

string getAttack()
{
    return ATTACK;
}


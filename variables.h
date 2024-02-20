#ifndef VARIABLES_H
#define VARIABLES_H
#include <iostream>
#include <string>

using namespace std;

//backwardchaing.cpp
//TODO: change # of elements in each array to be appropriate for our data
inline const int CONCLUSION_LIST_SIZE = 10;
inline const int VAR_LIST_SIZE = 10;
inline const int CLAUSE_VAR_LIST_SIZE = 40;

inline string conclusionList[CONCLUSION_LIST_SIZE];
inline string bc_varList[VAR_LIST_SIZE];
inline string bc_clauseVarList[CLAUSE_VAR_LIST_SIZE];

inline string variable;
//changed these variables to match variable list in lists.txt
inline string TRAFFIC, PATTERN, EMAILS, DATABASE, SCRIPTS, INTERCEPT, RANSOM, DNSREQUESTS, VULNERABILITIES; //im not sure if these are even necessary 
inline string PROBLEM, ATTACK;
inline string buff;

// Instantiated list
inline int instantiatedList[11];

// Statement stack
inline int statementStack[11];

// Clause stack
inline int clauseStack[11];

inline int bc_sn, sp, bc_s, bc_i;
inline int bc_f =1;

// Function prototypes
inline void determine_member_concl_list();
inline void push_on_stack();
inline void BC_instantiate();
inline int BC_main();
inline string getAttack();

//forwardchaining.cpp
inline int flag;
inline string conditionVar[10]; //condition variable
inline string varList[10], clauseVarList[40]; // Variable list and clause variable list //TODO change these to appropriate lengths
inline string c, vp, v; // Condition variables
inline string PREVENTION, FC_ATTACK;
inline string FIREWALL, HTTPS, TRAINING, SANITIZE, VPN, ANTIVIRUS, PATCH; // Conclusion variables TODO change these to conclusions from FC lists

//TODO: write a brief description of how to implement each prevention, see example
inline string prevention1 = "The best prevention for this attack is a firewall. Find a robust firewall that has rate limiting features.";
inline string prevention2 = "https prevention";
inline string prevention3 = "training prevention";
inline string prevention4 = "sanitize prevention";
inline string prevention5 = "csp prevention";
inline string prevention6 = "vpn prevention";
inline string prevention7 = "antivirus prevention";
inline string prevention8 = "dnssec prevention";
inline string prevention9 = "patch prevention";

inline int instlt[10]; // Instantiated list (for instantiated variables)
//TODO: remove unnecesarily global variables such as loop counters
inline int f, i, j, k, s, fp, bp, gr, sn, cn; // Pointers and counters 

// Function prototypes
inline void search();
inline void check_instantiation();
inline void instantiate();
inline int FC_main(string);

#endif
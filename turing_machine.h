#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

typedef vector<vector<int>> vvi;
typedef vector<vector<char>> vvc;

class TuringMachine {
	string file_name,
				tape;		// input tape on which turing machine works
	int num_states,	// number of states
		num_alphs, 	// number of alphabets
		ptr;		// location of pointer head of turing machine
	map<string, int> state_id;		// maps each state to a unique key
	map<char, int> alph_id;				// maps each alphabet to a unique key
	vector<int> accept_state;
	vector<vector<int>> state_table;	// transition table storing next state
												// for a given (present state, input char) pair
	vector<vector<int>> dir_table;	// transition table storing next direction
												// for a given (state, char) pair
	vector<vector<char>> write_table;	// transition table storing next write char
												// for a given (state, char) pair
public:
	TuringMachine(string _file_name):
		file_name(_file_name),
		num_states(0),
		num_alphs(0),
		ptr(0){};

	void displayTape();
	int parseFile();
	//void initializeTables();
	void makeTransitionTables();
	void turingSimulator();
};

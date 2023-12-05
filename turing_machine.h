#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

typedef vector<vector<int>> vvi;
typedef vector<vector<char>> vvc;

class TuringMachine {
	string file_name,
				tape;	// fita de entrada na qual a máquina de Turing trabalha
	int num_states,		// number of states
		num_alphs, 		// número de alfabetos
		ptr;			// localização da cabeça do ponteiro da máquina de turing
	map<string, int> state_id;		// associa cada estado a uma chave única
	map<char, int> alph_id;				// associa cada alfabeto a uma chave única
	vector<int> accept_state;
	vector<vector<int>> state_table;	// tabela de transição que armazena o estado seguinte
										// para um dado par (estado atual, carácter de entrada)
	vector<vector<int>> dir_table;	// tabela de transição que armazena a direção seguinte
									// para um determinado par (estado, carácter)
	vector<vector<char>> write_table;	// tabela de transição que armazena o próximo carácter de escrita
										// para um determinado par (estado, carácter)
public:
	TuringMachine(string _file_name):
		file_name(_file_name),
		num_states(0),
		num_alphs(0),
		ptr(0){};

	void displayTape();
	int parseFile();
	//void initializeTables(); //nao precisa dessa poha
	void makeTransitionTables();
	void turingSimulator();
};

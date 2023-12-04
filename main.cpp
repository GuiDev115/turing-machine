#include "turing_machine.h"

using namespace std;

int main(int argc, char const *argv[]){
	if(argc == 1){
		cerr << "Too few arguments\n";
		return 1;
	}
	for (int i = 1; i < argc; ++i){
		std::cout << argv[i] << ":\n";
		TuringMachine t(argv[i]);
		t.parseFile();
		t.makeTransitionTables();
		t.turingSimulator();
		cout << "\n\n";
	}
	return 0;
}
#include "turing_machine.h"
#include <unistd.h>

using namespace std; 

void TuringMachine::displayTape() {
	cout << "\r" << tape.substr(0, ptr);	// apresentar o conteúdo da fita antes da cabeça do ponteiro
	cout << "[" << tape[ptr] << "]";		// apresentar o conteúdo da fita sob a cabeça do ponteiro
	cout << tape.substr(ptr + 1) << endl;	// apresentar o conteúdo da fita sob a cabeça do ponteiro
	cout << flush; // limpar o buffer de saída
	usleep(100000);

}

int TuringMachine::parseFile() {

	// // abrir entrada para leitura
	ifstream ifs;
	ifs.open(file_name, ios::in); // abrir entrada
	if(!ifs.is_open()) {
		cerr << "error: Can't open file\n"; 
		return 1;
	}

	string line, present_state, next_state;
	char read_char, write_char, direction;

	getline(ifs,tape);	// lendo entrada
	while(getline(ifs, line)){
		istringstream iss(line);
		iss >> present_state;
		if(present_state == "accept"){
			while(iss >> present_state)
				accept_state.push_back(state_id.find(present_state)->second);
			continue;
		}
		iss >> read_char >> write_char >> direction >> next_state;
		if(state_id.insert(make_pair(present_state, num_states)).second) // inserir estado na tabela de estados
			++num_states;
		if(state_id.insert(make_pair(next_state, num_states)).second) // inserir estado na tabela de estados
			++num_states;
		if(alph_id.insert(make_pair(read_char, num_alphs)).second) // inserir alfabeto na tabela de alfabetos
			++num_alphs;
		if(alph_id.insert(make_pair(write_char, num_alphs)).second) // inserir alfabeto na tabela de alfabetos
			++num_alphs; 
	}
	
	// inicializando tabelas de transição
	state_table = vector<vector<int>>(num_states, vector<int>(num_alphs, -1));
	write_table = vector<vector<char>>(num_states, vector<char>(num_alphs, '_'));
	dir_table = vector<vector<int>>(num_states, vector<int>(num_alphs, 0));

	ifs.close(); // fechar entrada
	return 0; // sucesso
}

void TuringMachine::makeTransitionTables(){ // preencher tabelas de transição
	string line, present_state, next_state, tape;
	char read_char, write_char, direction; 
	int present_state_id, next_state_id, read_char_id, dir_id;

	ifstream ifs;
	ifs.open(file_name, ios:: in);
	getline(ifs, line);
	while(getline(ifs, line)){
		istringstream iss(line);

		iss >> present_state;
		if(present_state == "accept") // ignorar linha de aceitação
			continue;

		iss >> read_char >> write_char >> direction >> next_state;

		// encontrar as respectivas identificações únicas
		present_state_id = state_id.find(present_state)->second; 
		next_state_id = state_id.find(next_state)->second;
		read_char_id = alph_id.find(read_char)->second;
		if(direction == 'l') //vai pra esquerda
			dir_id = -1;
		else if(direction == 'r') //vai pra direita
			dir_id = +1;
		else
			dir_id = 0;

		// preencher as tabelas de transição com identificações únicas
		state_table[present_state_id][read_char_id] = next_state_id; 
		write_table[present_state_id][read_char_id] = write_char;
		dir_table[present_state_id][read_char_id] = dir_id; 
	}
	ifs.close(); // fechar entrada
} 

void TuringMachine::turingSimulator(){ // simular a máquina de turing
	int present_state_id = 0, read_char_id, dir_id = 0;

	displayTape(); // apresentar a fita
	while(true){
		read_char_id = alph_id.find(tape[ptr])->second;
		dir_id = dir_table[present_state_id][read_char_id];
		tape[ptr] = write_table[present_state_id][read_char_id];
		present_state_id = state_table[present_state_id][read_char_id];

		if(present_state_id == -1){ // se não houver transição para o estado atual
			if(accept_state.size() > 0) // se houver um estado de aceitação
				cout << "\n> rejeitado krai"; 
			else
				cout << "\n> Interrompido"; 
			break;
		}
		if(find(accept_state.begin(), accept_state.end(), present_state_id) 		// se o estado atual for um estado de aceitação
			!= accept_state.end()){
			cout << "\n> Aceito";
			break;
		}

		ptr += dir_id; // mover a cabeça do ponteiro
		if(ptr < 0){
			tape = "_" + tape; // inserir um espaço em branco no início da fita
			ptr = 0; // mover a cabeça do ponteiro para a direita
		}
		if(ptr >= tape.size())
			tape = tape + "_";
		displayTape(); // apresentar a fita
	}
}
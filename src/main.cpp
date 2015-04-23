#include <iostream>
#include <string>
#include <fstream>
#include "../headers/stack.hpp"

using namespace std;


int main(){
	ifstream entryFile;
	string expr;
	int i;
	Stack<char> tokens;

	//!ABRINDO ARQUIVO DE ENTRADA
	entryFile.open("expressions.txt");
	if (entryFile.is_open()){
		while(!entryFile.eof()){
			getline(entryFile, expr);

			//!FAZENDO "TOKENIZAÇÃO" : CRIANDO PILHA COM OS CARACTERES NAO NULOS
			for (i = 0; i < expr.length(); i++){
				if (expr[i] != ' ' && expr[i] != '\t')
					tokens.push(expr[i]);
			}
		}
	}
	else
		cout << "Erro ao abrir arquivo.\n";		

	while(!tokens.isEmpty())
		cout << tokens.pop() << endl;
	
	return 0;
}
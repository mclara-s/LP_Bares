/** @file bares.cpp
 *  Projeto Basic Arithmetic Expression Based on Stacks
 *
 *  O objetivo desde projeto é motivar o uso das estruturas de dados estudada, pilha e fila, no contexto
 * 	de uma aplicação real.
 */

#include "../headers/bares.hpp"

/**
* @main do projeto B.A.R.E.S.
*/

using namespace std;

bool readFile(Queue<string> &expressions){
	ifstream entryFile;
	string expr;

	entryFile.open("src/expressions.txt");
	if (entryFile.is_open()){
		while(!entryFile.eof()){
			getline(entryFile, expr);
			if (expr != "\n" && expr != " " && expr != "\t" && expr != "")
				expressions.enqueue(expr);
			expr.clear();
		}
		entryFile.close();
		return true;
	}
	else
		return false;
}

int main(){
	Bares bares;
	Queue<string> expressions;

	if(readFile(expressions)){
		while(!expressions.isEmpty()){
			if (bares.calculaPosF(expressions.dequeue()))				
				cout << bares.getResult() << endl;
		}
	}
	else
		cout << "Erro ao abrir o arquivo. Por favor, tente novamente.\n";
	
	return 0;
}

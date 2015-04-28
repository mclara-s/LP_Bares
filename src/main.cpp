//PARA COMPILAR: g++ main.cpp -std=c++11 -o programa

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "../headers/stack.hpp"
#include "../headers/queue.hpp"

using namespace std;

bool readFile(Queue<string> &expressions){
	ifstream entryFile;
	string expr;

	entryFile.open("expressions.txt");
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

bool isOperator(string ch){
	if (ch == "*" || ch == "/" || ch == "+" || ch == "-" || ch == "(" || ch == ")" ||
		ch == "\%" || ch == "$" || ch == "^")
		return true;
	else
		return false;
}

bool isNumber(string str){
	char ch;
	while (!str.empty()){
		ch = str.front();
		if (!isdigit(ch))
			return false;
		str.erase(str.begin());
	}
	return true;
}

void errors(int i){
	switch (i){
		case 1:
			cout << "Erro! Constate numerica invalida.\n";
			break;
		case 2:
			cout << "Erro! Falta operando.\n";
			break;
		case 3:
			cout << "Erro! Operando invalido.\n";
			break;
		case 4:
			cout << "Erro! Operador invalido.\n";
			break;
		case 5:
			cout << "Erro! Falta operador.\n";
			break;
		case 6:
			cout << "Erro! Fechamento de escopo invalido.\n";
			break;
		case 7:
			cout << "Erro! Escopo aberto.\n";
			break;
		case 8:
			cout << "Erro! Divisao por zero!\n";
			break; 
	}
}

int tokenizacao (string expr, Queue<string> &tokenQueue){
	string token, lastToken = "";
	while (!expr.empty()){
		token.clear();
		while (expr.front() != ' ' && expr.front() != '\t' && !expr.empty()){
			if (isdigit(expr.front())){
				token += expr.front();
				expr.erase(expr.begin());
			}
			else{
				if (!token.empty()){
					lastToken = token;
					tokenQueue.enqueue(token);
				}
				token = expr.front();
				if (token == "-" && (isOperator(lastToken) || lastToken == ""))
					token = "$";
				expr.erase(expr.begin());
				break;
			}
		}
		tokenQueue.enqueue(token);
		if (!expr.empty() && (expr.front() == ' ' || expr.front() == '\t')){
			expr.erase(expr.begin());
		}
		cout <<"token: "<< token << "lasttoken: " << lastToken << endl;
		if (isNumber(token) && isNumber(lastToken)){
			//errors(5);
			return -1;
		}
		lastToken.clear();
		lastToken = token;
	}
	if (isOperator(token) && token != ")"){
		errors(2);
		return -1;
	}
	return 1;
}

int prioridade(string op){
	if (op == "$")
		return 5;
	if (op == "^")
		return 4;
	if (op == "*" || op == "/" || op == "") // COMO FAÇO PARA TESTAR O %?
		return 3;
	if (op == "+" || op == "-")
		return 2;
	if (op == ")" || op == "(")
		return 1;
}


int transformaParaPos(Queue<string> &entrada, Queue<string> &saida){
	Stack<string> operators;
	string symb, topSymb;
	int op;

	while (!entrada.isEmpty()){
		symb = entrada.dequeue();
			if (!isOperator(symb)){
				if (isNumber(symb)){
					op = stoi(symb);
					if(op > 32767 || op < -32767){
						errors(1);
						return -1;
					}
					saida.enqueue(symb);
				}
				else{
					if ((symb.front() >= 65 && symb.front() <= 90) || (symb.front() >= 97 && symb.front() <= 122))
						errors(3);
					else
						errors(4);
					return -1;
				}
			}
			else if (symb == "(")
				operators.push(symb);
			else if (symb == ")"){
				while (operators.top() != "("){
					topSymb = operators.pop();
					if (topSymb == "$")
						topSymb = "-";
					saida.enqueue(topSymb);
				}
				operators.pop(); // remove o '(';
			}
			else{
				while(!operators.isEmpty() && prioridade(operators.top()) >= prioridade(symb)){
					topSymb = operators.pop();
					if (topSymb == "$")
						topSymb = "-";
					saida.enqueue(topSymb);
				}
				operators.push(symb);
			}

		}

	while(!operators.isEmpty()){
		symb = operators.pop();
		saida.enqueue(symb);
	}
	return 1;
}

int main(){
	Queue<string> infix, posfix, expressions;

	if (readFile(expressions)){
		while (!expressions.isEmpty()){
			infix.clear();
			posfix.clear();
			tokenizacao(expressions.dequeue(), infix); //OBS: CORRIGIR TOKENIZAÇÃO
			//infix.print();
			transformaParaPos(infix, posfix);
			//posfix.print();
			//if (transformaParaPos(infix, posfix) > 0){
				//calcula 
//			}			
		}
	}
	else{
		cout << "Erro ao abrir o arquivo. Por favor, tente novamente.\n";
	}

	//!ABRINDO ARQUIVO DE ENTRADA
/*	entryFile.open("expressions.txt");
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
	*/
	
	return 0;
}
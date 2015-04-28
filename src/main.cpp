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
		ch == "SIMBOLO PORCENTAGEM" || ch == "$" || ch == "^")
		return true;
	else
		return false;
}

void tokenizacao (string expr, Queue<string> &tokenQueue){
	string token, lastToken = "";
	while (!expr.empty()){
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
		lastToken.clear();
		lastToken = token;
		token.clear();
	}
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


void transformaParaPos(Queue<string> &entrada, Queue<string> &saida){
	Stack<string> operators;
	string symb, topSymb;

	while (!entrada.isEmpty()){
		symb = entrada.dequeue();
			if (!isOperator(symb))
				saida.enqueue(symb);
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
}

int main(){
	Queue<string> infix, posfix, expressions;

	if (readFile(expressions)){
		while (!expressions.isEmpty()){
			infix.clear();
			posfix.clear();
			tokenizacao(expressions.dequeue(), infix); //OBS: CORRIGIR TOKENIZAÇÃO
			infix.print();
			transformaParaPos(infix, posfix);
			posfix.print();
			
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
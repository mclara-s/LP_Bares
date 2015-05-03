	//PARA COMPILAR: g++ main.cpp -std=c++11 -o programa

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "../headers/stack.hpp"
#include "../headers/queue.hpp"

using namespace std;

struct Token {
	string str;
	int col;
	void print(){
		cout << "(" << str << ", " << col << ")\n";
	}
	
	friend ostream& operator<<(ostream& os, const Token& tk)
	{
	    os << "(" << tk.str <<  ", " << tk.col << ")";
	    return os;
	}
};

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
	if (str.empty())
		return false;
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
		default:
			break; 
	}
}

int testaErros1a5(string token, string lastToken){
	//TESTE ERRO 1
	if (isNumber(token)){
		int i = stoi(token);
		if(i > 32767 || i < -32767 )
			return 1;
	}

	//TESTE ERRO 2 NO MEIO DA EXPRESSAO
	if (isOperator(token) && isOperator(lastToken) && 
		token != "(" && token != ")" && token != "$" && lastToken!= "(" && lastToken!=")"){
		//cout <<"teste 2.1\n";
		return 2;
	}
	if (token == ")" && (isOperator(lastToken) && lastToken!= ")")){
		//cout <<"teste 2.2\n";
		return 2;
	}
	if (lastToken == "(" && (token!= "$" && token != "(" && !isNumber(token))){
		//cout <<"teste 2.3\n";
		return 2;
	}

	//TESTE ERRO 3 e 4
	if (!isNumber(token) && !isOperator(token)){
		if ((token.front() >= 65 && token.front() <= 90) || (token.front() >= 97 && token.front() <= 122))
			return 3;
		else
			return 4;
	}

	//TESTE ERRO 5
	if (isNumber(token) && isNumber(lastToken)){
		//cout <<"teste 5.1\n";
		return 5;
	}
	if (token == "(" && ((!isOperator(lastToken) && lastToken != "") || lastToken == ")")){
		//cout <<"teste 5.2\n";
		return 5;
	}
	else
		return 0;
}

/*
int testaErros6e7(int pA, int pF){
	if (pF > pA)
		return 6;
	else if (pA > pF)
		return 7;
	else
		return 0;
}
*/

int tokenizacao (string expr, Queue<Token> &tokenQueue){
	//string token, lastToken = "";
	Token tk, lastTk;
	int teste, coluna = 0;
	//nParentesisAb = nParentesisFech = 0;

	while (!expr.empty()){
		++coluna;
		//token.clear();
		while (expr.front() != ' ' && expr.front() != '\t' && !expr.empty()){
			if (!tk.str.empty()){
					lastTk.str = tk.str;
					lastTk.col = tk.col;
					tokenQueue.enqueue(tk);
					tk.str.clear();
					++coluna;
			}

			if (isdigit(expr.front())){
				/*if (!tk.str.empty()){
					lastTk.str = tk.str;
					lastTk.col = tk.col;
					tokenQueue.enqueue(tk);
					tk.str.clear();
					++coluna;
				}*/
				tk.str += expr.front();
				expr.erase(expr.begin());
			}
			else{
				/*if (!tk.str.empty()){
					lastTk.str = tk.str;
					lastTk.col = tk.col;
					tokenQueue.enqueue(tk);
					tk.str.clear();
					++coluna;
				}*/
				tk.str = expr.front();
				//if (tk.str == "(")
				//	++nParentesisAb;
				//else if (token == ")")
				//	++nParentesisFech;
				if (tk.str == "-" && (isOperator(lastTk.str) || lastTk.str == ""))
					tk.str = "$";
				expr.erase(expr.begin());
				//break;
			}
			tk.col = coluna;
		}
		tokenQueue.enqueue(tk);
		if (!expr.empty() && (expr.front() == ' ' || expr.front() == '\t')){
			++coluna;
			expr.erase(expr.begin());
		}

		teste = testaErros1a5(tk.str, lastTk.str);
		if (teste > 0){
			errors(teste);
			return -1;
		}
		lastTk.str.clear();
		lastTk.str = tk.str;
		lastTk.col = tk.col;
		tk.str.clear();
	}

	//TESTE ERRO 2 FINAL DA EXPRESSAO
	if (isOperator(lastTk.str) && lastTk.str != ")"){
		errors(2);
		return -1;
	}
/*	//TESTE ERRORS 6 E 7
	teste = testaErros6e7(nParentesisAb, nParentesisFech);
	if (teste > 0){
		errors(teste);
		return -1;
	}*/

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

/*
int transformaParaPos(Queue<string> &entrada, Queue<string> &saida){
	Stack<string> operators;
	string symb, topSymb;
	int op;

	while (!entrada.isEmpty()){
		symb = entrada.dequeue();
			if (!isOperator(symb)){
					saida.enqueue(symb);
			}
			else if (symb == "(")
				operators.push(symb);
			else if (symb == ")"){
				while (operators.top() != "(" && !operators.empty()){
					topSymb = operators.pop();
					if (topSymb == "$")
						topSymb = "-";
					saida.enqueue(topSymb);
				}
				if (operators.empty()){
					errors(6);
					return -1;
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
		if (symb == "("){
			errors(7);
			return -1;
		}
		saida.enqueue(symb);
	}
	return 1;
}
*/

int main(){
	Queue<Token> infix, posfix;
	Queue<string> expressions;
	Token t;

	if (readFile(expressions)){
		while (!expressions.isEmpty()){
			infix.clear();
			posfix.clear();
			tokenizacao(expressions.dequeue(), infix); //OBS: CORRIGIR TOKENIZAÇÃO
			/*while(!infix.isEmpty()){
				t = infix.dequeue();
				t.print();
				
			}*/
			infix.print();
			//transformaParaPos(infix, posfix);
			/*posfix.print();
			if (transformaParaPos(infix, posfix) > 0){
				calcula 
//			}*/			
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
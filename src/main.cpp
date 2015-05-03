	//PARA COMPILAR: g++ main.cpp -std=c++11 -o programa

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <math.h>
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

void errors(int i, Token tk){
	switch (i){
		case 1:
			cout << "Erro: coluna " << tk.col << " - Constate numerica invalida.\n";
			break;
		case 2:
			cout << "Erro: coluna " << tk.col << " - Falta operando.\n";
			break;
		case 3:
			cout << "Erro: coluna " << tk.col << " - Operando invalido.\n";
			break;
		case 4:
			cout << "Erro: coluna " << tk.col << " - Operador invalido.\n";
			break;
		case 5:
			cout << "Erro: coluna " << tk.col << " - Falta operador.\n";
			break;
		case 6:
			cout << "Erro: coluna " << tk.col << " - Fechamento de escopo invalido.\n";
			break;
		case 7:
			cout << "Erro: coluna " << tk.col << " - Escopo aberto.\n";
			break;
		case 8:
			cout << "Erro: coluna " << tk.col << " - Divisao por zero!\n";
			break;
		default:
			break; 
	}
}

int type(char str){
	if (isdigit(str))
		return 1;
	else
		return 2;
}

int type(string str){
	if (isNumber(str))
		return 1;
	else
		return 2;
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

int tokenizacao (string expr, Queue<Token> &tokenQueue){
	Token tk, lastTk;
	int teste, coluna = 0;

	while (!expr.empty()){
		++coluna;
		while (expr.front() != ' ' && expr.front() != '\t' && !expr.empty()){
			if (!tk.str.empty() && (type(expr.front()) != type(tk.str) || isOperator(tk.str))){
				teste = testaErros1a5(tk.str, lastTk.str);
				if (teste > 0){
					errors(teste, tk);
					return -1;
				}
				lastTk.str = tk.str;
				lastTk.col = tk.col;
				tokenQueue.enqueue(tk);
				tk.str.clear();
				++coluna;
			}

			if (isdigit(expr.front())){
				tk.str += expr.front();
				expr.erase(expr.begin());
			}
			else{
				tk.str = expr.front();
				if (tk.str == "-" && (isOperator(lastTk.str) || lastTk.str == ""))
					tk.str = "$";
				expr.erase(expr.begin());
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
			errors(teste, tk);
			return -1;
		}
		lastTk.str.clear();
		lastTk.str = tk.str;
		lastTk.col = tk.col;
		tk.str.clear();
	}

	//TESTE ERRO 2 FINAL DA EXPRESSAO
	if (isOperator(lastTk.str) && lastTk.str != ")"){
		errors(2, lastTk);
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


int transformaParaPos(Queue<Token> &entrada, Queue<Token> &saida){
	Stack<Token> operators;
	Token symb, topSymb;
	int op;

	while (!entrada.isEmpty()){
		symb = entrada.dequeue();
			if (!isOperator(symb.str)){
					saida.enqueue(symb);
			}
			else if (symb.str == "("){
				operators.push(symb);}
			else if (symb.str == ")"){
				while (!operators.isEmpty() && operators.top().str != "("){
					topSymb = operators.pop();
					if (topSymb.str == "$")
						topSymb.str = "-";
					saida.enqueue(topSymb);
				}
				if (operators.isEmpty()){
					errors(6, symb);
					return -1;
				}
				operators.pop(); // remove o '(';
			}
			else{
				while(!operators.isEmpty() && prioridade(operators.top().str) >= prioridade(symb.str)){
					topSymb = operators.pop();
					//if (topSymb.str == "$")
					//	topSymb.str = "-";
					saida.enqueue(topSymb);
				}
				operators.push(symb);
			}

		}
	while(!operators.isEmpty()){
		symb = operators.pop();
		if (symb.str == "("){
			errors(7, symb);
			return -1;
		}
		saida.enqueue(symb);
	}
	return 1;
}

int calcula(int op1, int op2, string symb){
	if (symb == "*")
		return op1*op2;
	if (symb == "/")
		return op1/op2;
	if (symb == "+")
		return op1 + op2;
	if (symb == "-")
		return op1 - op2;
	if (symb == "\%")
		return op1%op2;
	if (symb == "^")
		return pow(op1,op2);
}

int calculaPosF(Queue<Token> posfix){
	int result, op1, op2;
	Token symb;
	Stack<int>operandos;

	while (!posfix.isEmpty()){
		symb = posfix.dequeue();
		if (isNumber(symb.str))
			operandos.push(stoi(symb.str));
		else if(symb.str == "$"){
			op1 = operandos.pop();
			result = op1*(-1);
			operandos.push(result);
		}
		else{
			op2 = operandos.pop();
			op1 = operandos.pop();
			result = calcula(op1, op2, symb.str);
			operandos.push(result);
		}
	}
	result = operandos.pop();
	return result;
}

int main(){
	Queue<Token> infix, posfix;
	Queue<string> expressions;
	Token t;
	int result = 0;

	if (readFile(expressions)){
		while (!expressions.isEmpty()){
			cout << expressions.front() << endl;
			if (!infix.isEmpty())
				infix.clear();
			if (!posfix.isEmpty())
				posfix.clear();
			tokenizacao(expressions.dequeue(), infix); //OBS: CORRIGIR TOKENIZAÇÃO
			/*while(!infix.isEmpty()){
				t = infix.dequeue();
				t.print();
				
			}*/
			//infix.print();
			if (transformaParaPos(infix, posfix) > 0){
				//posfix.print();
				result = calculaPosF(posfix);
				cout << result << endl;
			}			
		}
	}
	else{
		cout << "Erro ao abrir o arquivo. Por favor, tente novamente.\n";
	}
	
	return 0;
}
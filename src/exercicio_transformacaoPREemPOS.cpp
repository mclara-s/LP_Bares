#include <iostream>
#include <string>
#include "../headers/stack.hpp"

bool isOperator(string ch){
	if (ch == "*" || ch == "/" || ch == "+" || ch == "-" || ch == "(" || ch == ")" ||
		ch == "SIMBOLO PORCENTAGEM" || ch == "$" || ch == "^")
		return true;
	else
		return false;
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

/*void calculaPos(string expr){  //A string expr ja eh a expressão pós-fixa
	int opA, opB;
	for (int i = 0; i < expr.length(); ++i)
	{
		if (isOperator(expr[i])){
			//Como a expressão pós-fixa sempre irá começar com um numero, com certeza a pilha já terá pelo menos 2 valores
			opA = (pilha.pop()).toInt(); 	
			opB = (pilha.pop()).toInt();
			result = opera(opA, opB, S[i]);
			pilha.push(to_string(result));
		}
		else
			pilha.push(S[i]);
	}
}*/

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
					saida.enqueue(topSymb);
				}
				operators.pop(); // remove o '(';
			}
			else{
				while(!operators.isEmpty() && prioridade(operators.top()) >= prioridade(symb)){
					topSymb = operators.pop();
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
	return 0;
}
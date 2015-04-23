#include <iostream>
#include <string>
#include "../headers/stack.hpp"

bool isOperator(char ch){
	if (ch == '*' || ch == '/' || ch == '+' || ch == '-')
		return true;
	else
		return false;
}

bool temPrioridade(char operador1, char operador2){

}

void calculaPos(string expr){  //A string expr ja eh a expressão pós-fixa
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
}

void transformaParaPos(string exprPre, string &exprPos){
	for (int i = 0; i < exprPre.length(); ++i){
		if (!isOperator(exprPre[i]))
			exprPos += exprPre[i];
		else if(!pilha.isEmpty() && temPrioridade(pilha.top(), exprPre[i])){
			while(!pilha.isEmpty())
				exprPos += pilha.pop();
			pilha.push(exprPre[i]);
		}
		else
			pilha.push(exprPre[i]);
	}
	while(!pilha.isEmpty())
		exprPos += pilha.pop();
}

int main(){
	return 0;
}
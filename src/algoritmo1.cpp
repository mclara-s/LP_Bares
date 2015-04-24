#include <iostream>
#include <string>
#include "../headers/stack.hpp"

/*char Infx2Posfx (){
	while(Sequence != top()){
		if(symb == op1 || symb == op2){
			top() = symb;
		}
		else{
			while((Sequence =! isEmpty()) && topSymb >= symb){
				if (topSymb >= symb){
					remove(topSymb) -> push();
				}

			}
			top(symb);
		}
	}
}*/

transformaParaPos(queue &entrada){
	queue saida;
	stack operators;
	string symb, topSymb;

while (!entrada.isEmpty()){
		symb = entrada.dequeue();
		if (!isOperator(symb))
			saida.enqueue(symb);
		else{
			while (!operators.isEmpty() && prcd(operators.top(), symb){
				//if (prcd(operators.top(), symb)){
					topSymb = operators.pop();
					saida.enqueue(topSymb);
				//}
			}
			operators.push(symb);
		}

	}
	while(!operators.isEmpty()){
		symb = operators.pop();
		saida.enqueue(symb);
	}
	return saida;
}
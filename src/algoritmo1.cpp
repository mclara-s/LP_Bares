#include <iostream>
#include <string>
#include "../headers/stack.hpp"

char Infx2Posfx (){
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
}
char Infx2Posfx (){
	while(Sequence != front()){
		if(symb == op1 || op2){
			popFront() = symb;
		}
		else{
			while((Sequence =! isEmpty()) && topSymb >= symb){
				if (topSymb >= symb){
					remove(topSymb) -> pushBack();
				}

			}
			popFront(symb);
		}
	}
}
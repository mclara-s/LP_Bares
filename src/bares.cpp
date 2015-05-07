#include "../headers/bares.hpp"

Bares::Bares(){
	infix.clear();
	posfix.clear();
	result = 0;
}
Bares::~Bares(){}

bool Bares::isOperator(string ch){
	if (ch == "*" || ch == "/" || ch == "+" || ch == "-" || ch == "(" || ch == ")" ||
		ch == "\%" || ch == "$" || ch == "^")
		return true;
	else
		return false;
}

bool Bares::isNumber(string str){
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

void Bares::errors(int i, Token tk){
	switch (i){
		case 1:
			cout << "Erro: coluna " << tk.col << " - Constante numerica invalida.\n";
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
			cout << "Erro: coluna " << tk.col+1 << " - Divisao por zero!\n";
			break;
		default:
			break; 
	}
}
int Bares::type(char str){
	if (isdigit(str))
		return 1;
	else
		return 2;
}
int Bares::type(string str){
	if (isNumber(str))
		return 1;
	else
		return 2;
}
int Bares::testaErros1a5(string token, string lastToken){
	/**
	* teste1
	*/
	if (isNumber(token)){
		int i = stoi(token);
		if(i > 32767 || i < -32767 )
			return 1;
	}

	/** teste2 no meio da expressão
	*/
	if (isOperator(token) && isOperator(lastToken) && 
		token != "(" && token != ")" && token != "$" && lastToken!= "(" && lastToken!=")"){
		return 2;
	}
	if (token == ")" && (isOperator(lastToken) && lastToken!= ")")){
		return 2;
	}
	if (lastToken == "(" && (token!= "$" && token != "(" && !isNumber(token))){

		return 2;
	}

	/**
	* teste 3 e 4
	*/
	if (!isNumber(token) && !isOperator(token)){
		if ((token.front() >= 65 && token.front() <= 90) || (token.front() >= 97 && token.front() <= 122))
			return 3;
		else
			return 4;
	}

	/**
	* teste5
	*/
	if (isNumber(token) && isNumber(lastToken)){
		return 5;
	}
	if (token == "(" && ((!isOperator(lastToken) && lastToken != "") || lastToken == ")")){
		return 5;
	}
	else
		return 0;
}
int Bares::tokenizacao (string expr){
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
				infix.enqueue(tk);
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
		infix.enqueue(tk);
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
	/**
	* teste2 no final da expressão
	*/
	if (isOperator(lastTk.str) && lastTk.str != ")"){
		errors(2, lastTk);
		return -1;
	}

	return 1;
}

int Bares::prioridade(string op){
	if (op == "$")
		return 5;
	if (op == "^")
		return 4;
	if (op == "*" || op == "/" || op == "\%")
		return 3;
	if (op == "+" || op == "-")
		return 2;
	if (op == ")" || op == "(")
		return 1;
}
int Bares::transformaParaPos(){
	Stack<Token> operators;
	Token symb, topSymb;
	int op;

	while (!infix.isEmpty()){
		symb = infix.dequeue();
			if (!isOperator(symb.str)){
					posfix.enqueue(symb);
			}
			else if (symb.str == "(" || symb.str == "$"){
				operators.push(symb);}
			else if (symb.str == ")"){
				while (!operators.isEmpty() && operators.top().str != "("){
					topSymb = operators.pop();
					posfix.enqueue(topSymb);
				}
				if (operators.isEmpty()){
					errors(6, symb);
					return -1;
				}
				operators.pop(); /** remove o operador'('*/
			}
			else{
				while(!operators.isEmpty() && prioridade(operators.top().str) >= prioridade(symb.str)){
					topSymb = operators.pop();
					posfix.enqueue(topSymb);
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
		posfix.enqueue(symb);
	}
	return 1;
}
bool Bares::calcula(int op1, int op2, Token symb){
	if (symb.str == "*")
		result = op1*op2;
	if (symb.str == "/"){
		if (op2 == 0){
			errors(8, symb);
			return false;
		}
		result = op1/op2;
	}
	if (symb.str == "+")
		result = op1 + op2;
	if (symb.str == "-")
		result = op1 - op2;
	if (symb.str == "\%")
		result = op1%op2;
	if (symb.str == "^")
		result = pow(op1,op2);

	return true;
}
bool Bares::calculaPosF(string expr){
	int op1, op2;
	Token symb;
	Stack<int>operandos;
	if (!posfix.isEmpty())
		posfix.clear();
	if(!infix.isEmpty())
		infix.clear();
	if (tokenizacao(expr) != -1){
		if(transformaParaPos() != -1){
			//posfix.print();
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
					if(calcula(op1, op2, symb))
						operandos.push(result);
					else
						return false;
				}
			}
			result = operandos.pop();
			return true;
		}
	}
		return false;

}

int Bares::getResult(){
	return result;
}
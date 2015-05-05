#ifndef __BARES__
	#define __BARES__

#include <iostream>
#include <cctype>
#include <math.h>
#include "token.hpp"
#include "stack.hpp"
#include "queue.hpp"

using namespace std;

class Bares{
	private:
		Token T;
		Queue<Token> infix, posfix;
		//Queue<string> expressions;
		int result;

	public:
	Bares();
	~Bares();	
/**
 * @readfile função para leitura das expressões
 * abertura do arquivo, leitura das expressões
*/
	//bool readFile();
/**
* @isoperator função para indicar quais operadores são reconhecidos
*/	
	bool isOperator(string);
/**
* @isnumber verificando se o arquivo está vazio
* caso não, fazer a leitura das expressões e números até o fim do arquivo
*/	
	bool isNumber(string);
/**
* @errors função para chamada do tratamento de erro
*/
	void errors(int, Token);
/**
* @type verifica se a string lida é válida como dígito (operador ou constante)
*/
	int type(char);
/**
* @type verifica se a string lida é válida como dígito numérico
*/
	int type(string);
/**
* @testaerros1a5 utilizando a tokenização verifica o arquivo por linha
* procurando encontrar os erros 1 a 5
*/
	int testaErros1a5(string, string);
/**
* @tokenização
*/		
	int tokenizacao (string);
	//void getExpressions();
/**
* @prioridade indicação da prioridade dos operandos 
*/
	int prioridade(string);
/**
* @transformaparapos função para empilhar usando o método pós fixo transformando a expressão
*/
	int transformaParaPos();
/**
* @calcula função para calcular as expressões matemáticas
*/
	bool calcula(int, int, Token);	
/**
* @calculaposf função para encontrar o resultado da expressão mesmo ela estando pós fixa
*/
	bool calculaPosF(string);

	int getResult();
};

#include "../src/bares.cpp"
#endif
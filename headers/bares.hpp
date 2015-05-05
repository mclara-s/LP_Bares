#ifndef __BARES__
	#define __BARES__

#include <iostream>
#include <cctype>
#include <math.h>
#include "token.hpp"
#include "stack.hpp"
#include "queue.hpp"

using namespace std;
/**
 * @class Bares Classe que iremos utilizar e suas chamadas de métodos
*/
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
 * @readfile função para leitura das expressões, abertura do arquivo, leitura das expressões
*/
	//bool readFile();
/**
* @isoperator função para indicar quais operadores são reconhecidos
* @string verifica operadores
*/	
	bool isOperator(string);
/**
* @isnumber verificando se o arquivo está vazio
* caso não, fazer a leitura das expressões e números até o fim do arquivo
* @param string verifica expressões (operandos e operadores)
*/	
	bool isNumber(string);
/**
* @errors função para chamada do tratamento de erro
* @param int, Token receberá os erros 
*/
	void errors(int, Token);
/**
* @type-char verifica se a string lida é válida como dígito (operador ou constante)
* @param char para receber apenas dígito
*/
	int type(char);
/**
* @type-string verifica se a string lida é válida como dígito numérico
* @char verifica dígito numérico
*/
	int type(string);
/**
* @testaerros1a5 utilizando a tokenização verifica o arquivo por linha
* verificando se existem os erros 1 a 5
* @param string verifica operandos e operadores
*/
	int testaErros1a5(string, string);
/**
* @tokenização
* @param string
*/		
	int tokenizacao (string);
	//void getExpressions();
/**
* @prioridade indicação da prioridade dos operandos 
* @param string verifica operandos para calcular na prioridade informada
*/
	int prioridade(string);
/**
* @transformaparapos função para empilhar usando o método pós fixo transformando a expressão
*/
	int transformaParaPos();
/**
* @calcula função para calcular as expressões matemáticas
* @param valores int e Token
*/
	bool calcula(int, int, Token);	
/**
* @calculaposf função para encontrar o resultado da expressão
* @param string pois recebe operadores e operandos
*/
	bool calculaPosF(string);
/**
* @getResult função para mostrar o resultado da função calcula
*/
	int getResult();
};

#include "../src/bares.cpp"
#endif